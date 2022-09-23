#include <iostream>
#include <thread>
#include <cstring>
#include <wiringPi.h>
#include "GolfMembershipManager.h"
#include "Listener.h"
#include "Controller.h"

#include "MembersEntity.h"
#include "tcpServer.h"
#include "ComDev.h"



void serverThread(tcpServer *server)
{
    char recvBuff[BUFSIZ];
    int recvLen;

    while (server->waitAccept() > 0)
    {
        server->setClientState(true);
        while((recvLen = server->recvData(recvBuff, sizeof(recvBuff))) > 0)
        {
            recvBuff[recvLen] = '\0';
            server->sendData(recvBuff, recvLen);
            printf("received : %s\n", recvBuff);
        }
        server->closeSocket(server->getClientSocket());
        server->setClientState(false);
        printf("close client socket\n");
    }
}

int main(void)
{
    tcpServer *cardTcpServer = new tcpServer(5100);
    ComDev *comDev = new ComDev(cardTcpServer);
    MembersManageService * membersManageSerivce = new MembersManageService(comDev);
    Controller *controller = new Controller(membersManageSerivce);
    Listener *listener = new Listener(controller);
    std::thread threadFunc(serverThread, cardTcpServer);

    //GolfMembershipManager golfMembershipManager;

    //golfMembershipManager.run();
    while(1)
    {
        listener->checkEvent();
        delay(50);
    }
    
    return 0;
}