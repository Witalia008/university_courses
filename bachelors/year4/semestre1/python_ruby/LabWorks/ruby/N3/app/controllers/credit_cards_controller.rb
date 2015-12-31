class CreditCardsController < ApplicationController
  before_filter :authenticated_user
  before_filter :myself_or_admin, :only => [:index, :show]

  def create
    @user = User.find(params[:user_id])
    @account = @user.accounts.find(params[:account_id])
    card = @account.credit_cards.create({:balance => 0, :user_id => @user.id})

    redirect_to edit_user_account_path(@user, @account)
    flash[:notice] = (I18n.t :created) + " #{card.id}"
  end

  def index
    @user = User.find(params[:user_id])
    @cards = @user.credit_cards.all
  end

  def show
    @user = User.find(params[:user_id])
    @card = @user.credit_cards.find(params[:id])
  end
end
