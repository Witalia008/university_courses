class ApplicationController < ActionController::Base
  before_filter :var_assign

  def var_assign
    @message = Message.new
    @groups_top = Group.where(:parent_id => nil)
    if session[:user_id]
      @user = User.find(session[:user_id])
      @is_admin = @user.role.rolename == 'ADMIN' if @user != nil
    end
  end

  def notice(colour='invalid', message='Something went wrong')
    flash[:colour] = colour
    flash[:notice] = message
  end

  # Prevent CSRF attacks by raising an exception.
  # For APIs, you may want to use :null_session instead.
  protect_from_forgery with: :exception

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
