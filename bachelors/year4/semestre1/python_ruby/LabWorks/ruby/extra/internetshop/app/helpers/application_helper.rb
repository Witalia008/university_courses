module ApplicationHelper
  def is_customer
    current_user.nil? ? false :  Customer.exists?(:user_id => current_user.id)
  end

  def is_worker
    current_user.nil? ? false : Worker.exists?(:user_id => current_user.id)
  end

  def is_admin
    current_user.nil? ? false : current_user.is_admin
  end

  def user_name(user)
    if not user.customer.nil?
      user.customer.full_name
    elsif not user.worker.nil?
      user.worker.name
    end
  end

  def unread_messages
    Message.where('receiver = ? AND (seen is null or seen = FALSE)', current_user.id).count
  end

  def unread_user_messages(user)
    Message.where('receiver = ? AND sender = ? AND (seen is null or seen = FALSE)', current_user.id, user.id).count
  end

  def unanswered_admin_messages
    AdminMessage.where('answer IS NULL').count
  end

  def unread_str
    num = unread_messages
    if num == 0
      ''
    else
      ' (' + num.to_s + ')'
    end
  end

  def unread_user_str(user)
    num = unread_user_messages user
    if num == 0
      ''
    else
      ' (' + num.to_s + ')'
    end
  end

  def unanswered_admin_str
    num = unanswered_admin_messages
    if num == 0
      ''
    else
      ' (' + num.to_s + ')'
    end
  end
end
