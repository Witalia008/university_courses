import xml.sax


class SAXHandler(xml.sax.ContentHandler):
    def __init__(self):
        self.methodName = ""
        self.source = ""
        self.name = ""
        self.content = []

    def startElement(self, tag, attributes):
        self.content.append("")
        pass

    def endElement(self, tag):
        if tag in ["name", "methodName", "source"]:
            self.__dict__[tag] = self.content[-1]
        self.content.pop()
        pass

    def characters(self, content):
        # if not content.isspace():
        self.content[-1] += content
        pass


def parse_file(file_name):
    parser = xml.sax.make_parser()
    parser.setFeature(xml.sax.handler.feature_namespaces, 0)
    handler = SAXHandler()
    parser.setContentHandler(handler)
    parser.parse(file_name)
    return handler


a = list(reversed(range(0, 10)))
bubble = parse_file("bubble.xml")
exec(bubble.source)
print(bubble.source)
b = eval("%s(%s)" % (bubble.methodName, "a"))
print(b)

quick = parse_file("quick.xml")
exec(quick.source)
print(quick.source)
b = eval("%s(%s)" % (quick.methodName, "a"))
print(b)
