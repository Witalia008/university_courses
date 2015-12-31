require 'redis'
require 'open-uri'
require 'json'
require 'active_support/core_ext'

require File.expand_path('../application',  __FILE__)
Rhw4::Application.initialize!

# Development middlewares
if Rhw4::Application.env == 'development'
  use AsyncRack::CommonLogger

  # Enable code reloading on every request
  use Rack::Reloader, 0

  # Serve assets from /public
  use Rack::Static, :urls => ["/javascripts"], :root => Rhw4::Application.root(:public)
end

# Running thin :
#
#   bundle exec thin --max-persistent-conns 1024 --timeout 0 -R config.ru start
#
# Vebose mode :
#
#   Very useful when you want to view all the data being sent/received by thin
#
#   bundle exec thin --max-persistent-conns 1024 --timeout 0 -V -R config.ru start
#
run Rhw4::Application.routes
