class UsersController < ApplicationController
  before_filter :save_login_state, :only => [:new, :create]
  # before_filter :is_admin, :only => [:show]

  def new
    @user = User.new
  end

  def create
    @user = User.new(user_params)
    if @user.save
      notice('valid', 'Registration successful')
      redirect_to(:controller => 'sessions', :action => 'login')
    else
      notice
      render 'new'
    end
  end

  def show
    @user = User.find(session[:user_id])
  end

  private
  def user_params
    params.require(:user).permit(:username, :email, :password, :password_confirm)
  end
end
