class GroupsController < ApplicationController
  before_action :authenticate_user!, :only => [:new, :edit, :create, :update,
                                               :destroy, :join, :leave]
  before_filter(:only => [:edit, :update, :destroy]) { |c|
    redirect_to groups_path unless myself_or_moderator
  }

  before_filter(:only => [:new, :create]) { |c|
    redirect_to groups_path unless myself
  }



  def index
    @owned = @local_user.groups_created
    @groups = @local_user.groups.all
  end

  def new
    @group = Group.new
  end

  def edit
    @group = Group.find(params[:id])
  end

  def create
    @group = Group.new(group_params)
    @group.creator_id = current_user.id
    if @group.save
      redirect_to group_path(@local_user, @group)
    else
      render 'new'
    end
  end

  def update
    @group = Group.find(params[:id])
    @group.update(group_params)
    if @group.save
      redirect_to group_path(@local_user, @group)
    else
      render 'edit'
    end
  end

  def destroy
    @group = Group.find(params[:id])
    @group.destroy
    redirect_to groups_path(@local_user)
  end

  def show
    @group = Group.find(params[:id])
    @messages = Message.where(:group_id => @group.id)
    @message = Message.new
  end

  def join
    group = Group.find(params[:group_id])
    current_user.groups << group
    group.users << current_user
    redirect_to groups_path(current_user)
  end

  def leave
    group = Group.find(params[:group_id])
    current_user.groups.delete(group)
    group.users.delete(current_user)
    redirect_to groups_path(current_user)
  end

  protected
  def group_params
    params.require(:group).permit(:group_name, :open)
  end
end
