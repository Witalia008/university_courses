from django.contrib.auth.decorators import login_required
from django.contrib.auth.views import login
from django.shortcuts import render, redirect


@login_required(login_url='/login/')
def index(request):
    return render(request, 'index.html', {})


def custom_login(request):
    if request.user.is_authenticated():
        return redirect('index')
    else:
        return login(request)
