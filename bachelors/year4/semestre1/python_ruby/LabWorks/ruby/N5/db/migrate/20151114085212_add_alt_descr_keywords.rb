class AddAltDescrKeywords < ActiveRecord::Migration
  def change
    add_column :groups, :image_alt, :string
    add_column :items, :image_alt, :string
    add_column :news, :image_alt, :string

    add_column :groups, :keywords, :string
    add_column :items, :keywords, :string
    add_column :news, :keywords, :string
  end
end
