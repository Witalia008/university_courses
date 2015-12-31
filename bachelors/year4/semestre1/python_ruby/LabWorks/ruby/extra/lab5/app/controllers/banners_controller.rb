class BannersController < ApplicationController
  before_action :authenticate_user!, :only => [:new, :create, :destroy]
  before_filter { |c| redirect_to groups_path unless current_user.admin? }

  def new
    @group = Group.find(params[:group_id])
    @banner = Banner.new
  end

  def create
    @group = Group.find(params[:group_id])
    @banner = @group.banners.create(banner_params)
    if @banner.save
      redirect_to group_path(@local_user, @group)
    else
      render 'new'
    end
  end

  def destroy
    @group = Group.find(params[:group_id])
    @group.banners.find(params[:id]).destroy
    redirect_to group_path(@local_user, @group)
  end

  protected
  def banner_params
    params.require(:banner).permit(:image, :url)
  end
end
