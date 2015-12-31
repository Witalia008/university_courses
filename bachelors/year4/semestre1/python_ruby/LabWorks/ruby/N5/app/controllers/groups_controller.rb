class GroupsController < ApplicationController
  before_filter :is_admin, :only => [:new, :create]
  before_filter :authenticated_user

  def new
    @group = Group.new
  end
  def create
    if params[:group_id]
      parent = Group.find(params[:group_id])
      @group = parent.children.create(group_params)
    else
      @group = Group.new(group_params)
    end

    if @group.save
      notice('valid', 'Group has been added')
      redirect_to group_path(@group)
    else
      notice
      render 'new'
    end
  end

  def show
    @group = Group.find(params[:id])
    @items = @group.items.paginate(:page => params[:page])
  end

  protected
  def group_params
    params.require(:group).permit(
        :group_name, :image, :description, :parent_id, :image_alt, :keywords)
  end
end
