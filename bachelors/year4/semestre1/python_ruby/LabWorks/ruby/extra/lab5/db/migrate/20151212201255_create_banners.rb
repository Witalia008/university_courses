class CreateBanners < ActiveRecord::Migration
  def change
    create_table :banners do |t|
      t.string :image
      t.string :url
      t.references :group, index: true, foreign_key: true

      t.timestamps null: false
    end
  end
end
