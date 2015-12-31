class CreateRoles < ActiveRecord::Migration
  def change
    create_table :roles do |t|
      t.string :rolename

      t.timestamps null: false
    end
  end
end
