class DeleteOrderItem < ActiveRecord::Migration
  def change
    remove_column :order_float_parameters, :order_item_id
    add_column :order_float_parameters, :order_id, :integer
    add_foreign_key :order_float_parameters, :orders
    drop_table :order_items
  end
end
