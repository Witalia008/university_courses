class ApplicationController < ActionController::Base
  before_action :set_locale, :set_vars

  def set_locale
    I18n.locale = params[:locale] || I18n.default_locale
  end

  def set_vars
    if session[:user_id]
      @user = User.find(session[:user_id])
    end
  end

  def default_url_options(options = {})
    { locale: I18n.locale }.merge options
  end

  # Prevent CSRF attacks by raising an exception.
  # For APIs, you may want to use :null_session instead.
  protect_from_forgery with: :exception

  # allow if user is admin, otherwise redirect to login page
  def is_admin
    if session[:user_id]
      user = User.find(session[:user_id])
      if user.role.rolename == 'ADMIN'
        return true
      else
        redirect_to(:controller => 'sessions', :action => 'home')
      end
    else
      redirect_to(:controller => 'sessions', :action => 'login')
    end
    return false
  end
  # access will be granted only if this belongs to me or I am an admin
  def myself_or_admin
    @current_user = User.find(session[:user_id])
    @user = User.find(params[:user_id])
    if @user.id == @current_user.id || @current_user.role.rolename == 'ADMIN'
      logger.debug '    granted'
      return true
    else
      logger.debug '    refused'
      redirect_to(:controller => 'sessions', :action => 'home')
      return false
    end
  end
  protected
  # if not authenticated - redirect to login page
  def authenticated_user
    if session[:user_id]
      @current_user = User.find(session[:user_id])
      return true
    else
      redirect_to(:controller => 'sessions', :action => 'login')
      return false
    end
  end
  # if not authenticated - allow page render
  def save_login_state
    if session[:user_id]
      redirect_to(:controller => 'sessions', :action => 'home')
      return false
    else
      return true
    end
  end
end
