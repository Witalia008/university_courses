class CreateArticlesRoles < ActiveRecord::Migration
  def change
    create_table :articles_roles, id: false do |t|
      t.belongs_to :article, index: true
      t.belongs_to :role, index: true
    end
  end
end
