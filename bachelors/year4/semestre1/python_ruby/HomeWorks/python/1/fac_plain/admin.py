from django.contrib import admin

from .models import Course, Mark

admin.site.register(Course)
admin.site.register(Mark)