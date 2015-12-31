class Account < ActiveRecord::Base
  belongs_to :user
  has_many :credit_cards
end
