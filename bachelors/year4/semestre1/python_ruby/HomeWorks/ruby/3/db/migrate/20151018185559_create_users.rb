class CreateUsers < ActiveRecord::Migration
  def change
    create_table :users do |t|
      t.string :username
      t.string :email
      t.string :encrypted_password
      t.string :salt
      t.references :role, index: true, foreign_key: true

      t.timestamps null: false
    end
  end
end
