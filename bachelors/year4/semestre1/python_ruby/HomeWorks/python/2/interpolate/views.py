from collections import defaultdict
import json
from django.http import JsonResponse, HttpResponse
from django.shortcuts import render

# Create your views here.
from interpolate.models import Interpolation as ipl


def drange(start, stop, step):
    while start < stop:
        yield start
        start += step


def index(request):
    x = [i for i in drange(ipl.in_min_x, ipl.in_max_x + 1, ipl.in_step)]
    y = list(map(ipl.in_func, x))
    return render(request, 'index.html', {
        'x': ','.join(["%.3f" % i for i in x]),
        'y': ','.join(["%.3f" % i for i in y])
    })


def interpolate(request):
    x = list(map(float, request.POST['x'].split(',')))
    y = list(map(float, request.POST['y'].split(',')))
    dots = [ipl.Dot(xi, yi) for (xi, yi) in zip(x, y)]
    ipl.splines = defaultdict(lambda: ipl.Tuple())
    ipl.interpolate(dots)
    res = [ipl.Dot(i, ipl.calc(i)) for i in drange(ipl.out_min_x, ipl.out_max_x, ipl.out_step)]
    return render(request, 'func.html', {'arr': dots, 'res': res, 'splines': list(ipl.splines.values())})


class MyEncoder(json.JSONEncoder):
    def default(self, o):
        return o.__dict__


def remote_ipl(request):
    x = list(map(float, request.POST['x'].split(',')))
    y = list(map(float, request.POST['y'].split(',')))
    dots = [ipl.Dot(xi, yi) for (xi, yi) in zip(x, y)]
    ipl.splines = defaultdict(lambda: ipl.Tuple())
    ipl.interpolate(dots)
    res = [ipl.Dot(i, ipl.calc(i)) for i in drange(ipl.out_min_x, ipl.out_max_x, ipl.out_step)]

    return HttpResponse(json.dumps(
        {'arr': dots,
         'res': res,
         'splines': ipl.splines
         }, cls=MyEncoder
    ), content_type="application/json")
