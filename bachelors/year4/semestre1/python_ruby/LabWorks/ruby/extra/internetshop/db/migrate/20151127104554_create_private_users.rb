class CreatePrivateUsers < ActiveRecord::Migration
  def change
    create_table :private_users do |t|
      t.string :full_name
      t.references :user, index: true, foreign_key: true

      t.timestamps null: false
    end
  end
end
