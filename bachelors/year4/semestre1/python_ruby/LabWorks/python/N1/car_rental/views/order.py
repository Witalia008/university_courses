import logging
from django.contrib.auth.decorators import login_required, user_passes_test
from django.contrib.auth.models import User
from django.shortcuts import render, get_object_or_404, redirect
from car_rental.forms import OrderForm, AcceptForm
from car_rental.models import Car, Order


@login_required(login_url='/login/')
def rent(request, pk):
    logging.debug("%s inside rent, car.pk=%s" % (request.user, pk))
    car = get_object_or_404(Car, pk=pk)
    if request.method == 'POST':
        logging.debug("     POST received")
        form = OrderForm(request.POST)
        # if data sent is valid
        if form.is_valid():
            logging.debug("         adding rental")
            post = form.save(commit=False)
            post.customer = request.user
            post.car = car
            car.rent()
            post.save()
            return redirect('index')
        # we'll return form for editing otherwise
    else:
        # create initial form for this car
        logging.debug("     GET received")
        form = OrderForm()
        form.car = car
    return render(request, 'order/make_order.html', {'form': form})


@login_required(login_url='/login/')
def index(request, user_pk):
    user = get_object_or_404(User, pk=user_pk)
    if not request.user.is_superuser and request.user.pk != user.pk:
        return redirect('index')
    logging.debug("%s inside orders_index of %s" % (request.user, user))
    orders = Order.objects.filter(customer=user)
    return render(request, 'order/index.html', {'orders': orders, 'usr': user})


@login_required(login_url='/login/')
def detail(request, user_pk, order_pk):
    user = get_object_or_404(User, pk=user_pk)
    if not request.user.is_superuser and request.user.pk != user.pk:
        return redirect('index')
    logging.debug("%s inside orders_detail" % request.user)
    order = get_object_or_404(Order, pk=order_pk)
    return render(request, 'order/detail.html', {'order': order, 'usr': user, 'form': AcceptForm()})


@login_required(login_url='/login/')
def pay(request, user_pk, order_pk):
    user = get_object_or_404(User, pk=user_pk)
    if not request.user.is_superuser and request.user.pk != user.pk:
        return redirect('index')
    logging.debug("%s inside orders_pay for, order.pk=%s" % (request.user, order_pk))
    order = get_object_or_404(Order, pk=order_pk)
    order.pay()
    return redirect('order_detail', user_pk=user.pk, order_pk=order.pk)


@user_passes_test(lambda u: u.is_superuser)
def accept_order(request, user_pk, order_pk):
    user = get_object_or_404(User, pk=user_pk)
    order = get_object_or_404(user.order_set, pk=order_pk)
    order.accept()
    return redirect('order_detail', user_pk=user.pk, order_pk=order.pk)


@user_passes_test(lambda u: u.is_superuser)
def decline_order(request, user_pk, order_pk):
    user = get_object_or_404(User, pk=user_pk)
    order = get_object_or_404(user.order_set, pk=order_pk)
    if request.method == 'POST':
        user = get_object_or_404(User, pk=user_pk)
        order = get_object_or_404(user.order_set, pk=order_pk)
        form = AcceptForm(request.POST)
        if form.is_valid():
            order.decline(form.cleaned_data['reason'])
            order.car.ret()
    return redirect('order_detail', user_pk=user.pk, order_pk=order.pk)