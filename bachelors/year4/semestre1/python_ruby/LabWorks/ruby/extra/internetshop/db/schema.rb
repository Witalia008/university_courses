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

ActiveRecord::Schema.define(version: 20151212151625) do

  # These are extensions that must be enabled in order to support this database
  enable_extension "plpgsql"

  create_table "admin_messages", force: :cascade do |t|
    t.integer  "user_id"
    t.text     "content"
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
    t.text     "answer"
  end

  add_index "admin_messages", ["user_id"], name: "index_admin_messages_on_user_id", using: :btree

  create_table "banners", force: :cascade do |t|
    t.string   "link"
    t.string   "image_link"
    t.integer  "priority"
    t.integer  "width"
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
    t.integer  "height"
  end

  create_table "customers", force: :cascade do |t|
    t.string   "full_name"
    t.integer  "user_id"
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
  end

  add_index "customers", ["user_id"], name: "index_customers_on_user_id", using: :btree

  create_table "messages", force: :cascade do |t|
    t.integer  "sender"
    t.integer  "receiver"
    t.text     "content"
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
    t.boolean  "seen"
  end

  create_table "news_items", force: :cascade do |t|
    t.string   "title"
    t.text     "content"
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
  end

  create_table "order_float_parameters", force: :cascade do |t|
    t.string   "name"
    t.float    "value"
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
    t.integer  "order_id"
  end

  create_table "orders", force: :cascade do |t|
    t.integer  "user_id"
    t.datetime "created_at",  null: false
    t.datetime "updated_at",  null: false
    t.integer  "service_id"
    t.datetime "start_time"
    t.datetime "end_time"
    t.boolean  "is_approved"
  end

  add_index "orders", ["service_id"], name: "index_orders_on_service_id", using: :btree
  add_index "orders", ["user_id"], name: "index_orders_on_user_id", using: :btree

  create_table "service_float_parameters", force: :cascade do |t|
    t.integer  "service_id"
    t.string   "name"
    t.float    "value"
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
  end

  add_index "service_float_parameters", ["service_id"], name: "index_service_float_parameters_on_service_id", using: :btree

  create_table "service_string_parameters", force: :cascade do |t|
    t.integer  "service_id"
    t.string   "name"
    t.string   "value"
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
  end

  add_index "service_string_parameters", ["service_id"], name: "index_service_string_parameters_on_service_id", using: :btree

  create_table "services", force: :cascade do |t|
    t.string   "name"
    t.text     "description"
    t.float    "price"
    t.datetime "created_at",   null: false
    t.datetime "updated_at",   null: false
    t.integer  "user_id"
    t.string   "service_type"
  end

  add_index "services", ["user_id"], name: "index_services_on_user_id", using: :btree

  create_table "users", force: :cascade do |t|
    t.string   "email",                  default: "",    null: false
    t.string   "encrypted_password",     default: "",    null: false
    t.string   "reset_password_token"
    t.datetime "reset_password_sent_at"
    t.datetime "remember_created_at"
    t.integer  "sign_in_count",          default: 0,     null: false
    t.datetime "current_sign_in_at"
    t.datetime "last_sign_in_at"
    t.inet     "current_sign_in_ip"
    t.inet     "last_sign_in_ip"
    t.datetime "created_at",                             null: false
    t.datetime "updated_at",                             null: false
    t.boolean  "is_admin"
    t.boolean  "is_approved",            default: false
    t.binary   "image"
    t.string   "mime_type"
  end

  add_index "users", ["email"], name: "index_users_on_email", unique: true, using: :btree
  add_index "users", ["reset_password_token"], name: "index_users_on_reset_password_token", unique: true, using: :btree

  create_table "workers", force: :cascade do |t|
    t.string   "name"
    t.text     "description"
    t.integer  "user_id"
    t.datetime "created_at",  null: false
    t.datetime "updated_at",  null: false
  end

  add_index "workers", ["user_id"], name: "index_workers_on_user_id", using: :btree

  add_foreign_key "admin_messages", "users"
  add_foreign_key "customers", "users"
  add_foreign_key "messages", "users", column: "receiver", on_delete: :cascade
  add_foreign_key "messages", "users", column: "sender", on_delete: :cascade
  add_foreign_key "order_float_parameters", "orders"
  add_foreign_key "orders", "services"
  add_foreign_key "orders", "users"
  add_foreign_key "service_float_parameters", "services"
  add_foreign_key "service_string_parameters", "services"
  add_foreign_key "services", "users"
  add_foreign_key "workers", "users"
end
