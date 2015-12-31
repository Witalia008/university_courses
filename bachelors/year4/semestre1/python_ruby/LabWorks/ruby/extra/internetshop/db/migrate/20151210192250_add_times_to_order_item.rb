class AddTimesToOrderItem < ActiveRecord::Migration
  def change
    add_column :order_items, :start_time, :datetime
    add_column :order_items, :end_time, :datetime
  end
end
