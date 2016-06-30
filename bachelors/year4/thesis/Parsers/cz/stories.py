from selenium import webdriver
from bs4 import BeautifulSoup
import re
import json
import urlparse

url = "http://www.cist.cz/index.htm"

driver = webdriver.Firefox()

root_url = "http://www.cist.cz/"
fl = open('stories_cz.json', 'w')
fl.write('[\n')
first = True


def parseFairytale(soup, header):
    global first

    text = ""
    for p in soup.find('body').find_all('p', recursive=False):
        text += p.text + "\n"
    for p in soup.find('body').find('center').find_all('p', recursive=False):
        text += p.text + "\n"

    if len(text) < 200:
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

    for a in soup.find_all('a'):
        nurl = urlparse.urljoin(url, a.get('href'))
        if nurl.startswith(root_url):
            parseGroup(nurl, a.text)

parseGroup(url, header='Index')

fl.write('\n]')
fl.close()
