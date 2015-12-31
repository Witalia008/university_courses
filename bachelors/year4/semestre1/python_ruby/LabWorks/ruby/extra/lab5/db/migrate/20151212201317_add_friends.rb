class AddFriends < ActiveRecord::Migration
  def change
    create_table :friends, id: false do |t|
      t.integer :first_id, :null => false
      t.integer :second_id, :null => false
    end
    add_index :friends, :first_id
    add_index :friends, :second_id
  end
end
