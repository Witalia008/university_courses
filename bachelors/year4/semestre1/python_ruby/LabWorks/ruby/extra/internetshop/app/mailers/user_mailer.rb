class UserMailer < ApplicationMailer
  default from: 'idsgpr@gmail.com'

  def answer_email(user, question)
    @user = user
    @question = question
    mail(to: @user.email, subject: 'Question answer')
  end
end
