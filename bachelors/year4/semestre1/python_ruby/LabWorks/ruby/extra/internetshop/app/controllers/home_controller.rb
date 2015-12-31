class HomeController < ApplicationController
  before_filter :check_admin, only: [:backup]

  def index
    @news = NewsItem.order(:created_at => :desc).all
    @banners = Banner.all
  end

  def backup
    #system("echo '' | sudo -HS -u postgres bash -c 'pg_dump postgres > ~/out.txt'")
    system('pg_dump ' + Rails.configuration.database_configuration[Rails.env]["database"]  + '> ~/out.txt')
    flash[:notice] = 'Database backup created'
    redirect_to root_url
  end

  def thanks
  end

  def contact_admin

  end

  def send_admin

  end
end
