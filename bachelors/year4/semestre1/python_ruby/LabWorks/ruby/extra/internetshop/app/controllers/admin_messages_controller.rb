class AdminMessagesController < ApplicationController
  before_action :set_admin_message, only: [:show, :edit, :update, :destroy]

  # GET /admin_messages
  # GET /admin_messages.json
  def index
    @admin_messages = AdminMessage.all
  end

  # GET /admin_messages/1
  # GET /admin_messages/1.json
  def show
  end

  # GET /admin_messages/new
  def new
    @admin_message = AdminMessage.new
  end

  # GET /admin_messages/1/edit
  def edit
  end

  # POST /admin_messages
  # POST /admin_messages.json
  def create
    @admin_message = AdminMessage.new(admin_message_params)
    @admin_message.user_id = current_user.id

    respond_to do |format|
      if @admin_message.save
        format.html { redirect_to @admin_message, notice: 'Admin message was successfully created.' }
        format.json { render :show, status: :created, location: @admin_message }
      else
        format.html { render :new }
        format.json { render json: @admin_message.errors, status: :unprocessable_entity }
      end
    end
  end

  # PATCH/PUT /admin_messages/1
  # PATCH/PUT /admin_messages/1.json
  def update
    respond_to do |format|
      if @admin_message.update(admin_message_params)
        UserMailer.answer_email(current_user, @admin_message).deliver
        format.html { redirect_to @admin_message, notice: 'Admin message was successfully updated.' }
        format.json { render :show, status: :ok, location: @admin_message }
      else
        format.html { render :edit }
        format.json { render json: @admin_message.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /admin_messages/1
  # DELETE /admin_messages/1.json
  def destroy
    @admin_message.destroy
    respond_to do |format|
      format.html { redirect_to admin_messages_url, notice: 'Admin message was successfully destroyed.' }
      format.json { head :no_content }
    end
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_admin_message
      @admin_message = AdminMessage.find(params[:id])
    end

    # Never trust parameters from the scary internet, only allow the white list through.
    def admin_message_params
      params.require(:admin_message).permit(:user_id, :content, :answer)
    end
end
