class RenameGoodIdToServiceIdInOrderItems < ActiveRecord::Migration
  def change
    rename_column :order_items, :good_id, :service_id
  end
end
