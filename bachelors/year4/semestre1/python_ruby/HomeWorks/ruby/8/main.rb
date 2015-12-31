require 'rubygems'
gem 'nokogiri'
require 'nokogiri'
require 'rexml/document'
require 'rexml/streamlistener'
gem 'prawn'
gem 'prawn-table'
require 'prawn'
require 'prawn/table'
include REXML


# Validation against XSD

def validate(document_path, schema_path)
  schema = Nokogiri::XML::Schema(File.read(schema_path))
  document = Nokogiri::XML(File.read(document_path))
  schema.validate(document)
end

validate('OldCards.xml', 'OldCards.xsd').each do |error|
  puts error.message
end


# Class Definitions

class OldCards
  def initialize
    @cards = []
  end

  attr_accessor :cards

  def to_s
    @cards.map { |x| x.to_s }.join
  end
end

class Card
  def initialize
    @authors = []
  end

  attr_accessor :id
  attr_accessor :theme
  attr_accessor :type
  attr_accessor :country
  attr_accessor :year
  attr_accessor :authors
  attr_accessor :valuable

  def to_s
    "Card {#{id}, #{theme}, #{type}, #{country}, #{year}, #{authors}, #{valuable}}\n"
  end
end


# DOM Parser

def parse_card(elem)
  card = Card.new
  card.id = elem.attributes['id']
  elem.each_child do |child|
    if child.node_type == :element
      case child.name
        when 'theme'
          card.theme = child.text.to_sym
        when 'type'
          card.type = child.text.to_sym
        when 'country'
          card.country = child.text
        when 'year'
          card.year = child.text
        when 'valuable'
          card.valuable = child.text.to_sym
        when 'author'
          card.authors << child.text
        else
          # puts 'blah-blah'
      end
    end
  end
  card
end

def parse_cards(root)
  cards = OldCards.new
  root.each_child do |child|
    if child.node_type == :element
      cards.cards << parse_card(child)
    end
  end
  cards
end

xmlfile = File.new('OldCards.xml')
xmldoc = Document.new(xmlfile)

root = xmldoc.root
cards = parse_cards(root)

# Save as PDF

Prawn::Document.generate('hello.pdf') do
  cards.cards.each do |card|
    table([
              [{:content => card.id, :colspan => 2, :background_color => 'FFFFCC'}],
              ['Theme', card.theme.to_s],
              ['Type', card.type.to_s],
              ['Country', card.country],
              ['Year', card.year],
              ['Authors', card.authors.size > 0 ? card.authors.join(', ') : 'Unknown'],
              ['Valuable', card.valuable.to_s]
          ], :column_widths => {1 => 100})
    move_down 20
  end
end