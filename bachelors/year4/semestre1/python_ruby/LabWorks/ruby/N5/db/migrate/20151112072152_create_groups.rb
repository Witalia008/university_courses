class CreateGroups < ActiveRecord::Migration
  def change
    create_table :groups do |t|
      t.string :group_name
      t.string :image
      t.string :description

      t.timestamps null: false
    end
    add_reference :groups, :parent, references: :groups
    add_foreign_key :groups, :groups, column: :parent_id
  end
end
