class GeneralController < ApplicationController

  def index
    @news = News.where(['created_at >= ?', 3.months.ago])
  end
  def about
  end
  def search
    if params[:query]
      search_items = Item.search do
        fulltext params[:query]
      end
      search_groups = Group.search do
        fulltext params[:query]
      end
      search_news = News.search do
        fulltext params[:query]
      end
      @items = search_items.results
      @groups = search_groups.results
      @news = search_news.results
    else
      @items, @groups, @news = [], [], []
    end
  end
end
