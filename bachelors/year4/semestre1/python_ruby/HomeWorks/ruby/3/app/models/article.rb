class Article < ActiveRecord::Base
  has_and_belongs_to_many :roles
  has_many :comments

  validates :topic, :length => {:minimum => 5}
  validates :text, :length => {:minimum => 1}, :allow_blank => false

  def is_permitted(role_id)
    # role shouldn't be in banned list
    !self.roles.exists?(:id => role_id)
  end
end
