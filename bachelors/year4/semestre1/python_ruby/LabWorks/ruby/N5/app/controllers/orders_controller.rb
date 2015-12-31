class OrdersController < ApplicationController
  before_filter :authenticated_user, only: [:create, :show, :trolley, :destroy]

  def create
    group = Group.find(params[:group_id])
    item = group.items.find(params[:item_id])
    order = @user.orders.create(:item_id => item.id, :count => params[:count])
    if order.save
      notice('valid', 'Order placed')
    else
      notice
    end
    redirect_to group_item_path(group, item)
  end

  def show
    @orders = @user.orders.where(:pending => false)
    render 'orders/show'
  end

  def trolley
    @pending = true
    @orders = @user.orders.where(:pending => true)
    render 'orders/show'
  end

  def destroy
    @pending = false
    @user.orders.destroy(params[:id])
    redirect_to user_trolley_path(@user)
  end

  def trolley_pay
    @user.orders.where(:pending => true).update_all(:pending => false)
    redirect_to user_orders_path(@user)
  end
end
