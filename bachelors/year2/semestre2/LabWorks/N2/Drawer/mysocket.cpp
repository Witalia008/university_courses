#include "mysocket.h"

MySocket::MySocket(string ip, string port)
{
    init(ip, port);
}

int MySocket::init(string ip, string port)
{
    sock = INVALID_SOCKET;
    WSAData wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result) {
        cout << "WSAStartUp failed " << result << endl;
        return result;
    }
    addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = ip == "" ? AF_INET : AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    if (ip == "")
        hints.ai_flags = AI_PASSIVE;
    result = getaddrinfo(ip == "" ? nullptr : ip.c_str(), port.c_str(), &hints, &res);
    if (result) {
        cout << "GetAddrInfo failed " << result << endl;
        WSACleanup();
        return result;
    }
    return 0;
}

int MySocket::send(SOCKET client, vector<char> data) {
    int result = ::send(client, &data[0], data.size(), 0);
    if (result < 0)
        cout << "send failed " << WSAGetLastError() << endl;
    else if (result == 0)
        cout << "Client disconnected" << endl;
    return result;
}

ClientSocket::ClientSocket(string ip, string port)
{
    init(ip, port);
}

int ClientSocket::init(string ip, string port)
{
     int result = MySocket::init(ip, port);
     if (result) return result;
     for (addrinfo *ptr = res; ptr != NULL; ptr = ptr->ai_next) {

         sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
         if (sock == INVALID_SOCKET) {
             cout << "socket failed with error: %ld\n" << WSAGetLastError() << endl;
             WSACleanup();
             return 1;
         }

         result = connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen);
         if (result == SOCKET_ERROR) {
             closesocket(sock);
             sock = INVALID_SOCKET;
             continue;
         }
         break;
     }
     freeaddrinfo(res);
     if (sock == INVALID_SOCKET) {
         cout << "Unable to connect to server!\n";
         WSACleanup();
         return 1;
     }
     return 0;
}

vector<char> ClientSocket::receive() {
#define DEFAULT_BUFLEN 512
    char recvbuf[DEFAULT_BUFLEN];
    int result = recv(sock, recvbuf, 4, 0);
    if (result != 4) return vector<char>();
    DataHandler res(vector<char>(recvbuf, recvbuf + 4), true);
    do {
        int result = recv(sock, recvbuf, DEFAULT_BUFLEN, 0);
        if (result < 0)
            cout << "receive failed" << endl;
        else if (result == 0)
            cout << "disconnected\n";
        else
            res.push_back(vector<char>(recvbuf, recvbuf + result));
    } while (result > 0 && res.realLength() != res.length());
    return res.getData();
}

ServerSocket::ServerSocket(string port)
{
    init("", port);
}

int ServerSocket::init(string ip, string port)
{
    int result = MySocket::init(ip, port);
    if (result) return result;
    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock == INVALID_SOCKET) {
        cout << "socket failed " << WSAGetLastError() << endl;
        freeaddrinfo(res);
        WSACleanup();
        return WSAGetLastError();
    }
    result = ::bind(sock, res->ai_addr, (int)res->ai_addrlen);
    if (result == SOCKET_ERROR) {
        cout << "bind failed " << WSAGetLastError() << endl;
        freeaddrinfo(res);
        closesocket(sock);
        WSACleanup();
        return WSAGetLastError();
    }
    freeaddrinfo(res);
    result = listen(sock, SOMAXCONN);
    if (result == SOCKET_ERROR) {
        cout << "listen error " << WSAGetLastError() << endl;
        closesocket(sock);
        WSACleanup();
        return WSAGetLastError();
    }
    return 0;
}

void ServerSocket::send(vector<char> data) {
    data = DataHandler(data, false).getSendData();
    for (auto i = clients.begin(); i != clients.end(); ) {
        if (!MySocket::send(*i, data)) {
            clients.erase(i);
        }
        else {
            ++i;
        }
    }
}

void checkPendingConnections(ServerSocket &server) {
    for (;;) {
        if (!server.isValid()) return;
        SOCKET clientSocket = accept(server.sock, NULL, NULL);
        if (clientSocket == INVALID_SOCKET)
            continue;
        server.clients.push_back(clientSocket);
        ++server.new_connected;
    }
}
