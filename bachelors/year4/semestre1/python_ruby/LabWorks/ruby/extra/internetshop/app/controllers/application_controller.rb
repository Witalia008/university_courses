class ApplicationController < ActionController::Base
  # Prevent CSRF attacks by raising an exception.
  # For APIs, you may want to use :null_session instead.
  protect_from_forgery with: :exception

  def render_404
    render file: 'public/404.html', status: 404
  end

  def render_403
    render file: 'public/403.html', status: 403
  end

  def check_customer
    if is_customer
      unless current_user.is_approved
        render 'home/not_approved', status: 403
      end
    else
      render_403
    end
  end

  def check_worker
    if is_worker
      unless current_user.is_approved
        render 'home/not_approved', status: 403
      end
    else
      render_403
    end
  end

  def check_admin
    if is_admin
      unless current_user.is_approved
        render 'home/not_approved', status: 403
      end
    else
      render_403
    end
  end

  def is_customer
    current_user.nil? ? false :  Customer.exists?(:user_id => current_user.id)
  end

  def is_worker
    current_user.nil? ? false : Worker.exists?(:user_id => current_user.id)
  end

  def is_admin
    current_user.nil? ? false : current_user.is_admin
  end

  def is_time_occupied(orders, date, hour)
    _cur = DateTime.parse("#{date} #{hour}:00")
    orders.each do |order|
      _start = DateTime.parse(order.start_time.to_s)
      _end = DateTime.parse(order.end_time.to_s)
      if _start <= _cur && _cur < _end
        return true
      end
    end
    false
  end
  helper_method :is_time_occupied
end
