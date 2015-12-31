class UsersController < ApplicationController
  before_filter :save_login_state, :only => [:new, :create]
  before_filter :is_admin, :only => [:show]

  def new
    @user = User.new
  end

  def create
    @user = User.new(user_params)
    if @user.save
      redirect_to(:controller => 'sessions', :action => 'login')
    else
      render 'new'
    end
  end

  def show
    role_user = Role.find_by_rolename('USER')
    @users = []
    User.where(role_id: role_user.id).find_each do |user|
      @users << user
    end
  end

  private
  def user_params
    params.require(:user).permit(:username, :email, :password, :password_confirm)
  end
end
