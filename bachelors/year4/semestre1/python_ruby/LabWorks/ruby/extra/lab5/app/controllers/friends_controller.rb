class FriendsController < ApplicationController
  before_action :authenticate_user!, :only => [:index, :add, :remove]

  def index
    @friends = @local_user.users
  end

  def add
    if @local_user.id != current_user.id
      @local_user.users << current_user
      current_user.users << @local_user
    end
    redirect_to friends_path(current_user)
  end

  def remove
    @local_user.users.delete(current_user)
    current_user.users.delete(@local_user)
    redirect_to friends_path(current_user)
  end
end
