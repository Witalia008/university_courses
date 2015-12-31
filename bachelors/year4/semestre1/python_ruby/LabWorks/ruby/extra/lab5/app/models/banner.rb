class Banner < ActiveRecord::Base
  belongs_to :group

  mount_uploader :image, PuctureUploader
  validates_presence_of :image, :group_id

  URL_PATTERN = /\A(https?:\/\/)([\da-z\.-]+)\.([a-z\.]{2,6})([\/\w \.-]*)*\/?\z/
  validates_format_of :url, :with => URL_PATTERN
end
