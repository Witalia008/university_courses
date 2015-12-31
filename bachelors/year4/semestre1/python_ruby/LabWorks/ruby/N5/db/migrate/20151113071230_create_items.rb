class CreateItems < ActiveRecord::Migration
  def change
    create_table :items do |t|
      t.string :item_name
      t.string :short_descr
      t.string :image
      t.float :price
      t.string :description
      t.references :group, index: true, foreign_key: true

      t.timestamps null: false
    end
  end
end
