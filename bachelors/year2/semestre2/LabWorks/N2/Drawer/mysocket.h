#ifndef MYSOCKET_H
#define MYSOCKET_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <string>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>
#include <iostream>
#include <datahandler.h>

using namespace std;

class MySocket
{
protected:
    SOCKET sock;
    addrinfo *res;
    MySocket(){}
    MySocket(string, string);
public:
    virtual int init(string, string) = 0;
    virtual void send(vector<char>) = 0;
    virtual vector<char> receive() = 0;
    virtual int send(SOCKET, vector<char>);
    bool isValid() { return sock != INVALID_SOCKET; }
};

class ClientSocket : public MySocket {
public:
    ClientSocket(string, string);
    int init(string, string) override;
    void send(vector<char>) override {}
    vector<char> receive() override;
};

class ServerSocket : public MySocket {
    vector<SOCKET> clients;
    int new_connected;
public:
    ServerSocket(string);
    int init(string, string) override;
    void send(vector<char>) override;
    vector<char> receive() override { return vector<char>(); }
    int nNewConnections() { return new_connected; }
    void wipeNew() { new_connected = 0; }
    friend void checkPendingConnections(ServerSocket&);
};

void checkPendingConnections(ServerSocket&);

#endif // MYSOCKET_H
