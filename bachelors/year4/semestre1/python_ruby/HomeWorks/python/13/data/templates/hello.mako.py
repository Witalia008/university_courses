# -*- coding:utf-8 -*-
from mako import runtime, filters, cache
UNDEFINED = runtime.UNDEFINED
STOP_RENDERING = runtime.STOP_RENDERING
__M_dict_builtin = dict
__M_locals_builtin = locals
_magic_number = 10
_modified_time = 1446146949.953
_enable_loop = True
_template_filename = 'E:/Cloud/OneDrive/My Computer/Projects/ProgInUniv/4 Course/python&ruby/HomeWorks/phw13/phw13/templates/hello.mako'
_template_uri = '/hello.mako'
_source_encoding = 'utf-8'
from markupsafe import escape
_exports = []


def render_body(context,**pageargs):
    __M_caller = context.caller_stack._push_frame()
    try:
        __M_locals = __M_dict_builtin(pageargs=pageargs)
        __M_writer = context.writer()
        __M_writer(u'<form method="post" action="/hello/search">\r\n    <label for="srch">Search request:</label>\r\n    <input id="srch" name="search_string" type="text">\r\n    <input type="submit" value="Search">\r\n</form>')
        return ''
    finally:
        context.caller_stack._pop_frame()


"""
__M_BEGIN_METADATA
{"source_encoding": "utf-8", "line_map": {"17": 0, "28": 22, "22": 1}, "uri": "/hello.mako", "filename": "phw13/templates/hello.mako"}
__M_END_METADATA
"""
