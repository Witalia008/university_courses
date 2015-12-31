class RenameTypeToServiceTypeInGoods < ActiveRecord::Migration
  def change
    rename_column :goods, :type, :service_type
  end
end
