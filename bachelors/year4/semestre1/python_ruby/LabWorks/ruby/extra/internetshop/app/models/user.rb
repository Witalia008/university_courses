class User < ActiveRecord::Base
  # Include default devise modules. Others available are:
  # :confirmable, :lockable, :timeoutable and :omniauthable
  devise :database_authenticatable, :registerable,
         :recoverable, :rememberable, :trackable, :validatable
  has_one :customer, dependent: :destroy
  has_one :worker, dependent: :destroy
  has_many :services, dependent: :destroy
  has_many :messages, dependent: :destroy, :foreign_key => :sender
  has_many :messages, dependent: :destroy, :foreign_key => :receiver
end
