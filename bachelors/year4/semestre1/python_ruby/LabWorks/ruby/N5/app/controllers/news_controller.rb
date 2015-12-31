class NewsController < ApplicationController
  before_filter :is_admin, only: [:new, :create]

  def index
    # Require only latest ones
    @all_news = News.where(['created_at >= ?', 3.months.ago])
  end

  def index_old
    if params[:start_date]
      date = params[:start_date].to_date.beginning_of_day
      @old_news = News.where(:created_at => date..[date+1.months, 3.months.ago].min)
    else
      @old_news = News.where(['created_at < ?', 3.months.ago])
    end
  end

  def new
    @news = News.new
  end
  def create
    @news = News.new(news_params)
    if @news.save
      notice('valid', 'News has been added')
      redirect_to news_path(@news)
    else
      notice
      render 'new'
    end
  end

  def show
    @news = News.find(params[:id])
  end

  protected
  def news_params
    params.require(:news).permit(
        :header, :preview, :image, :full_text, :image_alt, :keywords)
  end
end
