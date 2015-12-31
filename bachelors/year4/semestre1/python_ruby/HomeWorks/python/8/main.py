import sys
from os import listdir
from os.path import isfile, isdir, join
from lxml import etree
import xml.sax
import xml.dom.minidom
import threading


def validate(xml, xsd):
    with open(xsd, 'rb') as f:
        schema_root = etree.XML(f.read())
    schema = etree.XMLSchema(schema_root)
    xmlparser = etree.XMLParser(schema=schema)
    try:
        with open(xml, 'rb') as f:
            etree.fromstring(f.read(), xmlparser)
        return True
    except etree.XMLSchemaError:
        return False


def obj_to_string(self, level=0):
    if isinstance(self, str):
        return ("    " * level) + self

    res = ("    " * level) + type(self).__name__ + "("
    for (k,v) in self.__dict__.items():
        res += "\n"
        res += ("    " * (level + 1)) + "%s=[" % k
        for x in v:
            res += "\n" + obj_to_string(x, level+2) + ", "
        res += "]"
    return res + ")"


class SAXHandler(xml.sax.ContentHandler):
    def __init__(self):
        self.st = []
        self.dt = {}
        self.root = None
        self.content = ""

    def startElement(self, tag, attributes):
        if tag not in self.dt:
            self.dt[tag] = type(tag, (), {'__str__': obj_to_string})
        cur = self.dt[tag]()
        if len(self.st) > 0:
            if (tag + "s") not in self.st[-1].__dict__:
                self.st[-1].__dict__[tag + "s"] = []
            self.st[-1].__dict__[tag + "s"].append(cur)
        self.st.append(cur)

    def endElement(self, tag):
        self.root = self.st.pop()

    def characters(self, content):
        if not content.isspace():
            self.st[-1].content = [content]


def parseSAX(xmlfile):
    parser = xml.sax.make_parser()
    parser.setFeature(xml.sax.handler.feature_namespaces, 0)
    handler = SAXHandler()
    parser.setContentHandler(handler)
    parser.parse(xmlfile)
    return handler.root


class_dict = {}


def parseElement(elem):
    if isinstance(elem, xml.dom.minidom.Text):
        return elem.data

    tag = elem.tagName
    if tag not in class_dict:
        class_dict[tag] = type(tag, (), {'__str__': obj_to_string})
    cur = class_dict[tag]()

    for child in elem.childNodes:
        if isinstance(child, xml.dom.minidom.Text):
            if not child.data.isspace():
                cur.content = [child.data]
        else:
            c = parseElement(child)

            ctag = child.tagName
            if (ctag + "s") not in cur.__dict__:
                cur.__dict__[ctag + "s"] = []
            cur.__dict__[ctag + "s"].append(c)

    return cur


def parseDOM(xmlfile):
    dom_tree = xml.dom.minidom.parse(xmlfile)
    root = dom_tree.documentElement
    global class_dict
    class_dict = {}
    return parseElement(root)


class MyThread(threading.Thread):
    def __init__(self, xml):
        threading.Thread.__init__(self)
        self.file = xml

    def run(self):
        if self.file.endswith(".xml") and isfile(self.file[:-3] + "xsd"):
            xml = self.file
            xsd = self.file[:-3] + "xsd"
            valid = validate(xml, xsd)
            print(xml, ":", "valid" if valid else "invalid")
            if valid:
                with open(self.file[:-4] + ".SAX.txt", 'w') as f:
                    f.write(str(parseSAX(xml)))
                with open(self.file[:-4] + ".DOM.txt", 'w') as f:
                    f.write(str(parseSAX(xml)))


threads = []


def check_files(files):
    for f in files:
        if isfile(f):
            new_thread = MyThread(f)
            new_thread.start()
            threads.append(new_thread)
        elif isdir(f):
            lst = list(map(lambda x: join(f, x), listdir(f)))
            check_files(lst)


check_files(sys.argv[1:])
for x in threads:
    x.join()
