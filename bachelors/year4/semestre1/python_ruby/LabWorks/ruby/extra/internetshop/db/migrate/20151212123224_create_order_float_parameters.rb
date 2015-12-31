class CreateOrderFloatParameters < ActiveRecord::Migration
  def change
    create_table :order_float_parameters do |t|
      t.references :order_item, index: true, foreign_key: true
      t.string :name
      t.float :value

      t.timestamps null: false
    end
  end
end
