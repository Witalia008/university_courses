class CreateGoodFloatParameters < ActiveRecord::Migration
  def change
    create_table :good_float_parameters do |t|
      t.references :good, index: true, foreign_key: true
      t.string :name
      t.float :value

      t.timestamps null: false
    end
  end
end
