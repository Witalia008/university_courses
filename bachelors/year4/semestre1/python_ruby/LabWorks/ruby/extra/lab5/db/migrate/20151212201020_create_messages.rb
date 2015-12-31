class CreateMessages < ActiveRecord::Migration
  def change
    create_table :messages do |t|
      t.integer :from_id
      t.integer :to_id, null: true
      t.string :text
      t.references :group, index: true, foreign_key: true, null: true

      t.timestamps null: false
    end

    add_index :messages, :from_id
    add_index :messages, :to_id
  end
end
