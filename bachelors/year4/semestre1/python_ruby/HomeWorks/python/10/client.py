# https://code.google.com/p/twisted-chat-example/source/browse/?r=7e06743af6bc71b707e45c03e665a630dfefbf6b
import random

import gtk
from twisted.internet.protocol import ClientFactory
from twisted.protocols.basic import LineReceiver
from twisted.internet import gtk2reactor
gtk2reactor.install()


dim = 'BATTLESHIP'
cols = 10
rows = 10
config = {1: 4, 2: 3, 3: 2, 4: 1}
white = gtk.gdk.color_parse('white')
black = gtk.gdk.color_parse('black')
blue = gtk.gdk.color_parse('blue')
red = gtk.gdk.color_parse('red')


class Field:
    def __init__(self):
        self.mine = [[False] * cols for _ in range(0, rows)]
        self.myShot = [[False] * cols for _ in range(0, rows)]
        self.foes = [[False] * cols for _ in range(0, rows)]
        self.foeShot = [[False] * cols for _ in range(0, rows)]
        self.playing = False
        self.ready = False
        self.finished = False
        self.myMove = False
        self.myShipCnt = 10
        self.foeShipCnt = 10

    def randomize(self):
        while not self.check(end=True):
            x = random.randint(0, rows-1)
            y = random.randint(0, cols-1)
            self.flip(x, y)

    def flip(self, x, y):
        if self.mine[x][y]:
            # print(x, y)
            self.mine[x][y] = False
        else:
            self.mine[x][y] = True
            if not self.check():
                self.mine[x][y] = False

    def check(self, end=False):
        ships = {}
        for i in range(0, rows):
            for j in range(0, cols):
                if (i == 0 or not self.mine[i-1][j]) and (j == 0 or not self.mine[i][j-1]) and self.mine[i][j]:
                    right, down = 1, 1
                    while j+right < cols and self.mine[i][j+right]:
                        right += 1
                    while i+down < rows and self.mine[i+down][j]:
                        down += 1
                    if right != 1 and down != 1:
                        return False
                    slen = max(down, right)
                    ships[slen] = ships.get(slen, 0) + 1
                    if not self.empty(i, j, down, right):
                        return False
        # print(ships)
        for i in ships.keys():
            if ships[i] > config.get(i, 0):
                return False
        if end:
            for i in config.keys():
                if ships.get(i, 0) != config[i]:
                    return False
        return True

    def empty(self, x, y, height, width):
        # print(x, y, height, width)
        for i in range(x-1, x+height+1):
            if 0 <= i < rows:
                # print('i', i)
                if y > 0 and self.mine[i][y-1]: return False
                if y+width < cols and self.mine[i][y+width]: return False
        for j in range(y-1, y+width+1):
            if 0 <= j < cols:
                # print('j', j)
                if x > 0 and self.mine[x-1][j]: return False
                if x+height < rows and self.mine[x+height][j]: return False
        # print(True)
        return True

    def foeshoot(self, x, y, resp):
        self.foeShot[x][y] = True
        self.foes[x][y] = False if resp == '0' else True
        if resp == '2':
            self.defeat_ship(self.foes, self.foeShot, x, y)
            self.foeShipCnt -= 1

    def defeat_ship(self, ships, shots, x, y, px=-1, py=-1):
        for i in range(-1, 2):
            for j in range(-1, 2):
                if 0 <= x+i < rows and 0 <= y+j < cols and (i != 0 or j != 0):
                    if ships[x+i][y+j] and (px != x+i or py != y+j):
                        self.defeat_ship(ships, shots, x+i, y+j, x, y)
                    if not ships[x+i][y+j]:
                        shots[x+i][y+j] = True

    def myshoot(self, x, y):
        self.myShot[x][y] = True
        if not self.mine[x][y]:
            return 0
        else:
            if self.lastPiece(x, y):
                self.defeat_ship(self.mine, self.myShot, x, y)
                self.myShipCnt -= 1
                return 2
            else:
                return 1

    def lastPiece(self, x, y, px=-1, py=-1):
        res = True
        print('piece', x, y)
        for i in range(-1, 2):
            for j in range(-1, 2):
                if 0 <= x+i < rows and 0 <= y+j < cols and (i != 0 or j != 0):
                    if self.mine[x+i][y+j]:
                        if not self.myShot[x+i][y+j]:
                            print('Bad', x+i, y+j)
                            return False
                        elif px != x+i or py != y+j:
                            res = res and self.lastPiece(x+i, y+j, x, y)
        return res


class Window(gtk.Window):
    def __init__ (self):
        gtk.Window.__init__(self)
        self.field_width = 400
        self.gap = 20
        self.width = self.field_width * 2 + self.gap
        self.foefield_left = self.field_width + self.gap
        self.height = 400
        self.cell_width = self.field_width // cols
        self.cell_height = self.height // rows
        # self.set_default_size(self.width, self.height)
        self.set_title("The Battleship Game")
        self.set_resizable(False)

        vbox = gtk.VBox()

        self.drawing_area = gtk.DrawingArea()
        self.drawing_area.set_size_request(self.width, self.height)
        self.drawing_area.set_events(gtk.gdk.BUTTON_PRESS_MASK)
        self.drawing_area.connect('button_press_event', self.on_button_press)
        self.drawing_area.modify_bg(gtk.STATE_NORMAL, white)
        vbox.pack_start(self.drawing_area)

        hbox = gtk.HBox()
        self.start_btn = gtk.Button('Start')
        self.start_btn.connect('clicked', self.start_clicked)
        self.randomize_btn = gtk.Button('Randomly put ships')
        self.randomize_btn.connect('clicked', self.random_clicked)
        hbox.pack_start(self.randomize_btn)
        hbox.pack_start(self.start_btn)
        vbox.pack_start(hbox)

        self.add(vbox)

        self.started = False
        self.field = None
        self.last_shot = None

        self.connect('destroy', lambda x: reactor.stop())
        self.show_all()
        self.show()

    def random_clicked(self, widget):
        if self.field:
            self.field.randomize()
            self.draw()

    def start_clicked(self, widget):
        if self.field.check(end=True):
            self.field.ready = True
            factory.instance.sendLine("ready")
            print('started')
        else:
            print('Place ships')

    def on_button_press(self, widget, event):
        if not self.field:
            return
        if not hasattr(self, 'gc'):
            self.gc = self.drawing_area.get_style().fg_gc[gtk.STATE_NORMAL]
        ex = int(event.x)
        ey = int(event.y)
        # self.drawing_area.window.draw_point(self.gc, int(event.x), int(event.y))
        inMyField = True
        if event.x >= self.foefield_left:
            inMyField = False
            ex -= self.foefield_left
        x = ey // self.cell_width
        y = ex // self.cell_height

        if inMyField and not self.field.ready:
            self.field.flip(x, y)

        if not inMyField and self.field.myMove and self.field.playing:
            self.last_shot = (x, y)
            factory.instance.sendLine('shoot,%d,%d' % (x, y))

        self.draw()

    def draw(self):
        self.set_title("The Battleship Game (%s move)" % ('Your' if gui.field.myMove else "Opponent's"))
        # print(self.field.mine)
        for left in [0, self.foefield_left]:
            for i in range(0, rows):
                for j in range(0, cols):
                    if self.field:
                        if left == 0:
                            # print(i, j, self.field.mine[i][j], black if self.field.mine[i][j] else white)
                            if self.field.myShot[i][j]:
                                self.gc.set_rgb_fg_color(red if self.field.mine[i][j] else blue)
                            else:
                                self.gc.set_rgb_fg_color(black if self.field.mine[i][j] else white)
                            self.drawing_area.window.draw_rectangle(self.gc, True,
                                    left + j * self.cell_width, i * self.cell_height,
                                    self.cell_width, self.cell_height)
                        else:
                            if self.field.foeShot[i][j]:
                                self.gc.set_rgb_fg_color(red if self.field.foes[i][j] else blue)
                            else:
                                self.gc.set_rgb_fg_color(white)
                            self.drawing_area.window.draw_rectangle(self.gc, True,
                                    left + j * self.cell_width, i * self.cell_height,
                                    self.cell_width, self.cell_height)
        self.gc.set_rgb_fg_color(black)
        for left in [0, self.foefield_left]:
            for i in range(0, rows):
                for j in range(0, cols):
                    self.drawing_area.window.draw_rectangle(self.gc, False,
                            left + j * self.cell_width, i * self.cell_height,
                            self.cell_width, self.cell_height)
        self.gc.set_rgb_fg_color(black)
        if self.field.playing and not self.field.finished:
            if self.field.myShipCnt == 0:
                self.end_game('lost')
            if self.field.foeShipCnt == 0:
                self.end_game('won')

    def start_game(self, meFirst):
        self.started = True
        self.field = Field()
        self.field.myMove = meFirst

    def end_game(self, status):
        md = gtk.MessageDialog(None,
            gtk.DIALOG_DESTROY_WITH_PARENT, gtk.MESSAGE_INFO,
            gtk.BUTTONS_CLOSE, "You %s" % staticmethod)
        md.run()
        self.field.finished = True


class MyProtocol(LineReceiver):
    def lineReceived(self, line):
        print('Received: %s' % line)
        comm = line.split(',')
        if comm[0] == 'start':
            gui.start_game(True if comm[1] == '0' else False)
        if comm[0] == 'next':
            gui.field.myMove = not gui.field.myMove
            gui.draw()
        if comm[0] == 'resp' and gui.last_shot:
            gui.field.foeshoot(gui.last_shot[0], gui.last_shot[1], comm[1])
            gui.last_shot = None
            gui.draw()
        if comm[0] == 'finish':
            print(comm[1])
        if comm[0] == 'shoot':
            self.sendLine('resp,%d' % gui.field.myshoot(int(comm[1]), int(comm[2])))
            gui.draw()
        if comm[0] == 'go':
            gui.field.playing = True

    def connectionMade(self):
        print "Connection made"
        # gui.set_connected("Connected")

    def connectionLost(self, reason):
        print "Connection Lost"
        # gui.set_connected("Connection Lost")


class MyFactory(ClientFactory):
    protocol = MyProtocol

    def buildProtocol(self, addr):
        self.instance = self.protocol()
        return self.instance

if __name__ == '__main__':
    gui = Window()
    from twisted.internet import reactor
    factory = MyFactory()
    reactor.connectTCP('localhost', 1234, factory)
    reactor.run()
