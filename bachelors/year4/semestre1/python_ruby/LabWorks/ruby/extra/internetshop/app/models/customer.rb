class Customer < ActiveRecord::Base
  belongs_to :user
  validates :full_name, :presence => true
end
