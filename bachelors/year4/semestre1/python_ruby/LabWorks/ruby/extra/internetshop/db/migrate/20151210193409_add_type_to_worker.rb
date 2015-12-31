class AddTypeToWorker < ActiveRecord::Migration
  def change
    add_column :workers, :type, :string
  end
end
