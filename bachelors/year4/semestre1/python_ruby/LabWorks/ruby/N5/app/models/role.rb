class Role < ActiveRecord::Base
  has_many :users

  validates :rolename, :presence => true, :uniqueness => true, :length => { :in => 3..30 }
end
