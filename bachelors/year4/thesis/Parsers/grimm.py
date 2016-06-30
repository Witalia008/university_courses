from selenium import webdriver
from bs4 import BeautifulSoup
import re
import json

urls = [
    "http://www.grimmstories.com/da/grimm_eventyr/list",
    "http://www.grimmstories.com/de/grimm_maerchen/list",
    "http://www.grimmstories.com/en/grimm_fairy-tales/list",
    "http://www.grimmstories.com/es/grimm_cuentos/list",
    "http://www.grimmstories.com/fi/grimm_sadut/list",
    "http://www.grimmstories.com/fr/grimm_contes/list",
    "http://www.grimmstories.com/hu/grimm_mesek/list",
    "http://www.grimmstories.com/it/grimm_fiabe/list",
    "http://www.grimmstories.com/ja/grimm_dowa/list",
    "http://www.grimmstories.com/ko/grimm_donghwa/list",
    "http://www.grimmstories.com/nl/grimm_sprookjes/list",
    "http://www.grimmstories.com/pl/grimm_basnie/list",
    "http://www.grimmstories.com/pt/grimm_contos/list",
    "http://www.grimmstories.com/ro/grimm_basme/list",
    "http://www.grimmstories.com/ru/grimm_skazki/list",
    "http://www.grimmstories.com/tr/grimm_masallari/list",
    "http://www.grimmstories.com/vi/grimm_truyen/list",
    "http://www.grimmstories.com/zh/grimm_tonghua/list"
]


driver = webdriver.Firefox()
root_url = "http://www.grimmstories.com"

for url in urls:
    ss = url.split('/')
    l = ss[3]
    fname = ss[4]
    fl = open('%s_%s.json' % (fname, l), 'w')
    fl.write('[\n')
    first = True

    driver.get(url)
    html = driver.page_source
    soup = BeautifulSoup(html, 'xml')
    for li in soup.find('ul', {'class': 'bluelink'}).find_all('li'):
        a = li.find('a')
        link = a.get('href')
        print link

        driver.get(link)
        html = driver.page_source
        soup = BeautifulSoup(html, 'xml')

        try:
            header = a.text
            print(header)

            text = soup.find('div', {'class': 'text'}).text
            print(text)

            img = root_url + soup.find('div', {'class': 'afbfloat'}).find('img').attrs['src']
            print(img)

            fl.write('' if first else ',\n')
            first = False
            fl.write(json.dumps({
                        'Headline': header,
                        'Text': text,
                        'ShortDescr': text[:100],
                        'Difficulty': 3,
                        'Rating': 5,
                        'Image': img}))
        except Exception:
            pass

    fl.write('\n]')
    fl.close()
