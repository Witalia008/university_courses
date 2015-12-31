require 'rubygems'
gem 'nokogiri'
require 'nokogiri'
require 'rexml/document'
require 'rexml/streamlistener'
include REXML



# Validation against XSD

def validate(document_path, schema_path, root_element)
  schema = Nokogiri::XML::Schema(File.read(schema_path))
  document = Nokogiri::XML(File.read(document_path))
  schema.validate(document)
end

validate('OldCards.xml', 'OldCards.xsd', 'OldCards').each do |error|
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
cards.cards.sort_by! { |obj| obj.year }
print cards, "\n"



# SAX Parser

class MyListener
  def initialize
    @cards = OldCards.new
  end
  attr_accessor :cards

  include REXML::StreamListener
  def tag_start(element, attributes)
    if element == 'card'
      @card = Card.new
      @card.id = attributes['id']
    end
  end
  def tag_end(element)
    case element
      when 'card'
        @cards.cards << @card
      when 'theme'
        @card.theme = @content.to_sym
      when 'type'
        @card.type = @content.to_sym
      when 'country'
        @card.country = @content
      when 'year'
        @card.year = @content
      when 'valuable'
        @card.valuable = @content.to_sym
      when 'author'
        @card.authors << @content
      else
        #puts "Unexpected tag #{element}"
    end
  end
  def text(data)
    return if data =~ /^\s*$/
    @content = data.to_s
  end
end

list = MyListener.new
xmlfile = File.new('OldCards.xml')
Document.parse_stream(xmlfile, list)
list.cards.cards.sort!  { |a, b| a.id <=> b.id }
print list.cards