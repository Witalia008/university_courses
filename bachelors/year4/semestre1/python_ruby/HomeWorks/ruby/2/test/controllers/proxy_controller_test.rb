require 'test_helper'
require 'savon'

class ProxyControllerTest < ActionController::TestCase
  test 'Test SOAP Proxy' do
    client = Savon::Client.new(wsdl: 'http://localhost:3000/proxy/wsdl')
    result = client.call(:proxy_get, message: {:value => 'http://google.com'})
    response = result.to_hash[:proxy_get_response][:value]
    puts response
  end
end
