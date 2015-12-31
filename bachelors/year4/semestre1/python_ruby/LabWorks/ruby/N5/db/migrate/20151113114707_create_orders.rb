class CreateOrders < ActiveRecord::Migration
  def change
    create_table :orders do |t|
      t.references :user, index: true, foreign_key: true
      t.references :item, index: true, foreign_key: true
      t.integer :count
      t.float :price
      t.boolean :pending

      t.timestamps null: false
    end
  end
end
