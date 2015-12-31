import logging

from pylons import request, response, session, tmpl_context as c, url
from pylons.controllers.util import abort, redirect

from phw13.lib.base import BaseController, render

log = logging.getLogger(__name__)


import json
import urllib


class HelloController(BaseController):

    def index(self):
        # Return a rendered template
        #return render('/hello.mako')
        # or, return a string
        return render('/hello.mako')

    def search(self):
        string = request.params['search_string']

        query = urllib.urlencode({'q': string})
        url = 'http://ajax.googleapis.com/ajax/services/search/web?v=1.0&%s' % query
        search_response = urllib.urlopen(url)
        search_results = search_response.read()
        results = json.loads(search_results)
        data = results['responseData']
        print('Total results: %s' % data['cursor']['estimatedResultCount'])
        hits = data['results']

        return render('/results.mako', extra_vars={
            'query': string,
            'estCount': data['cursor']['estimatedResultCount'],
            'count': len(hits),
            'hits': hits,
            'moreUrl': data['cursor']['moreResultsUrl']
        })
