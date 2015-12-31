from django.conf.urls import url
from interpolate import views

urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^fun/$', views.interpolate, name='interpolate'),
    url(r'^remote/$', views.remote_ipl, name='remote_ipl')
]
