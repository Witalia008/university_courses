from django.db import models

# Create your models here.
from django.utils import timezone


class Car(models.Model):
    car_name = models.CharField(max_length=200)
    year = models.IntegerField()
    seat_number = models.IntegerField()
    is_rented = models.BooleanField(default=False)

    def rent(self):
        self.is_rented = True
        self.save()

    def ret(self):
        self.is_rented = False
        self.save()

    def __str__(self):
        return "%s (%d, %d seats)" % (self.car_name, self.year, self.seat_number)


class Order(models.Model):
    car = models.ForeignKey('Car')
    customer = models.ForeignKey('auth.User')
    date_placed = models.DateTimeField(default=timezone.now)
    passport_number = models.CharField(max_length=10)
    term = models.IntegerField()
    was_paid = models.BooleanField(default=False)
    accepted = models.NullBooleanField(null=True)
    rej_reason = models.TextField(null=True, blank=True)
    returned = models.BooleanField(default=False)

    def pay(self):
        self.was_paid = True
        self.save()

    def ret(self):
        self.returned = True
        self.save()

    def accept(self):
        self.accepted = True
        self.save()

    def decline(self, reason):
        self.accepted = False
        self.rej_reason = reason
        self.save()

    def __str__(self):
        return "%s - %s" % (self.car.car_name, self.customer.username)


class Bill(models.Model):
    order = models.ForeignKey('Order')
    add_price = models.IntegerField(default=0)
    add_price_reason = models.TextField(blank=True)
    was_paid = models.BooleanField(default=False)

    def pay(self):
        self.was_paid = True
        self.save()

    def __str__(self):
        return "%s (%d$)" % (self.order, self.add_price)
