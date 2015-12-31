from django.conf.urls import url

from .views.shared import index, custom_login, all_users
import car_rental.views.car as car_view
import car_rental.views.order as order_view
import car_rental.views.bill as bill_view

urlpatterns = [
    url(r'^$', index, name='index'),
    url(r'^logout/$', 'django.contrib.auth.views.logout', name='logout'),
    url(r'^login/$', custom_login, name='login'),
    url(r'^cars/$', car_view.index, name='cars'),
    url(r'^cars/(?P<pk>\d+)/$', car_view.detail, name='car_detail'),
    url(r'^cars/(?P<pk>\d+)/rent/$', order_view.rent, name='rent'),
    url(r'^users/(?P<user_pk>\d+)/orders/$', order_view.index, name='orders'),
    url(r'^users/(?P<user_pk>\d+)/orders/(?P<order_pk>\d+)/$', order_view.detail, name='order_detail'),
    url(r'^users/(?P<user_pk>\d+)/orders/(?P<order_pk>\d+)/pay$', order_view.pay, name='pay_order'),
    url(r'^users/(?P<user_pk>\d+)/bills/$', bill_view.index, name='bills'),
    url(r'^users/(?P<user_pk>\d+)/bills/(?P<bill_pk>\d+)/$', bill_view.detail, name='bill_detail'),
    url(r'^users/(?P<user_pk>\d+)/bills/(?P<bill_pk>\d+)/pay/$', bill_view.pay, name='pay_bill'),
    url(r'^users/$', all_users, name='all_users'),
    url(r'^users/(?P<user_pk>\d+)/orders/(?P<order_pk>\d+)/close/$', bill_view.close_order, name='close_order'),
    url(r'^users/(?P<user_pk>\d+)/orders/(?P<order_pk>\d+)/accept/$', order_view.accept_order, name='accept_order'),
    url(r'^users/(?P<user_pk>\d+)/orders/(?P<order_pk>\d+)/decline/$', order_view.decline_order, name='decline_order')
]
