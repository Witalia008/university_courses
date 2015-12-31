from django.contrib.auth.models import User
from django.shortcuts import render


def user_marks(request, user_pk):
    user = User.objects.get(pk=user_pk)
    marks = user.mark_student.all()
    return render(request, 'marks/index.html',
                  {'marks': marks})
