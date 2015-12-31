class GeneralController < ApplicationController
  before_action :authenticate_user!, only: [:groups, :chat]

  def index
    session[:cur_menu] = :home
  end

  def profile
    if myself
      session[:cur_menu] = :profile
    end
  end

  def groups
    session[:cur_menu] = :groups
    @groups = Group.where(open: true)
  end

  def users
    session[:cur_menu] = :people
    @users = User.all
  end

  def chat
    session[:cur_menu] = :chat
    # render 'general/chat', :layout => false
  end
end
