# -*- coding: utf-8 -*-
import requests
from urllib import urlopen
import re

stations = [raw_input("From: "), raw_input("To: ")]
date = raw_input("Date (dd.mm.yyyy): ")
time = raw_input("From time (hh:mm): ")
station_id = []

for station in stations:
    s = urlopen("http://booking.uz.gov.ua/purchase/station/" + station)
    s = s.read().decode("unicode_escape")
    m = re.search('"value":\[({("\w+":("\w+"|\d+),*)*},*)*\]', s)
    print m.group()
    #station_id.append(m.group('id'))


requestData = {'station_id_from' : station_id[0], 'station_id_till' : station_id[1], 
'station_from' : stations[0], 'station_till' : stations[1], 'date_dep' : date, 'time_dep' : time}

requestHeaders = {
        "Host" : "booking.uz.gov.ua",
        "Connection": "keep-alive",
        "Content-Length": 174,
        "Origin" : "http://booking.uz.gov.ua",
        "User-Agent": "Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/27.0.1453.116 Safari/537.36",
        "Content-Type" : "application/x-www-form-urlencoded",
        "GV-Unique-Host": 1,
        "GV-Ajax": 1,
        "GV-Screen": "1366x768",
        "GV-Referer": "http://booking.uz.gov.ua",
        "Accept": "*/*",
        "Referer": "http://booking.uz.gov.ua",
        "Accept-Encoding": "gzip,deflate,sdch",
        "Accept-Language": "ru-RU,ru;q=0.8,en-US;q=0.6,en;q=0.4",
}

r = requests.post('http://booking.uz.gov.ua/purchase/search', data = requestData, headers = requestHeaders)
s = r.text.decode("unicode_escape")
print s
