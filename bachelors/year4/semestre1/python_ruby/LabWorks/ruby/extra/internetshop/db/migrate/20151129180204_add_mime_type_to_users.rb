class AddMimeTypeToUsers < ActiveRecord::Migration
  def change
    add_column :users, :mime_type, :string
  end
end
