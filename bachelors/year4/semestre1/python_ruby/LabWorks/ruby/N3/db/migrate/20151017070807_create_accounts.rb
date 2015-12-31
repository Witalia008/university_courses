class CreateAccounts < ActiveRecord::Migration
  def change
    create_table :accounts do |t|
      t.integer :balance
      t.boolean :blocked
      t.references :user, index: true, foreign_key: true

      t.timestamps null: false
    end
  end
end
