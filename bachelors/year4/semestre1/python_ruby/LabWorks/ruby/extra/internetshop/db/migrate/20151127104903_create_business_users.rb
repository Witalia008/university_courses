class CreateBusinessUsers < ActiveRecord::Migration
  def change
    create_table :business_users do |t|
      t.string :name
      t.text :description
      t.references :user, index: true, foreign_key: true

      t.timestamps null: false
    end
  end
end
