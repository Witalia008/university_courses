import logging
from django.contrib.auth.decorators import login_required, user_passes_test
from django.contrib.auth.models import User
from django.shortcuts import render, get_object_or_404, redirect
from car_rental.forms import BillForm
from car_rental.models import Bill


@login_required(login_url='/login/')
def index(request, user_pk):
    user = get_object_or_404(User, pk=user_pk)
    logging.debug("%s inside bills_index" % request.user)
    bills = Bill.objects.filter(order__customer=request.user)
    return render(request, 'bill/index.html', {'bills': bills, 'usr': user})


@login_required(login_url='/login/')
def detail(request, user_pk, bill_pk):
    user = get_object_or_404(User, pk=user_pk)
    logging.debug("%s inside bill_detail, bill.pk=%s" % (request.user, bill_pk))
    bill = get_object_or_404(Bill, pk=bill_pk)
    return render(request, 'bill/detail.html', {'bill': bill, 'usr': user})


@login_required(login_url='/login/')
def pay(request, user_pk, bill_pk):
    user = get_object_or_404(User, pk=user_pk)
    logging.debug("%s inside bill_pay, bill.pk=%s" % (request.user, bill_pk))
    bill = get_object_or_404(Bill, pk=bill_pk)
    bill.pay()
    return redirect('bill_detail', user_pk=user.pk, bill_pk=bill.pk)


@user_passes_test(lambda u: u.is_superuser)
def close_order(request, user_pk, order_pk):
    user = get_object_or_404(User, pk=user_pk)
    order = get_object_or_404(user.order_set, pk=order_pk)
    if request.method == 'POST':
        form = BillForm(request.POST)
        form.order = order
        if form.is_valid():
            bill = form.save(commit=False)
            bill.order = order
            bill.order.ret()
            bill.order.car.ret()
            bill.save()
            return redirect('orders', user_pk=user.pk)
    else:
        form = BillForm()
        form.order = order
    return render(request, 'bill/close_order.html', {'form': form, 'usr': user})

