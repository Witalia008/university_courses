class ItemsController < ApplicationController
  before_filter :is_admin, :only => [:new, :create]

  def new
    @group = Group.find(params[:group_id])
    @item = Item.new
  end
  def create
    @group = Group.find(params[:group_id])
    @item = @group.items.create(item_params)
    if @item.save
      notice('valid', 'Item has been added')
      redirect_to group_item_path(@group, @item)
    else
      notice
      render 'new'
    end
  end

  def show
    @group = Group.find(params[:group_id])
    @item = @group.items.find(params[:id])
  end

  protected
  def item_params
    params.require(:item).permit(
        :item_name, :short_descr, :image, :price, :description, :image_alt, :keywords)
  end
end
