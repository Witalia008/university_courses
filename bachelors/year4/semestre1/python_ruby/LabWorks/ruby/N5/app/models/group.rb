class Group < ActiveRecord::Base
  mount_uploader :image, PictureUploader

  belongs_to  :parent,
              :foreign_key => 'parent_id',
              :class_name => 'Group'

  has_many    :children,
              :foreign_key => 'parent_id',
              :class_name => 'Group',
              :dependent => :delete_all

  has_many :items

  validates :group_name, :image, :image_alt, :keywords, :description, :presence => true
  validates_length_of :group_name, :minimum => 5
  validates_length_of :description, :minimum => 10

  searchable do
    text :group_name, boost: 5.0
    text :keywords, boost: 6.0
    text :description, boost: 4.0
    text :image_alt, boost: 1.0
  end
end
