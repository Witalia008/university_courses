gem 'gtk3'
require 'gtk3'
gem 'actionmailer'
require 'action_mailer'
require 'net/imap'

$my_email = 'username@ukr.net'
$my_password = ''
$smtp_server = 'smtp.ukr.net'
$smtp_port = 465
$imap_server = 'imap.ukr.net'
$imap_port = 993

ActionMailer::Base.raise_delivery_errors = true
ActionMailer::Base.delivery_method = :smtp
ActionMailer::Base.smtp_settings = {
    :address   => $smtp_server,
    :port      => $smtp_port,
    :ssl => true,
    :authentication => :login,
    :user_name      => $my_email,
    :password       => $my_password
}

class SendWindow < Gtk::Window
  def initialize
    super
    init_ui
  end

  def init_ui
    vbox = Gtk::Box.new :vertical, 2

    grid = Gtk::Grid.new
    grid.set_property 'column-homogeneous', true

    grid.attach (Gtk::Label.new 'From:'), 0, 0, 1, 1
    grid.attach (Gtk::Label.new $my_email), 1, 0, 1, 1

    grid.attach (Gtk::Label.new 'To:'), 0, 1, 1, 1
    entry_to = Gtk::Entry.new
    grid.attach entry_to, 1, 1, 1, 1

    grid.attach (Gtk::Label.new 'Subject:'), 0, 2, 1, 1
    entry_subject = Gtk::Entry.new
    grid.attach entry_subject, 1, 2, 1, 1

    vbox.pack_start grid, :expand => false, :fill => false

    vbox.pack_start (Gtk::Label.new 'Message Body:'), :expand => false, :fill => false

    entry_body = Gtk::TextView.new
    entry_body.cursor_visible = true
    entry_body.set_size_request 400, 300
    vbox.pack_start entry_body, :expand => true

    hbox = Gtk::Box.new :horizontal, 5
    send_btn = Gtk::Button.new :label => 'Send'
    send_btn.signal_connect('clicked') do |w|
      if send_mail(entry_to.text, entry_subject.text, entry_body.buffer.text)
        md = Gtk::MessageDialog.new :parent => self,
                                    :flags => :destroy_with_parent, :type => :info,
                                    :buttons_type => :close, :message => 'Email sent'
        md.run
        md.destroy
        self.hide
      else
        md = Gtk::MessageDialog.new :parent => self,
                                    :flags => :destroy_with_parent, :type => :info,
                                    :buttons_type => :close, :message => 'There was an error'
        md.run
        md.destroy
      end
    end
    discard_btn = Gtk::Button.new :label => 'Discard'
    discard_btn.signal_connect('clicked') do |w|
      self.hide
    end
    hbox.add send_btn
    hbox.add discard_btn

    halign = Gtk::Alignment.new 1, 0, 0, 0
    halign.add hbox

    vbox.pack_start halign, :expand => false, :fill => false

    align = Gtk::Alignment.new 0, 0, 0, 0
    align.add vbox
    add align

    set_title 'Send Mail'
    # set_default_size 400, 300
    set_window_position Gtk::WindowPosition::CENTER
    show_all
  end

  def send_mail(to, subject, body)
    ActionMailer::Base.mail(:from => $my_email, :to => to, :subject => subject, :body => body).deliver_now
  end
end

class RubyApp < Gtk::Window

  def initialize
    super
    init_ui
    @mails = []
    @imap = Net::IMAP.new($imap_server)
    @imap.login($my_email, $my_password)
    @imap.select('inbox')
  end

  def init_ui
    vbox = Gtk::Box.new :vertical, 2

    scrolled_win = Gtk::ScrolledWindow.new
    scrolled_win.set_size_request 200, 300
    scrolled_win.set_policy(:automatic,:automatic)
    email_list = Gtk::ListStore.new(String)
    column = Gtk::TreeViewColumn.new('Inbox:',
                                     Gtk::CellRendererText.new, {:text => 0})
    treeview = Gtk::TreeView.new(email_list)
    treeview.append_column(column)
    treeview.selection.set_mode(:single)
    scrolled_win.add_with_viewport(treeview)

    scrolled_msg = Gtk::ScrolledWindow.new
    scrolled_msg.set_size_request 500, 300
    scrolled_msg.set_policy(:automatic,:automatic)
    message_view = Gtk::TextView.new
    message_view.set_editable false
    message_view.set_cursor_visible false
    scrolled_msg.add(message_view)

    treeview.signal_connect('row-activated') do |_, path, _|
      message_view.buffer.text = @mails[path.to_s.to_i].attr['BODY[TEXT]']
    end

    grid = Gtk::Box.new :horizontal, 2
    grid.add scrolled_win
    grid.add scrolled_msg
    vbox.pack_start grid, :expand => true

    send_btn = Gtk::Button.new :label => 'New E-mail'
    send_btn.signal_connect('clicked') do |w|
      SendWindow.new
    end
    refresh_btn = Gtk::Button.new :label => 'Refresh'
    refresh_btn.signal_connect('clicked') do |w|
      Thread.new {
        retrieve_mail
        update_mail_list email_list
      }
    end
    hbox = Gtk::Box.new :horizontal, 2
    hbox.add send_btn
    hbox.add refresh_btn

    haligh = Gtk::Alignment.new 1, 0, 0, 0
    haligh.add hbox

    vbox.pack_start haligh, :expand => false, :fill => false, :padding => 5

    add vbox

    set_title 'My Mail'
    signal_connect 'destroy' do
      @imap.logout
      @imap.disconnect
      Gtk.main_quit
    end
    set_default_size 400, 300
    set_window_position Gtk::WindowPosition::CENTER

    show_all
  end

  def update_mail_list(list)
    list.clear
    @mails.each do |mail|
      # puts "#{mail}"
      header = mail.attr['ENVELOPE']
      list.append[0] = (header.from[0].name || header.from[0].mailbox + '@' + header.from[0].host || '') + ' , ' + header.subject
    end
  end

  def retrieve_mail
    cnt = @imap.status('inbox', ['MESSAGES'])['MESSAGES']
    @mails = @imap.fetch(cnt-20..cnt, %w(ENVELOPE BODY[TEXT])).reverse
  end
end

window = RubyApp.new
Gtk.main