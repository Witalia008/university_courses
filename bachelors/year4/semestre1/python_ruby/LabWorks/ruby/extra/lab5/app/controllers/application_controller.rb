class ApplicationController < ActionController::Base
  # Prevent CSRF attacks by raising an exception.
  # For APIs, you may want to use :null_session instead.
  protect_from_forgery with: :exception

  rescue_from CanCan::AccessDenied do |exception|
    render :file => "#{Rails.root}/public/404.html", :layout => false
  end

  before_action :assign_user
  def assign_user
    if params[:user_id]
      @local_user = User.find(params[:user_id])
    else
      @local_user = current_user
    end
  end

  before_action :configure_permitted_parameters, if: :devise_controller?

  protected
  def configure_permitted_parameters
    devise_parameter_sanitizer.for(:sign_up) do |u|
      u.permit(:username, :email, :password, :password_confirmation, :remember_me)
    end
    devise_parameter_sanitizer.for(:sign_in) do |u|
      u.permit(:login, :username, :email, :password, :remember_me)
    end
    devise_parameter_sanitizer.for(:account_update) do |u|
      u.permit(:username, :email, :password, :password_confirmation, :phone, :skype, :current_password)
    end
  end

  def myself
    current_user && current_user.id == @local_user.id
  end
  def myself_or_admin
    myself || current_user.role == 'ADMIN'
  end
  def myself_or_moderator
    myself_or_admin || current_user.role == 'MODERATOR'
  end
  def can_edit_messages(msg)
    current_user.role == 'ADMIN' or
        current_user.role == 'MODERATOR' and msg.group.creator_id == current_user.id
  end
  helper_method :myself, :myself_or_admin, :myself_or_moderator, :can_edit_messages
end
