class AddTypeToGood < ActiveRecord::Migration
  def change
    add_column :goods, :type, :string
  end
end
