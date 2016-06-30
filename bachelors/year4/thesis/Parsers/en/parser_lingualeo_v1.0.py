from selenium import webdriver
from bs4 import BeautifulSoup
import re
import json

def combineContent(trans):
    res = ""
    for item in trans:
        res += item.text
    return res

fl = open('materials.json', 'w')
fl.write('[\n')
first = True
driver = webdriver.Firefox()
root_url = 'http://lingualeo.com'
url = "http://lingualeo.com/ru/jungle?isNew=0&levelMin=1&levelMax=7&entry=all&byTheme=0&sortBy=best&sortDir=desc&contentFormat=3&userLang=ru&srt=0&page=%d"
for p in range(1, 51):
    driver.get(url % p)
    html = driver.page_source
    soup = BeautifulSoup(html, 'xml')
    for divv in soup.find_all('div', {'class': re.compile('content-item.*')}):
        link = divv.find('a').get('href')
        print link

        try:
            driver.get(root_url + link)
            html = driver.page_source
            soup = BeautifulSoup(html, 'xml')

            header = soup.find('div', {'class': re.compile('content-title-text.*')})\
                .find('h1').find('context').findChildren()
            header_str = combineContent(header)
            print header_str

            text_inner = soup.find('div', {'class': re.compile('text-container-inner.*')}).findChildren(recursive=False)

            text = [""]
            for item in text_inner:
                if item.name == "br":
                    text.append("\n")
                elif item.name == "context":
                    text[-1] += combineContent(item.find_all(re.compile('tran.*'))) + " "
            text_str = "".join([(x if x == "\n" else x.strip()) for x in text])
            text_str = text_str.strip()
            print(text_str)

            fl.write('' if first else ',\n')
            first = False
            fl.write(json.dumps({'Headline': header_str, 'Text': text_str, 'ShortDescr': text[0]}))
        except Exception:
            pass

fl.write('\n]')
fl.close()
