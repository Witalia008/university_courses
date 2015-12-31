class Group < ActiveRecord::Base
  has_and_belongs_to_many :users,
                          :join_table => 'users_groups',
                          :foreign_key => 'group_id',
                          :association_foreign_key => 'user_id'
  belongs_to :creator, class_name: 'User'
  has_many :messages
  has_many :banners

  validates_presence_of :creator_id, :group_name
end
