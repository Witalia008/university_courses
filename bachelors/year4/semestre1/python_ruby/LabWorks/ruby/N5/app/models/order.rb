class Order < ActiveRecord::Base
  belongs_to :user
  belongs_to :item

  validates :user_id, :item_id, :count, :presence => true
  validates :count, numericality: {greater_than: 0}

  before_save :default_values, :set_price

  private
  def default_values
    self.pending = true
  end
  def set_price
    self.price = self.count * self.item.price
  end
end
