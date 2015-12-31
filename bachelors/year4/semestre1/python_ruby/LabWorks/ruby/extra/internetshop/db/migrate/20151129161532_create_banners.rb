class CreateBanners < ActiveRecord::Migration
  def change
    create_table :banners do |t|
      t.string :link
      t.string :image_link
      t.integer :priority
      t.integer :width

      t.timestamps null: false
    end
  end
end
