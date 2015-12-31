# https://www.redmine.org/projects/redmine/wiki/HowTo_install_rmagick_gem_on_Windows
# OR: http://www.julesberman.info/rubyhome.htm
require 'RMagick'

CHECK_SEQ = 0b11011010 # 1 byte - 8 bits of control seq
LSB_FIRST = 0
LSB_SECOND = 1

class Fixnum
  def reverse_bits(bcnt)
    a = self
    b = 0
    (bcnt * 8).times do
      b = (b << 1) | (a & 1)
      a >>= 1
    end
    b
  end
  def set(pos)
    self | (1 << pos)
  end
  def unset(pos)
    self & (~(1 << pos))
  end
  def change_bit(pos, val)
    if val == 1 then set(pos) else unset(pos) end
  end
end

def write_byte(data, b, pos)
  (0..3).each do |i|
    data[pos] = data[pos].ord.change_bit(LSB_FIRST, b[i*2]).chr
    data[pos] = data[pos].ord.change_bit(LSB_SECOND, b[i*2+1]).chr
    pos += 1
  end
  pos
end

def read_byte(data, pos)
  res = 0
  (0..3).each do |i|
    res = res.change_bit(i*2, data[pos].ord[LSB_FIRST])
    res = res.change_bit(i*2+1, data[pos].ord[LSB_SECOND])
    pos += 1
  end
  return res, pos
end

def encode(data, msg)
  raise 'Wrong format' unless data[0..5] == 'GIF89a'

  # three least significant bits are size
  # 10th byte - where options are stored
  size = data[10].ord.reverse_bits(1) >> 5
  colour_count = 1 << (size + 1)
  poss_msg_len = colour_count * 3 / 4
  poss_txt_len = poss_msg_len - 2 # 1 byte for check, 1 byte for length

  raise 'Too long message' if poss_txt_len < msg.length

  pos = 13 # here starts the palette

  pos = write_byte(data, CHECK_SEQ, pos)
  pos = write_byte(data, msg.length, pos)
  msg.each_byte do |b|
    pos = write_byte(data, b, pos)
  end

  data
end

def decode(data)
  raise 'Wrong format' unless data[0..5] == 'GIF89a'

  size = data[10].ord.reverse_bits(1) >> 5
  colour_count = 1 << (size + 1)
  poss_msg_len = colour_count * 3 / 4
  poss_txt_len = poss_msg_len - 2

  pos = 13
  chk, pos = read_byte(data, pos)

  raise 'No message (Check incorrect)' if chk != CHECK_SEQ

  len, pos = read_byte(data, pos)

  raise 'No message (Length incorrect)' if poss_txt_len < len

  res = ''
  len.times do
    val, pos = read_byte(data, pos)
    res << val.chr
  end
  res
end


require 'tk'
require 'tempfile'

root = TkRoot.new {title 'Steganography'}

img_btn = TkButton.new(root) do
  grid(:row => 0, :column => 0, :columnspan => 2)
end

TkButton.new(root) do
  text 'Load Image'
  command {
    $img_file = Tk.getOpenFile
    img_btn.image = TkPhotoImage.new(:file => $img_file)
    $img_rm = Magick::Image.read($img_file).first
  }
  grid(:row => 1, :column => 0)
end
TkButton.new(root) do
  text 'Save Image'
  command {
    if $img_rm
      file = Tk.getSaveFile
      $img_rm.write(file)
    end
  }
  grid(:row => 1, :column => 1)
end
TkLabel.new(root) {
  text 'Message:'
  grid(:row => 2, :column => 0)
}
text_entry = TkEntry.new(root) {
  grid(:row => 2, :column => 1)
}
TkButton.new(root) do
  text 'Encode ->'
  command {
    if $img_rm
      _, blob = $img_rm.marshal_dump
      $img_rm = Magick::Image.from_blob(encode(blob, text_entry.value)).first
      file = Dir::Tmpname.make_tmpname($img_file, nil)
      $img_rm.write(file)
      img_btn.image = TkPhotoImage.new(:file => file)
      Tk.messageBox(
            :type => :ok,
            :icon => :info,
            :title => 'Success',
            :message => 'Text was encrypted successfully'
      )
      File::delete(file)
    end
  }
  grid(:row => 3, :column => 0)
end
TkButton.new(root) do
  text '<- Decode'
  command {
    _, blob = $img_rm.marshal_dump
    msg = decode(blob)
    puts msg
    Tk.messageBox(
        :type => :ok,
        :icon => :info,
        :title => 'Decrypt Success',
        :message => msg
    )
  }
  grid(:row => 3, :column => 1)
end

Tk.mainloop