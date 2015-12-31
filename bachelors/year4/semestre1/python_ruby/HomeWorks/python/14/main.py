import xml.sax
import pygtk
pygtk.require('2.0')
import gtk


class MyHandler(xml.sax.ContentHandler):
    def __init__(self):
        self.dt = {}
        self.widgets = []
        self.widget = None
        self.content = []

    def startElement(self, tag, attributes):
        if tag == 'widget':
            widgetName = attributes['name']
            if widgetName not in self.dt:
                self.dt[widgetName] = type(str(widgetName), (), {'name': widgetName})
            self.widget = self.dt[widgetName]()
        self.content.append([])

    def endElement(self, tag):
        if tag == 'widget':
            self.widgets.append(self.widget)
            self.widget = None
        elif self.widget is not None:
            self.widget.__dict__[tag] = '\n'.join(self.content[-1])
        elif tag != 'widgets':
            self.__dict__[tag] = '\n'.join(self.content[-1])
        self.content.pop()

    def characters(self, content):
        if not content.isspace():
            # print(content)
            self.content[-1].append(content)


def parseSAX(xmlfile):
    parser = xml.sax.make_parser()
    parser.setFeature(xml.sax.handler.feature_namespaces, 0)
    handler = MyHandler()
    parser.setContentHandler(handler)
    parser.parse(xmlfile)
    return handler


class HelloWorld(gtk.Window):

    def __init__(self):
        gtk.Window.__init__(self)

        res = parseSAX('widgets.xml')

        if res.layout == 'Table':
            table = gtk.Table(int(res.rows), int(res.cols), True)
            self.add(table)

            for obj in res.widgets:
                widget = None
                if obj.name == 'Label':
                    widget = gtk.Label(obj.text)
                elif obj.name == 'Button':
                    widget = gtk.Button(obj.label)
                elif obj.name == 'Entry':
                    widget = gtk.Entry()
                    widget.set_text(obj.text)
                elif obj.name == 'ProgressBar':
                    widget = gtk.ProgressBar()
                    widget.set_text(obj.text)
                    widget.set_fraction(float(obj.fraction))
                elif obj.name == 'Spinner':
                    widget = gtk.Spinner()
                    if bool(obj.spinning):
                        widget.start()

                if widget:
                    table.attach(widget,
                                 int(obj.colStart), int(obj.colFinish), int(obj.rowStart), int(obj.rowFinish))

        self.connect("delete-event", gtk.main_quit)
        self.show_all()


# print(gtk.__dict__)
hello = HelloWorld()
gtk.main()
