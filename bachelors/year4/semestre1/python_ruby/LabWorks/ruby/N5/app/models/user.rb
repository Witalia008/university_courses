class User < ActiveRecord::Base
  belongs_to :role
  has_many :orders

  attr_accessor :password
  EMAIL_REGEX = /\A[a-z0-9._+-]+@[a-z0-9.-]+\.[a-z0-9.-]{2,}\z/i
  validates :username, :presence => true, :uniqueness => true, :length => { :in => 3..20 }
  validates :email, :presence => true, :uniqueness => true, :format => EMAIL_REGEX
  validates :password, :confirmation => true
  validates_length_of :password, :in => 6..20, :on => :create

  before_save :encrypt_password, :assign_role
  after_save :delete_password

  def self.authenticate(username_or_email='', login_password='')
    if EMAIL_REGEX.match(username_or_email)
      user = User.find_by_email(username_or_email)
    else
      user = User.find_by_username(username_or_email)
    end
    if user && user.match_password(login_password)
      return user
    else
      return false
    end
  end
  def match_password(login_password)
    encrypted_password == BCrypt::Engine.hash_secret(login_password, salt)
  end

  private
  def assign_role
    role = Role.find_by_rolename('USER')
    if role
      self.role_id = role.id
    end
  end
  def encrypt_password
    if password.present?
      self.salt = BCrypt::Engine.generate_salt
      self.encrypted_password = BCrypt::Engine.hash_secret(password, salt)
    end
  end
  def delete_password
    self.password = nil
  end
end
