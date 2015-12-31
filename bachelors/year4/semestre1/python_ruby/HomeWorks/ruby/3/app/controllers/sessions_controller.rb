class SessionsController < ApplicationController
  before_filter :authenticate_user, :only => :home
  before_filter :save_login_state, :only => [:login, :login_attempt]

  def login
  end
  def login_attempt
    logger.debug 'sessions#login_attempt'
    authorized_user = User.authenticate(params[:username_or_email], params[:login_password])
    if authorized_user
      session[:user_id] = authorized_user.id
      flash[:notice] = "Logged successfully as #{authorized_user.username}"
      flash[:colour] = :valid
      redirect_to(:action => 'home')
    else
      flash[:notice] = 'Login or password incorrect'
      flash[:colour] = :invalid
      render 'login'
    end
  end

  def logout
    session[:user_id] = nil
    redirect_to(:action => 'login')
  end

  def home
    @user = User.find(session[:user_id])
    @is_admin = @user.role.role_name == 'ADMIN'
  end
end
