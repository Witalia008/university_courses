class MessagesController < ApplicationController
  before_filter(:only => [:index, :edit, :update, :destroy]) { |c|
    if params[:group_id]
      group = Group.find(params[:group_id])
      redirect_to group_path(group) unless current_user.id == @local_user.id ||
          current_user.role == 'ADMIN' ||
          current_user.role == 'MODERATOR' && group.creator_id == current_user.id
    else
      redirect_to profile_path(@local_user) unless myself
    end
  }

  def index
    @messages = current_user.messages.where(:group_id => nil) +
        Message.where(to_id: current_user.id, group_id: nil)
  end
  def new
    @message = Message.new
    logger.debug(params)
    @to = User.find(params[:to_id]) if params[:to_id]
  end
  def create
    @message = current_user.messages.create(message_params)
    if @message.save
      if @message.group
        redirect_to group_path(@local_user, @message.group)
      else
        # TODO: somewhere else, I believe
        redirect_to profile_path(current_user)
      end
    else
      @group = @message.group
      render 'new'
    end
  end

  def edit
    @message = Message.find(params[:id])
  end
  def update
    @message = Message.find(params[:id])
    @message.update(message_params)
    if @message.save
      if @message.group
        redirect_to group_path(@local_user, @message.group)
      else
        # TODO: somewhere else, I believe
        redirect_to profile_path(@local_user)
      end
    else
      @group = @message.group
      render 'edit'
    end
  end

  def destroy
    @message = @local_user.messages.find(params[:id])
    @message.destroy
    if @message.group
      redirect_to group_path(@local_user, @message.group)
    else
      redirect_to profile_path(@message.from)
    end
  end

  protected
  def message_params
    params.require(:message).permit(:from_id, :to_id, :text, :group_id)
  end
end
