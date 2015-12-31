class RemoveTypeFromWorker < ActiveRecord::Migration
  def change
    remove_column :workers, :type, :string
  end
end
