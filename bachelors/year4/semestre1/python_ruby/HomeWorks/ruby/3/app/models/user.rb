require 'BCrypt'

class User < ActiveRecord::Base
  belongs_to :role

  attr_accessor :password
  EMAIL_REGEX = /\A[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,}\z/i
  validates :username, :presence => true, :uniqueness => true, :length => {:in => 3..20}
  validates :email, :presence => true, :uniqueness => true, :format => EMAIL_REGEX
  validates :password, :confirmation => true
  validates_length_of :password, :in => 6..20, :on => create

  before_save :encrypt_password, :assign_role
  after_save :clear_password

  def self.authenticate(username_or_email='', login_password='')
    if EMAIL_REGEX.match(username_or_email)
      user = User.find_by_email(username_or_email)
    else
      user = User.find_by_username(username_or_email)
    end
    if user && user.match_password(login_password)
      logger.debug "Auth success for #{username_or_email}"
      return user
    else
      logger.debug "Auth failure for #{username_or_email}"
      return false
    end
  end

  def match_password(login_password='')
    encrypted_password == BCrypt::Engine.hash_secret(login_password, salt)
  end

  protected
  def encrypt_password
    if password.present?
      self.salt = BCrypt::Engine.generate_salt
      self.encrypted_password = BCrypt::Engine.hash_secret(password, salt)
    end
  end
  def clear_password
    self.password = nil
  end
  def assign_role
    unless self.role
      self.role = Role.find_by_role_name('USER')
    end
  end
end
