class AddCategoryToGood < ActiveRecord::Migration
  def change
    add_reference :goods, :category, index: true, foreign_key: true
  end
end
