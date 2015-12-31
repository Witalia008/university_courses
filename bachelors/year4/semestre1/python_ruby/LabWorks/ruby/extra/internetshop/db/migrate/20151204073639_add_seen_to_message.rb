class AddSeenToMessage < ActiveRecord::Migration
  def change
    add_column :messages, :seen, :boolean
  end
end
