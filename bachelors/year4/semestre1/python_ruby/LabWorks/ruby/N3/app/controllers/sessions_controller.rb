class SessionsController < ApplicationController
  before_filter :authenticated_user, :only => [:home, :profile, :setting]
  before_filter :save_login_state, :only => [:login, :login_attempt]

  def login
  end
  def login_attempt
    logger.debug 'sessions#login_attempt'
    authorized_user = User.authenticate(params[:username_or_email], params[:login_password])
    if authorized_user
      # logger.debug("#{authorized_user.username} logged successfully")
      session[:user_id] = authorized_user.id
      flash[:notice] = I18n.t :login_welcome, user: authorized_user.username
      redirect_to(:action => 'home')
    else
      # logger.debug("#{authorized_user.username} entered incorrect password")
      flash[:notice] = I18n.t :invalid_credentials
      flash[:colour] = 'invalid'
      render 'login'
    end
  end

  def logout
    logger.debug "#{session[:user_id]} Logged out"
    session[:user_id] = nil
    redirect_to(:action => 'login')
  end

  def home
    @user = User.find(session[:user_id])
    @is_admin = @user.role.rolename == 'ADMIN'
  end

  def profile
  end

  def setting
  end
end
