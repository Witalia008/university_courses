class RemoveCategoryFromGoods < ActiveRecord::Migration
  def change
    remove_column :goods, :category_id
  end
end
