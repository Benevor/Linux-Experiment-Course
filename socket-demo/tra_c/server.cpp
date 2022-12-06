#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <unistd.h>

#include <iostream>

typedef void (*TCPServer)(int nConnectedSocket, int nListenSocket);

//服务器B进程
// nlengthOfQueueOflisten 监听队列长度
int RunTCPServer(TCPServer ServerFunction, int nPort, int nLengthOfQueueOfListen = 100, const char *strBoundIP = NULL)
{
    int nListenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
    // IPv4， 数据流
    if (-1 == nListenSocket)
    {
        std::cout << "socket error" << std::endl;
        return -1;
    }
    // init
    sockaddr_in ServerAddress;
    memset(&ServerAddress, 0, sizeof(sockaddr_in));
    ServerAddress.sin_family = AF_INET;
    //静态绑定IP，如果没有，则为本地IP
    if (NULL == strBoundIP)
    {
        ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else
    {
        //如果有，则绑定
        if (::inet_pton(AF_INET, strBoundIP, &ServerAddress.sin_addr) != 1)
        {
            std::cout << "inet_pton error" << std::endl;
            ::close(nListenSocket);
            return -1;
        }
    }
    //绑定端口
    ServerAddress.sin_port = htons(nPort);
    //套接字与ip和端口号的绑定
    if (::bind(nListenSocket, (sockaddr *)&ServerAddress, sizeof(sockaddr_in)) == -1)
    {
        std::cout << "bind error" << std::endl;
        ::close(nListenSocket);
        return -1;
    }

    if (::listen(nListenSocket, nLengthOfQueueOfListen) == -1)
    {
        std::cout << "listen error" << std::endl;
        ::close(nListenSocket);
        return -1;
    }

    while (true)
    {
        sockaddr_in ClientAddress;
        socklen_t LengthOfClientAddress = sizeof(sockaddr_in);
        int nConnectedSocket = ::accept(nListenSocket, (sockaddr *)&ClientAddress, &LengthOfClientAddress);
        if (-1 == nConnectedSocket)
        {
            std::cout << "accept error" << std::endl;
            ::close(nListenSocket);
            return -1;
        }
        ServerFunction(nConnectedSocket, nListenSocket);
        ::close(nConnectedSocket);
    }
    ::close(nListenSocket);
    return 0;
}

void MyServer(int nConnectedSocket, int nListenSocket)
{
    ::write(nConnectedSocket, "Received from Server: Hello World\n", 35);
}

int main()
{
    RunTCPServer(MyServer, 5000);
    return 0;
}
