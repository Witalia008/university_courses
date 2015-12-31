class RenameGoodFloatParameterToServiceFloatParameter < ActiveRecord::Migration
  def change
    rename_table :good_float_parameters, :service_float_parameters
  end
end
