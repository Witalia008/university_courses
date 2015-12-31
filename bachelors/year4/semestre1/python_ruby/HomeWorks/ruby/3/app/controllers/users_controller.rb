class UsersController < ApplicationController
  before_filter :user_admin, :only => [:index, :edit_role]

  def index
    @users = User.all
  end

  def new
    @user = User.new
  end

  def create
    @user = User.new(user_params)
    if @user.save
      logger.debug "Registered #{@user.username}"
      redirect_to login_path
    else
      render 'new'
    end
  end

  def edit_role
    @user = User.find(params[:user_id])
    @user.update(:role_id => params[:role][:id])
    logger.debug "Edit role #{params}"
    redirect_to users_path
  end

  private
  def user_params
    params.require(:user).permit(:username, :email, :password, :password_confirmation)
  end
end
