class RenameGoodStringParameterToServiceStringParameter < ActiveRecord::Migration
  def change
    rename_table :good_string_parameters, :service_string_parameters
  end
end
