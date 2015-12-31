# This file should contain all the record creation needed to seed the database with its default values.
# The data can then be loaded with the rake db:seed (or created alongside the db with db:setup).
#
# Examples:
#
#   cities = City.create([{ name: 'Chicago' }, { name: 'Copenhagen' }])
#   Mayor.create(name: 'Emanuel', city: cities.first)

admin = User.create(
    email: 'admin@example.com',
    username: 'admin',
    password: 'admin',
    role: 'ADMIN'
)
moderator = User.create(
    email: 'moderator@example.com',
    username: 'moderator',
    password: 'moderator',
    role: 'MODERATOR'
)
user = User.create(
    email: 'user@example.com',
    username: 'user',
    password: 'password',
    role: 'USER'
)