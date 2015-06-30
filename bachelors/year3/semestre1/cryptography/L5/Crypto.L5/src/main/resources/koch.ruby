require 'RMagick' include Magick
$cos_t = [[1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
          [0.9807853, 0.8314696, 0.5555702, 0.1950903,  -0.1950903,-0.5555702,-0.8314696,-0.9807853],
          [0.9238795, 0.3826834,-0.3826834,-0.9238795,  -0.9238795,-0.3826834, 0.3826834, 0.9238795],
          [0.8314696,-0.1950903,-0.9807853,-0.5555702,   0.5555702, 0.9807853, 0.1950903,-0.8314696],
          [0.7071068,-0.7071068,-0.7071068, 0.7071068,   0.7071068,-0.7071068,-0.7071068, 0.7071068],
          [0.5555702,-0.9807853, 0.1950903, 0.8314696,  -0.8314696,-0.1950903, 0.9807853,-0.5555702],
          [0.3826834,-0.9238795, 0.9238795,-0.3826834,  -0.3826834, 0.9238795,-0.9238795, 0.3826834],
          [0.1950903,-0.5555702, 0.8314696,-0.9807853,   0.9807853,-0.8314696, 0.5555702,-0.1950903] ]
$e = [[0.125, 0.176777777, 0.176777777, 0.176777777,   0.176777777, 0.176777777, 0.176777777, 0.176777777],
      [0.176777777, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25],
      [0.176777777, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25],
      [0.176777777, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25],
      [0.176777777, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25],
      [0.176777777, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25],
      [0.176777777, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25],
      [0.176777777, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25]];

def insert_message(image,text)
    i = image.copy
    dct = Array.new(8).map!{Array.new(8)}
    k = 0
    l = 0
    s=0
    temp = Array.new(8).map!{Array.new(8)}
    (0..(image.columns - 1)).step(8) do |i|
        (0..(image.rows - 1)).step(8) do |j|
            break if l >= text.length*8
            (0..7).each do |x|
                 (0..7).each do |y|
                      temp[x][y] = {
                           :red=>image.pixel_color(j+x,i+y).red,
                           :green=>image.pixel_color(j+x,i+y).green,
                           :blue=>image.pixel_color(j+x,i+y).blue
                      }
                 end
            end
            dct = dct(dct,temp)
            k = dct[3][4].abs - dct[4][3].abs
            if get_bit(text,l)
                if k<=25
                    dct[3][4] = (dct[3][4]>=0) ? dct[4][3].abs + 150 : -1*(dct[4][3].abs + 150)
                end
            else
                if k>=-25
                    dct[4][3] = (dct[4][3]>=0) ? dct[3][4].abs + 150 : -1*(dct[3][4].abs + 150)
                end
            end
            xt  = temp.clone
            temp = idct(dct,temp)
            (0..7).each do |x|
                (0..7).each do |y|
                    pixel = Pixel.new(temp[x][y][:red],temp[x][y][:green],temp[x][y][:blue])
                    image.pixel_color(j+x,i+y,pixel)
                end
            end
            l=l+1
        end
        break if l >= text.length
    end
    image.write('cr.bmp')
    return image
end

def read_message(image)
      k = 0
      s=0
      out = []
      l=0
      a=''
      p=0
      b=0
      dct = Array.new(8).map!{Array.new(8)}
      temp = Array.new(8).map!{Array.new(8)}
      (0..(image.columns - 1)).step(8) do |i|
        (0..(image.rows - 1)).step(8) do |j|
            (0..7).each do |x|
                (0..7).each do |y|
                    temp[x][y] = {
                        :red=>image.pixel_color(j+x,i+y).red,
                        :green=>image.pixel_color(j+x,i+y).green,
                        :blue=>image.pixel_color(j+x,i+y).blue
                    }
                end
            end
            l=l+1
            dct = dct(dct,temp)
            k = dct[3][4].abs-dct[4][3].abs
            if k>=25
                a=1
            elsif k<=-25
                a=0
            else
                a=-1
                break
            end
            b |= a << p
            if p==7
                out.push(b.chr)
                b=0
            end
            p=(p<7) ? p+1 : 0
        end
        if a==-1
            break
        end   
    end   
    return out.join 
end  
def get_bit(str,pos)
  return true if  str[pos/8].ord & (1 << pos % 8) > 0
  return false if  str[pos/8].ord & (1 << pos % 8) <= 0 
end 
image = Magick::Image.read('src.bmp').first insert_message(image,"qweqwe")
image = Magick::Image.read('dst.bmp').first puts read_message image