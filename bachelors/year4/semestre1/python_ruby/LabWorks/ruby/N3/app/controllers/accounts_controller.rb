class AccountsController < ApplicationController
  before_filter :authenticated_user
  before_filter :is_admin, :only => [:unblock]
  before_filter :myself_or_admin, :only => [:index]

  def index
    @current_user = User.find(session[:user_id])
    @is_admin = @current_user.role.rolename == 'ADMIN'
    @user = User.find(params[:user_id])
    logger.debug "Access to accounts of #{@user.username} to #{@current_user.username} (#{@current_user.role.rolename})"
  end

  def edit
    @user = User.find(params[:user_id])
    @account = @user.accounts.find(params[:id])
    @cards = @account.credit_cards.all
  end

  def create
    @user = User.find(params[:user_id])
    @account = @user.accounts.create({:balance => 0, :blocked => false})
    redirect_to edit_user_account_path(@user, @account)
    flash[:notice] = (I18n.t :created) + " #{@account.id}"
  end

  def block
    @user = User.find(params[:user_id])
    @account = @user.accounts.find(params[:account_id])
    logger.debug "#{@user.username} blocks acc#{@account.id}"
    @account.update(:blocked => true)
    redirect_to edit_user_account_path(@user, @account)
    flash[:notice] = I18n.t :blocked
    flash[:colour] = 'valid'
  end

  def unblock
    @user = User.find(params[:user_id])
    @account = @user.accounts.find(params[:account_id])
    logger.debug "#{@user.username} unblocks acc#{@account.id}"
    @account.update(:blocked => false)
    redirect_to edit_user_account_path(@user, @account)
    flash[:notice] = I18n.t :unblocked
    flash[:colour] = 'valid'
  end

  def update_balance
    @user = User.find(params[:user_id])
    @account = @user.accounts.find(params[:account_id])
    if @account.balance + params[:balance_delta].to_i >= 0 && !@account.blocked
      @account.update(:balance => @account.balance + params[:balance_delta].to_i)
      flash[:notice] = I18n.t :changed
      flash[:colour] = 'valid'
    else
      flash[:notice] = I18n.t :cannot_be_done
      flash[:colour] = 'invalid'
    end
    redirect_to edit_user_account_path(@user, @account)
  end
end
