class Service < ActiveRecord::Base
  TYPE_OPTIONS = ['nanny']
  TYPE_OPTION_NAMES = [['Nanny', 'nanny']]
  TYPE_OPTION_MAP = {'nanny' => 'Nanny'}

  belongs_to :user
  belongs_to :category

  has_many :service_string_parameters, dependent: :destroy
  has_many :service_float_parameters, dependent: :destroy
  has_many :orders, dependent: :destroy

  validates_inclusion_of :service_type, in: TYPE_OPTIONS

  def service_name
    Service::TYPE_OPTION_MAP[service_type]
  end

  def is_nanny
    service_type == 'nanny'
  end

  def create_nanny(params)
    service_float_parameters << ServiceFloatParameter.new(name: :max_children, value: params[:max_children])
    prices = params[:price]
    prices.each_with_index do |price, i|
      service_float_parameters << ServiceFloatParameter.new(
          name: 'price_' + (i+1).to_s, value: price.to_i
      )
    end
  end

  def update_nanny(params)
    with_transaction_returning_status do
      service_float_parameters.where(name: :max_children).first.update_attribute(:value, params[:max_children])
      prices = params[:price]
      prices.each_with_index do |price, i|
        p = service_float_parameters.where(name: 'price_' + (i+1).to_s).first
        if p.nil?
          service_float_parameters << ServiceFloatParameter.new(
              name: 'price_' + (i+1).to_s, value: price.to_i
          )
        else
          p.update_attribute(:value, price.to_i)
        end
      end
    end
  end

  def nanny
    if @nanny.nil?
      @nanny = Nanny.new(self)
    end
    @nanny
  end

end


class Nanny
  attr_accessor :price
  attr_accessor :max_children

  def initialize(service)
    max_children = service.service_float_parameters.where(name: :max_children).first
    if max_children.nil?
      @max_children = 1
    else
      @max_children = max_children.value.to_i
    end
    @price = []
    for i in 1..@max_children
      price = service.service_float_parameters.where(name: 'price_' + i.to_s).first
      if price.nil?
        @price << 100.0
      else
        @price << price.value
      end
    end
  end
end
