class Users::RegistrationsController < Devise::RegistrationsController
# before_filter :configure_sign_up_params, only: [:create]
# before_filter :configure_account_update_params, only: [:update]
  before_action :authenticate_user!, only: [:services, :new_message, :create_message]

  def index
    @customers = User.includes(:customer).where("customers.id IS NOT NULL").references(:customer)
    @workers = User.includes(:worker).where("workers.id IS NOT NULL").references(:worker)
  end

  # GET /resource/sign_up
  def new_customer
    new
  end

  def new_worker
    new
  end

  # POST /resource
  def create_customer
    build_resource(sign_up_params)
    if params[:user][:image]
      resource.image = params[:user][:image].read
      resource.mime_type = params[:user][:image].content_type
    end
    resource.customer = Customer.new(params.require(:user).require(:customer).permit(:full_name))
    resource.is_approved = true

    resource.save
    yield resource if block_given?
    if resource.persisted?
      if resource.active_for_authentication?
        set_flash_message :notice, :signed_up if is_flashing_format?
        sign_up(resource_name, resource)
        respond_with resource, location: after_sign_up_path_for(resource)
      else
        set_flash_message :notice, :"signed_up_but_#{resource.inactive_message}" if is_flashing_format?
        expire_data_after_sign_in!
        respond_with resource, location: after_inactive_sign_up_path_for(resource)
      end
    else
      clean_up_passwords resource
      set_minimum_password_length
      render :action => "new_customer", :object => resource
    end
  end

  def create_worker
    build_resource(sign_up_params)
    if params[:user][:image]
      resource.image = params[:user][:image].read
      resource.mime_type = params[:user][:image].content_type
    end
    resource.worker = Worker.new(params.require(:user).require(:worker).permit(:name, :description))

    resource.save
    yield resource if block_given?
    if resource.persisted?
      if resource.active_for_authentication?
        set_flash_message :notice, :signed_up if is_flashing_format?
        sign_up(resource_name, resource)
        respond_with resource, location: after_sign_up_path_for(resource)
      else
        set_flash_message :notice, :"signed_up_but_#{resource.inactive_message}" if is_flashing_format?
        expire_data_after_sign_in!
        respond_with resource, location: after_inactive_sign_up_path_for(resource)
      end
    else
      clean_up_passwords resource
      set_minimum_password_length
      render :action => "new_worker", :object => resource
    end
  end

  def serve_image
    @user = User.find(params[:id])
    unless @user.image.nil? or @user.mime_type.nil?
      send_data(@user.image, :type => @user.mime_type, :disposition => "inline")
    else

    end
  end

  def show
    @user = User.find(params[:id])
  end

  # GET /resource/edit
  def edit
    super
  end

  # PUT /resource
  def update
    self.resource = resource_class.to_adapter.get!(send(:"current_#{resource_name}").to_key)
    prev_unconfirmed_email = resource.unconfirmed_email if resource.respond_to?(:unconfirmed_email)

    resource_updated = update_resource(resource, account_update_params)
    if resource_updated
      if params[:user][:image]
        resource.image = params[:user][:image].read
        resource.mime_type = params[:user][:image].content_type
      end
      if params[:user].has_key?(:customer)
        resource.customer.update(params.require(:user).require(:customer).permit(:name, :description))
      elsif params[:user].has_key?(:worker)
        resource.worker.update(params.require(:user).require(:worker).permit(:name, :description))
      end
      resource.save
      resource_updated = resource.valid?
    end

    yield resource if block_given?
    if resource_updated
      if is_flashing_format?
        flash_key = update_needs_confirmation?(resource, prev_unconfirmed_email) ?
            :update_needs_confirmation : :updated
        set_flash_message :notice, flash_key
      end
      sign_in resource_name, resource, bypass: true
      respond_with resource, location: after_update_path_for(resource)
    else
      clean_up_passwords resource
      respond_with resource
    end
  end

  def services
    @user = User.find(params[:id])
    @services = Service.where(user_id: @user.id)
    render 'users/registrations/services'
  end

  def new_message
    @message = Message.new
    @messages = Message.where('(sender = ? and receiver = ?) or (sender = ? and receiver = ?)',
                current_user.id, params[:id], params[:id], current_user.id)
    @messages.each do |m|
      if m.receiver == current_user.id
        m.seen = true
        m.save
      end
    end
    render 'users/registrations/message'
  end

  def create_message
    @user = User.find(params[:id])
    message = Message.new(params.require(:message).permit(:content))
    message.sender = current_user.id
    message.receiver = @user.id
    message.save
    redirect_to user_new_message_path(@user)
  end

# DELETE /resource
  # def destroy
  #   super
  # end

  # GET /resource/cancel
  # Forces the session data which is usually expired after sign
  # in to be expired now. This is useful if the user wants to
  # cancel oauth signing in/up in the middle of the process,
  # removing all OAuth session data.
  # def cancel
  #   super
  # end

  # protected

  # If you have extra params to permit, append them to the sanitizer.
  # def configure_sign_up_params
  #   devise_parameter_sanitizer.for(:sign_up)
  # end

  # If you have extra params to permit, append them to the sanitizer.
  # def configure_account_update_params
  #   devise_parameter_sanitizer.for(:account_update) << :attribute
  # end

  # The path used after sign up.
  # def after_sign_up_path_for(resource)
  #   super(resource)
  # end

  # The path used after sign up for inactive accounts.
  # def after_inactive_sign_up_path_for(resource)
  #   super(resource)
  # end
end
