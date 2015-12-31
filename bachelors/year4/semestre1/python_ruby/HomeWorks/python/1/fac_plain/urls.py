from django.conf.urls import url, patterns
from fac_plain.views.shared import index, custom_login
import views.courses
import views.marks

urlpatterns = patterns('',
    url(r'^$', index, name='index'),
    url(r'^logout/$', 'django.contrib.auth.views.logout', name='logout'),
    url(r'^login/$', custom_login, name='login'),
    url(r'^user/(?P<user_pk>\d+)/courses/$', views.courses.user_courses, name='my_courses'),
    url(r'^user/(?P<user_pk>\d+)/marks/$', views.marks.user_marks, name='my_marks'),
    url(r'^courses/$', views.courses.index, name='all_courses'),
    url(r'^courses/(?P<course_pk>\d+)/$', views.courses.show, name='course_info'),
    url(r'^courses/(?P<course_pk>\d+)/signup/$', views.courses.signup, name='course_signup'),
)
