from django.conf.urls import url
from django.views.generic import RedirectView
from phw5 import settings

urlpatterns = [
    url(regex=r'^%s(?P<path>.*)$' % settings.STATIC_URL[1:],
        view='django.views.static.serve',
        kwargs={
            'document_root': 'E:\\Cloud\\OneDrive\\My Computer\\Projects\\ProgInUniv'
                             '\\4 Course\\python&ruby\\HomeWorks\\phw5\\dir_cont\\static',
            'show_indexes': True}, name='static_show'),
    url(r'^$', RedirectView.as_view(url='%s' % settings.STATIC_URL)),
]
