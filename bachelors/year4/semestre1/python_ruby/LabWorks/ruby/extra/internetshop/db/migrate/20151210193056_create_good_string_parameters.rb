class CreateGoodStringParameters < ActiveRecord::Migration
  def change
    create_table :good_string_parameters do |t|
      t.references :good, index: true, foreign_key: true
      t.string :name
      t.string :value

      t.timestamps null: false
    end
  end
end
