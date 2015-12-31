# coding: utf-8
import os
from urllib.request import urljoin
import logging

from grab.spider import Spider, Task


class BBCSpider(Spider):
    initial_urls = ['http://www.bbc.com/news']

    def prepare(self):
        self.result_file = open('results.html', 'a')
        self.result_file.write("<h1>%s</h1>\n" % self.initial_urls[0])
        self.result_file.write("<table>\n")
        self.result_count = 0

    def task_initial(self, grab, task):
        yield Task('bbc', url=self.initial_urls[0])

    def task_bbc(self, grab, task):
        for cls in ["buzzard-item", "pigeon-item", "pigeon-item__body", "macaw-item__body"]:
            for elem in grab.doc.select('//div[@class="%s"]/a[@class="title-link"]' % cls):
                yield Task('bbc_new', url=urljoin(self.initial_urls[0], elem.attr('href')))

    def task_bbc_new(self, grab, task):
        for elem in grab.doc.select('//div[@class="story-body"]'):
            self.result_file.write("<tr><th>%s</th></tr>" % elem.select('//h1[@class="story-body__h1"]').text())
            for i in elem.select('//p'):
                self.result_file.write("<tr><td>%s<br/></td></tr>\n" % i.text())
        pass

    def close(self):
        self.result_file.write("</table>\n")
        self.result_file.close()


class GuardianSpider(Spider):
    initial_urls = ['http://www.theguardian.com/world']

    def prepare(self):
        self.result_file = open('results.html', 'a')
        self.result_file.write("<h1>%s</h1>\n" % self.initial_urls[0])
        self.result_file.write("<table>\n")
        self.result_count = 0
        self.visited = []

    def task_initial(self, grab, task):
        yield Task('guardian', url=self.initial_urls[0])

    def task_guardian(self, grab, task):
        for elem in grab.doc.select('//div[@class="fc-item__container"]/a'):
            url = elem.attr('href')
            if url not in self.visited:
                self.visited.append(url)
                yield Task('guardian_new', url=url)

    def task_guardian_new(self, grab, task):
        grab.response.save('results.txt')
        for elem in grab.doc.select('//article'):
            self.result_file.write("<tr><th>%s</th></tr>\n" %
                                   elem.select('//h1[@class="content__headline js-score"]').text())
            for i in elem.select('//div[@class="content__article-body from-content-api js-article__body"]//p'):
                self.result_file.write("<tr><td>%s<br/></td></tr>\n" % i.text())
        self.task_guardian(grab, task)

    def close(self):
        self.result_file.write("</table>\n")
        self.result_file.close()


if __name__ == "__main__":
    try:
        os.remove('results.html')
    except OSError:
        pass
    logging.basicConfig(level=logging.DEBUG)
    bot = BBCSpider(thread_number=2)
    bot.run()
    bot.close()
    bot = GuardianSpider(thread_number=2)
    bot.run()
    bot.close()
