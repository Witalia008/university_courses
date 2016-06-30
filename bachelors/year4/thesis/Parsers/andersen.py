from selenium import webdriver
from bs4 import BeautifulSoup
import re
import json

langs = [
    # "uk",
    # "be",
    # "ky",
    "ru"
]
urls = [
    # "http://xn----7sbbatgaljrc3bd4bel.xn--p1ai/%D0%BA%D0%B0%D0%B7%D0%BA%D0%B8-%D0%B0%D0%BD%D0%B4%D0%B5%D1%80%D1%81%D0%B5%D0%BD%D0%B0-%D0%BD%D0%B0-%D1%83%D0%BA%D1%80%D0%B0%D1%97%D0%BD%D1%81%D1%8C%D0%BA%D1%96%D0%B9-%D0%BC%D0%BE%D0%B2%D1%96/",
    # "http://xn----7sbbatgaljrc3bd4bel.xn--p1ai/%D0%BA%D0%B0%D0%B7%D0%BA%D1%96-%D0%B0%D0%BD%D0%B4%D1%8D%D1%80%D1%81%D0%B5%D0%BD%D0%B0-%D0%BD%D0%B0-%D0%B1%D0%B5%D0%BB%D0%B0%D1%80%D1%83%D1%81%D0%BA%D0%B0%D0%B9-%D0%BC%D0%BE%D0%B2%D0%B5/",
    # "http://xn----7sbbatgaljrc3bd4bel.xn--p1ai/%D0%B0%D0%BD%D0%B4%D0%B5%D1%80%D1%81%D0%B5%D0%BD%D0%BDi%D2%A3-%D0%B5%D1%80%D1%82%D0%B5%D0%B3i%D1%81i/",
    "http://xn----7sbbatgaljrc3bd4bel.xn--p1ai/"
]

driver = webdriver.Firefox()



def parseFairytale(url):
    driver.get(url)
    soup = BeautifulSoup(driver.page_source, "xml")
    div = soup.find('div', {'class': 'entry-content'})
    if not div:
        div = soup.find('div', {'class': 'page-content'})
    text = ""
    for p in div.find_all('p'):
        text += p.text + "\n"

    return text


for (url, l) in zip(urls, langs):
    fl = open('andersen_%s.json' % l, 'w')
    fl.write('[\n')
    first = True

    driver.get(url)
    html = driver.page_source
    soup = BeautifulSoup(html, 'xml')

    all = soup.find_all('a', {'class': 'title'}) \
            if l != "ru" \
            else soup.find('ul', {"id": "menu-%d1%81%d0%ba%d0%b0%d0%b7%d0%ba%d0%b8"}).find_all('a')
    for a in all:
        link = a.get('href')
        print link
        header = a.text
        print(header)

        try:
            text = parseFairytale(a.get('href'))
            print(text)

            fl.write('' if first else ',\n')
            first = False
            fl.write(json.dumps({
                        'Headline': header,
                        'Text': text,
                        'ShortDescr': text[:100],
                        'Difficulty': 3,
                        'Rating': 5}))
        except Exception:
            pass

    fl.write('\n]')
    fl.close()
