class CommentsController < ApplicationController
  before_filter :authenticate_user
  before_filter :moderate_user, :only => :destroy

  def create
    @article = Article.find(params[:article_id])
    @article.comments.create(:user_id => session[:user_id], :body => comment_params[:body])
    redirect_to article_path(@article)
  end

  def destroy
    @article = Article.find(params[:article_id])
    @comment = @article.comments.find(params[:id])
    @comment.destroy
    redirect_to article_path(@article)
  end

  private
  def comment_params
    params.require(:comment).permit(:body)
  end
end
