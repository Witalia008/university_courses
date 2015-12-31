class CreateGroups < ActiveRecord::Migration
  def change
    create_table :groups do |t|
      t.integer :creator_id
      t.text :group_name
      t.boolean :open

      t.timestamps null: false
    end
    add_index :groups, :creator_id

    create_table :users_groups, id: false do |t|
      t.belongs_to :user, index: true
      t.belongs_to :group, index: true
    end
  end
end
