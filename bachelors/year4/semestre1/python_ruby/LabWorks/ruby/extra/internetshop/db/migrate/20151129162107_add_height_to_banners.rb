class AddHeightToBanners < ActiveRecord::Migration
  def change
    add_column :banners, :height, :integer
  end
end
