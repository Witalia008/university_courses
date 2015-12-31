# encoding: UTF-8
# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# Note that this schema.rb definition is the authoritative source for your
# database schema. If you need to create the application database on another
# system, you should be using db:schema:load, not running all the migrations
# from scratch. The latter is a flawed and unsustainable approach (the more migrations
# you'll amass, the slower it'll run and the greater likelihood for issues).
#
# It's strongly recommended that you check this file into your version control system.

ActiveRecord::Schema.define(version: 20151114085212) do

  # These are extensions that must be enabled in order to support this database
  enable_extension "plpgsql"

  create_table "groups", force: :cascade do |t|
    t.string   "group_name"
    t.string   "image"
    t.string   "description"
    t.datetime "created_at",  null: false
    t.datetime "updated_at",  null: false
    t.integer  "parent_id"
    t.string   "image_alt"
    t.string   "keywords"
  end

  create_table "items", force: :cascade do |t|
    t.string   "item_name"
    t.string   "short_descr"
    t.string   "image"
    t.float    "price"
    t.string   "description"
    t.integer  "group_id"
    t.datetime "created_at",  null: false
    t.datetime "updated_at",  null: false
    t.string   "image_alt"
    t.string   "keywords"
  end

  add_index "items", ["group_id"], name: "index_items_on_group_id", using: :btree

  create_table "news", force: :cascade do |t|
    t.string   "header"
    t.string   "preview"
    t.string   "image"
    t.string   "full_text"
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
    t.string   "image_alt"
    t.string   "keywords"
  end

  create_table "orders", force: :cascade do |t|
    t.integer  "user_id"
    t.integer  "item_id"
    t.integer  "count"
    t.float    "price"
    t.boolean  "pending"
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
  end

  add_index "orders", ["item_id"], name: "index_orders_on_item_id", using: :btree
  add_index "orders", ["user_id"], name: "index_orders_on_user_id", using: :btree

  create_table "roles", force: :cascade do |t|
    t.string   "rolename"
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
  end

  create_table "users", force: :cascade do |t|
    t.string   "username"
    t.string   "email"
    t.string   "encrypted_password"
    t.string   "salt"
    t.integer  "role_id"
    t.datetime "created_at",         null: false
    t.datetime "updated_at",         null: false
  end

  add_index "users", ["role_id"], name: "index_users_on_role_id", using: :btree

  add_foreign_key "groups", "groups", column: "parent_id"
  add_foreign_key "items", "groups"
  add_foreign_key "orders", "items"
  add_foreign_key "orders", "users"
  add_foreign_key "users", "roles"
end
