class AddIsApprovedToOrder < ActiveRecord::Migration
  def change
    add_column :orders, :is_approved, :boolean
  end
end
