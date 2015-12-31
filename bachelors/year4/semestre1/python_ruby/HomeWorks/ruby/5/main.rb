gem 'em-proxy'
require 'em-proxy'
gem 'http_parser.rb'
require 'http/parser'
gem 'uuid'
require 'uuid'

host = '0.0.0.0'
port = 9889
puts "listening on #{host}:#{port}..."

#  PowerShell: wget 'http://google.com' -Proxy 'http://localhost:9889'

Proxy.start(:host => host, :port => port, :debug => true) do |conn|

  session = UUID.generate
  conn.server session, :host => host, :port => (port || 80) #, :bind_host => conn.sock[0] - # for bind ip

  @buffer = ''
  @parser = Http::Parser.new
  @parser.on_headers_complete = proc do |h|
    puts "New session: #{session} (#{h.inspect})"

    host, port = h['Host'].split(':')

    conn.relay_to_servers @buffer

    @buffer.clear
  end

  conn.on_connect do |data, b|
    # puts [:on_connect, data, b].inspect
  end

  conn.on_data do |data|
    # p [:on_data, data]
    @buffer << data
    @parser << data

    data
  end

  conn.on_response do |backend, resp|
    # puts [:on_response, backend, resp].inspect
    resp
  end

  conn.on_finish do |backend, name|
    puts [:on_finish, name].inspect
  end
end