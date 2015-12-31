class User < ActiveRecord::Base
  # Include default devise modules. Others available are:
  # :confirmable, :lockable, :timeoutable and :omniauthable
  devise :database_authenticatable, :registerable,
         :recoverable, :rememberable, :trackable, :validatable

  has_and_belongs_to_many :groups,
                          :join_table => 'users_groups',
                          :foreign_key => 'user_id',
                          :association_foreign_key => 'group_id'
  has_and_belongs_to_many :users,
                          :join_table => 'friends',
                          :foreign_key => 'first_id',
                          :association_foreign_key => 'second_id'
  has_many :messages, foreign_key: :from_id
  has_many :groups_created, class_name: 'Group', foreign_key: :creator_id

  validates_presence_of :email, :username
  validates_format_of :username, with: /\A[a-zA-Z0-9_\.]+\z/
  validates_format_of :phone, with: /\A(\(?([0-9]{3})\)?([ .-]?)([0-9]{3})\2([0-9]{4}))?\z/

  attr_accessor :login
  def self.find_for_database_authentication(warden_conditions)
    conditions = warden_conditions.dup
    if login = conditions.delete(:login)
      where(conditions.to_h).where(['username = :value OR lower(email) = lower(:value)', {:value => login }]).first
    else
      conditions[:email].downcase! if conditions[:email]
      where(conditions.to_h).first
    end
  end

  before_save :assign_role
  def assign_role
    unless self.role
      self.role = 'USER'
    end
  end

  def admin?
    self.role == 'ADMIN'
  end
end
