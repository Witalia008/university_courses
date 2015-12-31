class Message < ActiveRecord::Base
  belongs_to :group
  belongs_to :from, class_name: 'User'
  belongs_to :to, class_name: 'User'

  validates_presence_of :from_id, :text
end
