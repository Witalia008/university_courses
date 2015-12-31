json.array!(@banners) do |banner|
  json.extract! banner, :id, :link, :image_link, :priority, :width
  json.url banner_url(banner, format: :json)
end
