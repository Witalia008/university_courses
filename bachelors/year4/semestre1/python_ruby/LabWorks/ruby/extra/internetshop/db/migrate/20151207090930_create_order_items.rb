class CreateOrderItems < ActiveRecord::Migration
  def change
    create_table :order_items do |t|
      t.references :order, index: true, foreign_key: true
      t.references :good, index: true, foreign_key: true

      t.timestamps null: false
    end
  end
end
