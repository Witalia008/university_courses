import psycopg2

from tornado import web
from tornadio2 import SocketConnection, TornadioRouter, SocketServer, event


class IndexHandler(web.RequestHandler):
    def get(self):
        self.render('index.html')


class SocketIOHandler(web.RequestHandler):
    def get(self):
        self.render('socket.io.js')


class ChatConnection(SocketConnection):
    participants = {}
    nVisits = 0
    try:
        conn = psycopg2.connect("dbname='phw9' user='postgres' host='localhost' password='password'")
        cur = conn.cursor()
        cur.execute("""DELETE FROM users""")
        conn.commit()
        print('DB connection successful')
    except:
        print('Enable to connect to DB')

    def on_open(self, request):
        print('Connected')
        self.participants[self] = 'Anonymous%d' % ChatConnection.nVisits
        ChatConnection.nVisits += 1

    @event
    def message(self, message):
        print('Message from %s: %s' % (self.participants[self], message))
        to = ''
        if message[0] == '@':
            colonIdx = message.index(':')
            to = message[1:colonIdx]
            message = message[colonIdx+1:].strip()
        for p in self.participants:
            if to == '' or self.participants[p] == to:
                p.send('%s: %s' % (self.participants[self], message))

    @event
    def register(self, uname):
        self.participants[self] = uname
        for p in self.participants:
            p.send('System: %s has entered the room' % uname)
        self.send('System: Welcome, %s!' % uname)
        print('%s has registered' % uname)

        if hasattr(self, 'conn'):
            cur = self.conn.cursor()
            cur.execute("""INSERT INTO users (username) VALUES ('%s')""" % uname)
            self.conn.commit()
            cur.close()
            print('Inserted')

    def on_close(self):
        print('Disconnected')
        username = self.participants[self]
        del self.participants[self]
        for p in self.participants:
            p.send('System: %s has left' % username)

        if hasattr(self, 'conn'):
            cur = self.conn.cursor()
            cur.execute("""DELETE FROM users WHERE username='%s'""" % username)
            self.conn.commit()
            cur.close()
            print('Inserted')

# Create tornadio router
ChatRouter = TornadioRouter(ChatConnection)

# Create socket application
application = web.Application(
    ChatRouter.apply_routes([(r"/", IndexHandler),
                             (r"/socket.io.js", SocketIOHandler)]),
    socket_io_port=8001
)

if __name__ == "__main__":
    import logging
    logging.getLogger().setLevel(logging.DEBUG)

    # Create and start tornadio server
    SocketServer(application)
