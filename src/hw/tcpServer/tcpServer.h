#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class tcpServer
{
private:
    int serverSock_fd;  //정수형으로 리턴, filediscripter
    int clientSock_fd;  // client
    int portNum;
    bool clientState;

    struct sockaddr_in serv_addr;  //주소를 관리하는 구조체
    struct sockaddr_in client_addr;
    socklen_t clnt_addr_size;  //주소 길이에 대한 

public:
    tcpServer(int port);
    virtual ~tcpServer();
    int getServerSocket();
    int getClientSocket();
    bool getClientState();
    void setClientState(bool state);
    void createSocket();
    int waitAccept();
    int recvData(char *recvBuff, size_t size);  //받는 데이터와 사이즈
    int sendData(char *sendBuff, size_t size);
    void closeSocket(int socket);
};

#endif /* __TCPSERVER_H__ */