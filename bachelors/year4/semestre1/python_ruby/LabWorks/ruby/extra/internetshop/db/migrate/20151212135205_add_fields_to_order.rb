class AddFieldsToOrder < ActiveRecord::Migration
  def change
    add_reference :orders, :service, index: true, foreign_key: true
    add_column :orders, :start_time, :datetime
    add_column :orders, :end_time, :datetime
  end
end
