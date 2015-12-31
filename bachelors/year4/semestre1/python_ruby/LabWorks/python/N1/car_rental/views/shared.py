from django.contrib.auth.decorators import login_required, user_passes_test
from django.contrib.auth.models import User
from django.contrib.auth.views import login
from django.shortcuts import render, redirect


# Create your views here.


# @login_required(login_url='/login/')
def index(request):
    return render(request, 'index.html', {})


def custom_login(request):
    if request.user.is_authenticated():
        return redirect('index')
    else:
        return login(request)


@user_passes_test(lambda u: u.is_superuser)
def all_users(request):
    users = User.objects.all()
    return render(request, 'all_users.html', {'users': users})
