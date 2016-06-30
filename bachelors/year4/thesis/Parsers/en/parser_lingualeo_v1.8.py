from selenium import webdriver
from bs4 import BeautifulSoup
import re
import json
import math

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

    json_str = soup.find('div', {'class': 'l-content-inner'}).find('script').text
    json_str = json_str[json_str.index('=') + 1:].rstrip(' ;')

    json_obj = json.loads(json_str)
    lst = json_obj["result"]["list"]["content"]

    levelMin = float(json_obj["filterParams"]["levelMin"])
    levelMax = float(json_obj["filterParams"]["levelMax"])

    for lnk in lst:
        link = lnk["url"]
        print link

        header_str = lnk["content_name"]
        print header_str
        level = float(lnk["level"])
        rating = float(lnk["rating"])

        try:
            driver.get(root_url + link)
            html = driver.page_source
            soup = BeautifulSoup(html, 'xml')

            text_inner = soup.find('div', {'class': re.compile('text-container-inner.*')}).findChildren(recursive=False)

            text = [""]
            for item in text_inner:
                if item.name == "br":
                    text.append("\n")
                elif item.name == "context":
                    text[-1] += combineContent(item.find_all(re.compile('tran.*'))) + " "
            text_str = "".join([x.rstrip(' ') for x in text])
            text_str = text_str.strip()
            print(text)

            fl.write('' if first else ',\n')
            first = False
            fl.write(json.dumps({
                'Difficulty': int(1.5 + 3 * (level - levelMin) / (levelMax - levelMin)),
                'Rating': 1 + rating * 4,
                'Headline': header_str,
                'Text': text_str,
                'ShortDescr': (text[0] + text[1]).strip()}))
        except Exception:
            pass

fl.write('\n]')
fl.close()
