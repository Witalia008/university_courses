class Order < ActiveRecord::Base
  belongs_to :user
  belongs_to :service
  has_many :order_float_parameters, dependent: :destroy

  def price_proxy
    if is_nanny
      children = order_float_parameters[0].value.to_i
      service.nanny.price[children - 1] * ((end_time - start_time) / 3600)
    end
  end

  def price
    if is_nanny
      service.nanny.price[nanny.children - 1] * ((end_time - start_time) / 3600)
    end
  end

  def to_s
    'hello'
  end

  def is_nanny
    service.is_nanny
  end

  def create_nanny(params)
    order_float_parameters.build({name: :children, value: params[:children].to_f})
  end

  def update_nanny(params)
  end

  def nanny
    if @nanny.nil?
      @nanny = OrderNanny.new(self)
    end
    @nanny
  end
end


class OrderNanny
  attr_accessor :children

  def initialize(order)
    children = order.order_float_parameters.where(name: :children).first
    if children.nil?
      @children = 1
    else
      @children = children.value.to_i
    end
  end
end
