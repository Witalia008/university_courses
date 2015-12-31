class RenamePrivateUserToCustomer < ActiveRecord::Migration
  def change
    rename_table :private_users, :customers
  end
end
