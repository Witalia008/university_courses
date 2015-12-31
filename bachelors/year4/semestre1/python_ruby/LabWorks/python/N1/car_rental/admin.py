from django.contrib import admin

# Register your models here.
from car_rental.models import Car, Bill, Order

admin.site.register(Car)
admin.site.register(Bill)
admin.site.register(Order)