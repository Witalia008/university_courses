from selenium import webdriver
from bs4 import BeautifulSoup
import re
import json

url = "http://megaznaika.com.ua/kazka/kazki-pro.html"

driver = webdriver.Firefox()

root_url = "http://megaznaika.com.ua/kazka/"
fl = open('faitytales_uk.json', 'w')
fl.write('[\n')
first = True


def parseFairytale(soup, header):
    global first

    text = ""
    for div in soup.find_all('div', {'class': 'text-tab-content'}):
        for p in div.find_all('p'):
            text += p.text + "\n"

    if len(text) < 500:
        return
    print(header)
    print(text)

    fl.write('' if first else ',\n')
    first = False
    fl.write(json.dumps({
                'Headline': header,
                'Text': text,
                'ShortDescr': text[:100],
                'Difficulty': 3,
                'Rating': 5}))


visited = {}


def parseGroup(url, header):
    global visited
    if url in visited:
        return
    visited[url] = True

    print(url)
    driver.get(url)
    html = driver.page_source
    soup = BeautifulSoup(html, 'xml')

    try:
        parseFairytale(soup, header)
    except Exception:
        pass

    for a in soup.find_all('a', {'class': 'imCssLink'}):
        parseGroup(root_url + a.get('href'), a.text)

parseGroup(url, header='Index')

fl.write('\n]')
fl.close()
