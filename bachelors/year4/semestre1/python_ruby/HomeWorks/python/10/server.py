from twisted.protocols.basic import LineReceiver
from twisted.internet.protocol import ServerFactory
from twisted.internet import reactor


class MyProtocol(LineReceiver):
    def lineReceived(self, line):
        print('Received: %s' % line)
        comm = line.split(',')
        for online in self.factory.online:
            if online is not self:
                if self.factory.playing:
                    if comm[0] == 'shoot':
                        online.sendLine(line)
                    if comm[0] == 'resp':
                        online.sendLine(line)
                        if comm[1] == '0':
                            online.sendLine('next')
                            self.sendLine('next')
            else:
                if comm[0] == 'ready':
                    self.factory.ready[self] = True
        if not self.factory.playing and len(self.factory.ready) == 2:
            self.factory.playing = True
            for online in self.factory.online:
                online.sendLine('go')

    def connectionMade(self):
        if len(self.factory.online) < 2:
            self.sendLine('start,%d' % len(self.factory.online))
            self.factory.online.append(self)
            print self.transport.getHost()

    def connectionLost(self, reason):
        self.factory.online.remove(self)
        

class MyFactory(ServerFactory):
    protocol = MyProtocol

    def __init__(self):
        self.online = []
        self.ready = {}
        self.playing = False

if __name__ == '__main__':
    port = 1234
    print 'Server Started at port %d' % (port,)
    reactor.listenTCP(port, MyFactory())
    reactor.run()
