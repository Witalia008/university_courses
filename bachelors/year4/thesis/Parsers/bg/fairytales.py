from selenium import webdriver
from bs4 import BeautifulSoup
import re
import json

langs = [
    "bg"
]
urls = [
    "https://traditio.wiki/%D0%A1%D0%BA%D0%B0%D0%B7%D0%BA%D0%B8:%D0%91%D0%BE%D0%BB%D0%B3%D0%B0%D1%80%D1%81%D0%BA%D0%B8%D0%B5_%D0%BD%D0%B0%D1%80%D0%BE%D0%B4%D0%BD%D1%8B%D0%B5_%D1%81%D0%BA%D0%B0%D0%B7%D0%BA%D0%B8"
]

driver = webdriver.Firefox()


def parseFairytale(url):
    driver.get(url)
    soup = BeautifulSoup(driver.page_source, "xml")
    div = soup.find('div', {'id': 'mw-content-text'})
    text = ""
    for p in div.find_all('p'):
        text += p.text + "\n"

    return text

root_url = "https://traditio.wiki"
for (url, l) in zip(urls, langs):
    fl = open('fairytales_%s.json' % l, 'w')
    fl.write('[\n')
    first = True

    driver.get(url)
    html = driver.page_source
    soup = BeautifulSoup(html, 'xml')

    for ol in soup.find('div', {'id': 'mw-content-text'}).find_all('ol'):
        for li in ol.find_all('li'):
            a = li.find('a')
            link = root_url + a.get('href')
            print link
            header = a.text
            print(header)

            try:
                text = parseFairytale(link)
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
