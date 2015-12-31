class ApplicationController < ActionController::Base
  # Prevent CSRF attacks by raising an exception.
  # For APIs, you may want to use :null_session instead.
  protect_from_forgery with: :exception

  protected
  def authenticate_user
    if session[:user_id]
      @current_user = User.find(session[:user_id])
      return true
    else
      redirect_to(:controller => 'sessions', :action => 'login')
      return false
    end
  end
  def save_login_state
    if session[:user_id]
      redirect_to(:controller => 'sessions', :action => 'home')
      return false
    else
      return true
    end
  end
  def user_admin(tp=['ADMIN'])
    if session[:user_id]
      @current_user = User.find(session[:user_id])
      if tp.include? @current_user.role.role_name
        return true
      else
        redirect_to(:controller => 'sessions', :action => 'home')
        return false
      end
    else
      redirect_to(:controller => 'sessions', :action => 'login')
    end
  end
  def moderate_user
    user_admin(%w(ADMIN MODERATOR))
  end
end
