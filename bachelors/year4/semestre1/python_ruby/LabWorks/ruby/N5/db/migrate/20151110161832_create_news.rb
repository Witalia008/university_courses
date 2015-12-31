class CreateNews < ActiveRecord::Migration
  def change
    create_table :news do |t|
      t.string :header
      t.string :preview
      t.string :image
      t.string :full_text

      t.timestamps null: false
    end
  end
end
