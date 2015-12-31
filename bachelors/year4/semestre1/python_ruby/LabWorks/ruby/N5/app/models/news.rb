class News < ActiveRecord::Base
  mount_uploader :image, PictureUploader

  validates :header, :preview, :image, :image_alt, :full_text, :keywords,
            :presence => true

  validates_length_of :header, :minimum => 5
  validates_length_of :preview, :minimum => 5
  validates_length_of :full_text, :minimum => 10
  validates_length_of :image_alt, :minimum => 5
  validates_length_of :keywords, :minimum => 5

  searchable do
    text :header, boost: 5.0
    text :keywords, boost: 6.0
    text :full_text, boost: 4.0
    text :image_alt, boost: 1.0
  end
end
