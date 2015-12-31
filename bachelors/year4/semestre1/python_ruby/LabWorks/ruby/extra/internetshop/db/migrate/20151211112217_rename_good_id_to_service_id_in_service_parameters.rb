class RenameGoodIdToServiceIdInServiceParameters < ActiveRecord::Migration
  def change
    rename_column :service_float_parameters, :good_id, :service_id
    rename_column :service_string_parameters, :good_id, :service_id
  end
end
