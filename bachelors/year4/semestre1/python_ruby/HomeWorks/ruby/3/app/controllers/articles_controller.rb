class ArticlesController < ApplicationController
  before_filter :authenticate_user
  before_filter :moderate_user, :only => [:edit, :update]

  def index
    @user = User.find(session[:user_id])
    @articles = []
    Article.find_each do |art|
      if art.is_permitted(@user.role.id)
        @articles << art
      end
    end
  end
  def new
    @article = Article.new
  end
  def create
    @article = Article.new(article_params)
    if @article.save
      redirect_to(:action => 'index')
    else
      render 'new'
    end
  end
  def edit
    @user = User.find(session[:user_id])
    @article = Article.find(params[:id])
  end
  def update
    @article = Article.find(params[:id])
    if @article.update(article_params)
      redirect_to @article
    else
      render 'edit'
    end
  end
  def perm_edit
    @article = Article.find(params[:article_id])
    logger.debug "perm_edit #{params}"
    @role = Role.find(params[:role][:id])
    if params[:allowed] && !@article.is_permitted(@role.id)
      @article.roles.delete(@role.id)
    elsif !params[:allowed] && @article.is_permitted(@role.id)
      logger.debug "Forbidding for article #{@article.id} role #{@role.id}"
      @article.roles << @role
      @article.save
    end
    redirect_to edit_article_path(@article)
  end

  def show
    @user = User.find(session[:user_id])
    @article = Article.find(params[:id])
    unless @article.is_permitted(@user.role.id)
      redirect_to home_path
    end
  end

  private
  def article_params
    params.require(:article).permit(:topic, :text)
  end
end
