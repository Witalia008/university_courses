json.array!(@messages) do |message|
  json.extract! message, :id, :sender, :receiver, :content
  json.url message_url(message, format: :json)
end
