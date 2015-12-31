class ApplicationMailer < ActionMailer::Base
  default from: 'username@ukr.net'
  default to: 'username@ukr.net'
  layout 'mailer'
end
