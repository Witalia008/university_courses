RailsAdmin.config do |config|

  ### Popular gems integration

  ## == Devise ==
  # config.authenticate_with do
  #   warden.authenticate! scope: :user
  # end
  # config.current_user_method(&:current_user)

  ## == Cancan ==
  # config.authorize_with :cancan

  ## == Pundit ==
  # config.authorize_with :pundit

  ## == PaperTrail ==
  # config.audit_with :paper_trail, 'User', 'PaperTrail::Version' # PaperTrail >= 3.0.0

  ### More at https://github.com/sferik/rails_admin/wiki/Base-configuration

  config.authorize_with do
    logger.debug(session.inspect)
    logger.debug(session[:user_id])
    if session[:user_id]
      user = User.find(session[:user_id])
      if user.role.rolename != 'ADMIN'
        redirect_to home_path
      end
    else
      authenticate_or_request_with_http_basic('Site Message') do |username, password|
        user = User.authenticate(username, password)
        if user && user.role.rolename == 'ADMIN'
          session[:user_id] = user.id
        end
        false
      end
    end
  end

  config.actions do
    dashboard                     # mandatory
    index                         # mandatory
    new
    export
    bulk_delete
    show
    edit
    delete
    show_in_app

    ## With an audit adapter, you can add:
    # history_index
    # history_show
  end
end
