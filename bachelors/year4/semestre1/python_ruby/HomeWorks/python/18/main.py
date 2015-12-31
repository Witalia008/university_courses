import socket
import threading
import rsa
from rsa.bigfile import *
import pickle


MSGLEN = 2048


class MySocket:
    def __init__(self, sock=None):
        if not sock:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        else:
            self.sock = sock
        (pubkey, privkey) = rsa.newkeys(512)
        self.pubkey = pubkey
        self.privkey = privkey

    def send(self, msg):
        totalsent = 0
        while totalsent < len(msg):
            # print(dir(self.sock))
            sent = self.sock.send(msg[totalsent:])
            if sent == 0:
                raise RuntimeError("Socket connection broken")
            totalsent += sent

    def sendFile(self, fname):
        with open(fname, 'rb') as f:
            l = f.read(MSGLEN)
            while l:
                print("Sending...")
                print(l)
                self.send(l)
                l = f.read(MSGLEN)

    def receive(self):
        chunks = []
        bytes_recd = 0
        while bytes_recd < MSGLEN:
            # print(dir(self.sock))
            chunk = self.sock.recv(min(MSGLEN - bytes_recd, 2048))
            if chunk == b'':
                break
                # raise RuntimeError("Socket connection broken")
            chunks.append(chunk)
            bytes_recd += len(chunk)
        return b''.join(chunks)

    def receiveFile(self, fname):
        with open(fname, 'wb') as f:
            l = self.receive()
            while l:
                print(l)
                f.write(l)
                l = self.receive()


class ServerSocket(MySocket):
    def __init__(self):
        MySocket.__init__(self)
        self.sock.bind((socket.gethostname(), 27015))
        self.sock.listen(5)
        self.clients = []

    def accept(self):
        (c, _) = self.sock.accept()
        client = MySocket(c)
        self.clients.append(client)
        return client


class ClientSocket(MySocket):
    def __init__(self):
        MySocket.__init__(self)

    def connect(self, host, port):
        self.sock.connect((host, port))


class ClientThread(threading.Thread):
    def __init__(self, server, sock):
        threading.Thread.__init__(self)
        self.sock = sock

    def run(self):
        self.sock.send(pickle.dumps(server.pubkey))
        self.sock.sock.shutdown(socket.SHUT_WR)
        print("Sent Key")
        fname = 'server_data/some_file.enc'
        self.sock.receiveFile(fname)
        decryptFile(fname, server.privkey)
        print("Received Data")


def decryptFile(fname, privkey):
    rfile = 'server_data/some_file.txt'
    with open(fname, 'rb') as infile, open(rfile, 'wb') as outfile:
        decrypt_bigfile(infile, outfile, privkey)
    return rfile


def encryptFile(fname, pubkey):
    rfile = 'client_data/some_file.enc'
    with open(fname, 'rb') as infile, open(rfile, 'wb') as outfile:
        encrypt_bigfile(infile, outfile, pubkey)
    return rfile


choice = input("(s)erver or (c)lient: ")
if choice == 's':
    server = ServerSocket()
    while True:
        client = server.accept()
        ClientThread(server, client).start()
else:
    client = ClientSocket()
    client.connect(socket.gethostname(), 27015)
    pubkey = pickle.loads(client.receive())
    print(type(pubkey).__name__)
    print(pubkey)
    fname = encryptFile('client_data/some_file.txt', pubkey)
    client.sendFile(fname)
