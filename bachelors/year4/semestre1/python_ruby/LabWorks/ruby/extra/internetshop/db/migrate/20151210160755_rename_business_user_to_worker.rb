class RenameBusinessUserToWorker < ActiveRecord::Migration
  def change
    rename_table :business_users, :workers
  end
end
