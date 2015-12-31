# -*- coding:utf-8 -*-
from mako import runtime, filters, cache
UNDEFINED = runtime.UNDEFINED
STOP_RENDERING = runtime.STOP_RENDERING
__M_dict_builtin = dict
__M_locals_builtin = locals
_magic_number = 10
_modified_time = 1446146948.608
_enable_loop = True
_template_filename = 'phw13/templates/results.mako'
_template_uri = '/results.mako'
_source_encoding = 'utf-8'
from markupsafe import escape
_exports = []


def render_body(context,**pageargs):
    __M_caller = context.caller_stack._push_frame()
    try:
        __M_locals = __M_dict_builtin(pageargs=pageargs)
        count = context.get('count', UNDEFINED)
        query = context.get('query', UNDEFINED)
        hits = context.get('hits', UNDEFINED)
        estCount = context.get('estCount', UNDEFINED)
        moreUrl = context.get('moreUrl', UNDEFINED)
        __M_writer = context.writer()
        __M_writer(u'<form method="post" action="/hello/search">\r\n    <label for="srch">Search request:</label>\r\n    <input id="srch" name="search_string" type="text" value="')
        __M_writer(escape(query))
        __M_writer(u'">\r\n    <input type="submit" value="Search">\r\n</form>\r\n\r\nEstimated number of results: ')
        __M_writer(escape(estCount))
        __M_writer(u'<br/>\r\nShowing: ')
        __M_writer(escape(count))
        __M_writer(u'<br/>\r\n\r\n<table>\r\n    <tr>\r\n        <th>Title</th>\r\n        <th>Desctiprion</th>\r\n        <th>Url</th>\r\n    </tr>\r\n')
        for hit in hits:
            __M_writer(u'    <tr>')
            __M_writer(u'        <td>')
            __M_writer(hit['title'])
            __M_writer(u'</td>')
            __M_writer(u'        <td>')
            __M_writer(hit['content'])
            __M_writer(u'</td>')
            __M_writer(u'        <td><a href="')
            __M_writer(escape(hit['url']))
            __M_writer(u'">Link</a></td>\r\n    </tr>')
        __M_writer(u'</table>\r\n\r\n<a href="')
        __M_writer(escape(moreUrl))
        __M_writer(u'">More results</a><br/>\r\n<a href="/hello/index">To Index</a>')
        return ''
    finally:
        context.caller_stack._pop_frame()


"""
__M_BEGIN_METADATA
{"source_encoding": "utf-8", "line_map": {"17": 0, "27": 1, "28": 3, "29": 3, "30": 7, "31": 7, "32": 8, "33": 8, "34": 16, "35": 17, "36": 18, "37": 18, "38": 18, "39": 19, "40": 19, "41": 19, "42": 20, "43": 20, "44": 20, "45": 23, "46": 25, "47": 25, "53": 47}, "uri": "/results.mako", "filename": "phw13/templates/results.mako"}
__M_END_METADATA
"""
