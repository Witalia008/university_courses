class CreateMessages < ActiveRecord::Migration
  def change
    create_table :messages do |t|
      t.integer :sender
      t.integer :receiver
      t.text :content

      t.timestamps null: false
    end
    add_foreign_key :messages, :users, column: :sender, on_delete: :cascade
    add_foreign_key :messages, :users, column: :receiver, on_delete: :cascade
  end
end
