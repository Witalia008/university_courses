class CreateArticles < ActiveRecord::Migration
  def change
    create_table :articles do |t|
      t.string :topic
      t.string :text

      t.timestamps null: false
    end
  end
end
