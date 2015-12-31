class Message < ActiveRecord::Base
  belongs_to :user, :foreign_key => :sender
  belongs_to :user, :foreign_key => :receiver
end
