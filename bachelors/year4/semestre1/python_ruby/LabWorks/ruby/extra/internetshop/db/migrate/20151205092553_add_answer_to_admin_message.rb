class AddAnswerToAdminMessage < ActiveRecord::Migration
  def change
    add_column :admin_messages, :answer, :text
  end
end
