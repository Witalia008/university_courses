require 'net/http'

class ProxyController < ApplicationController
  soap_service namespace: 'urn:WashOut'

  soap_action 'proxy_get',
              :args => :string,
              :return => :string
  def proxy_get
    url = URI.parse(params[:value])
    if url
      logger.debug url.to_s
      req = Net::HTTP::Get.new(url.to_s)
      res = Net::HTTP.start(url.host, url.port) do |http|
        http.request(req)
      end
      logger.debug res.body
      render :soap => res.body.to_s
    else
      logger.debug 'Incorrect URL'
    end
  end
end
