class RenameGoodToService < ActiveRecord::Migration
  def change
    rename_table :goods, :services
  end
end
