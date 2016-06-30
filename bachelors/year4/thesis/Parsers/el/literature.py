from selenium import webdriver
from bs4 import BeautifulSoup
import re
import json
import urlparse

url = "http://www.snhell.gr/search/list.asp"

driver = webdriver.Firefox()

root_url = "http://www.snhell.gr/"
fl = open('stories_el.json', 'w')
fl.write('[\n')
first = True


def parseFairytale(soup, header):
    global first

    # all = soup.find('table', {'id': 'list'}).find_all('a')

    # if all is not None and len(all) > 0:
    #     return

    text = ""
    for td in soup.find('table', {'id': 'list'}).find_all('td'):
        text += td.text + "\n"

    if len(text) < 300:
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

    try:
        for a in soup.find('table', {'id': 'list'}).find_all('a'):
            nurl = urlparse.urljoin(url, a.get('href'))
            if nurl.startswith(root_url):
                parseGroup(nurl, a.text)
    except Exception:
        pass

parseGroup(url, header='Index')

fl.write('\n]')
fl.close()
