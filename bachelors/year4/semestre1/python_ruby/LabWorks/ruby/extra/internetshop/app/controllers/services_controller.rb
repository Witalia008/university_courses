require 'date'

class ServicesController < ApplicationController
  before_action :set_service, only: [:show, :edit, :update, :destroy, :buy, :order]
  # before_action :init_session
  before_action :authenticate_user!, except: [:index, :show]
  before_filter :check_worker, only: [:new, :edit, :create, :update, :destroy]
  before_filter :check_customer, only: [:buy, :order]

  # GET /services
  # GET /services.json
  def index
    @nannies = Service.where(service_type: :nanny)
  end

  # GET /services/1
  # GET /services/1.json
  def show
  end

  def date_of_prev(day)
    date = Date.parse(day)
    delta = date > Date.today ? 7 : 0
    date - delta
  end

  # GET /services/new
  def new
    @service = Service.new
  end

  # GET /services/1/edit
  def edit
  end

  # POST /services
  # POST /services.json
  def create
    @service = Service.new(service_params)
    @service.user_id = current_user.id
    @service.create_nanny(nanny_params)

    respond_to do |format|
      if @service.save
        format.html { redirect_to @service, notice: 'Service was successfully created.' }
        format.json { render :show, status: :created, location: @service }
      else
        format.html { render :new }
        format.json { render json: @service.errors, status: :unprocessable_entity }
      end
    end
  end

  # PATCH/PUT /services/1
  # PATCH/PUT /services/1.json
  def update
    respond_to do |format|
      if @service.update_nanny(nanny_params) and @service.update(service_params)
        format.html { redirect_to @service, notice: 'Service was successfully updated.' }
        format.json { render :show, status: :ok, location: @service }
      else
        format.html { render :edit }
        format.json { render json: @service.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /services/1
  # DELETE /services/1.json
  def destroy
    @service.destroy
    respond_to do |format|
      format.html { redirect_to request.referer, notice: 'Service was successfully destroyed.' }
      format.json { head :no_content }
    end
  end

  # def add_to_cart
  #   item = OrderItem.new(params.require(:order_item).permit(:start_time, :end_time))
  #   session[:carts][current_user.id.to_s] << [@service.id, item.start_time, item.end_time]
  #   redirect_to carts_edit_path
  # end
  #
  # def remove_from_cart
  #   session[:carts][current_user.id.to_s].slice!(
  #       session[:carts][current_user.id.to_s].index{|item| item[0] == @service.id})
  #   redirect_to carts_edit_path
  # end

  def buy
    @order = Order.new
    @order.service_id = @service.id
    @orders = Order.all
  end

  def order
    logger.debug(params)
    @order = Order.new(order_params)
    @order.user_id = current_user.id
    @order.service_id = @service.id
    @order.create_nanny(order_nanny_params)

    if request.format.js?
      respond_to do |format|
        format.js { }
      end
    else
      respond_to do |format|
        if @order.save
          format.html { redirect_to @order, notice: 'Order was successfully created.' }
          format.json { render :show, status: :created, location: @order }
        else
          format.html { render :new }
          format.json { render json: @order.errors, status: :unprocessable_entity }
        end
      end
    end
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_service
      @service = Service.find(params[:id])
    end

    # Never trust parameters from the scary internet, only allow the white list through.
    def service_params
      params.require(:service).permit(:service_type, :description)
    end

    def nanny_params
      params.require(:service).permit(:max_children, price: [])
    end

    def order_params
      params.require(:order).permit(:start_time, :end_time)
    end

    def order_nanny_params
      params.require(:order).permit(:children)
    end

    # def init_session
    #   unless current_user.nil?
    #     if session[:carts].nil?
    #       session[:carts] = {}
    #     end
    #     if session[:carts][current_user.id.to_s].nil?
    #       session[:carts][current_user.id.to_s] = []
    #     end
    #   end
    # end
  end
