class Item < ActiveRecord::Base
  @per_page = 2

  mount_uploader :image, PictureUploader

  belongs_to :group

  validates :item_name, :image, :image_alt,
            :short_descr, :price,
            :description, :group_id, :keywords,
            :presence => true

  validates_length_of :item_name, :minimum => 5
  validates :short_descr, :length => {:in => 5..50}
  validates :price, :numericality => {:greater_than => 0}
  validates_length_of :description, :minimum => 10

  searchable do
    text :item_name, boost: 5.0
    text :keywords, boost: 6.0
    text :description, boost: 4.0
    text :image_alt, boost: 1.0
  end
end
