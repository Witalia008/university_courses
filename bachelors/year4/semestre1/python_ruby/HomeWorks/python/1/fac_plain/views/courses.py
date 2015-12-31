from django.contrib.auth.models import User
from django.shortcuts import render, redirect
from django.utils import timezone
from fac_plain.models import Course


def index(request):
    courses = Course.objects.filter(endDate__gte=timezone.now)
    pastc = Course.objects.filter(endDate__lt=timezone.now)
    return render(request, 'courses/index.html',
                  {'courses': courses,
                   'pastc': pastc,
                   'page_name': 'All courses'})


def user_courses(request, user_pk):
    user = User.objects.get(pk=user_pk)
    courses = user.course_students.filter(endDate__gte=timezone.now)
    pastc = user.course_students.filter(endDate__lt=timezone.now)
    return render(request, 'courses/index.html',
                  {'courses': courses,
                   'pastc': pastc,
                   'page_name': 'My courses'})


def show(request, course_pk):
    course = Course.objects.get(pk=course_pk)
    return render(request, 'courses/show.html', {'course': course})


def signup(request, course_pk):
    user = request.user
    course = Course.objects.get(pk=course_pk)
    course.signup(user)
    return redirect('course_info', course_pk=course_pk)