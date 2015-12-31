import logging
from django.shortcuts import render, get_object_or_404
from car_rental.models import Car


def index(request):
    logging.debug("%s inside cars_index" % request.user)
    cars = Car.objects.all()
    return render(request, 'car/index.html', {'cars': cars})


def detail(request, pk):
    logging.debug("%s inside car_detail, car.pk=%s" % (request.user, pk))
    car = get_object_or_404(Car, pk=pk)
    return render(request, 'car/detail.html', {'car': car})
