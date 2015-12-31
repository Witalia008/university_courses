from django import forms
from car_rental.models import Order, Bill


class OrderForm(forms.ModelForm):
    class Meta:
        model = Order
        fields = ('passport_number', 'term', )


class BillForm(forms.ModelForm):
    class Meta:
        model = Bill
        fields = ('add_price', 'add_price_reason', )


class AcceptForm(forms.Form):
    reason = forms.CharField()
