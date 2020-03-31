#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc , char *argv[])
{
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");

    //Create a socket
    if((s = socket(AF_INET,SOCK_STREAM,0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }

    printf("Socket created.\n");


    server.sin_addr.s_addr = inet_addr("192.168.1.7");//inet_addr("172.217.19.131");
    server.sin_family = AF_INET;
    server.sin_port = htons( 1000 );
while(1){
    //Connect to remote server
    if (connect(s , (struct sockaddr *)&server , sizeof(server)), 0)
    {
        puts("connect error");
        return 1;
    }

    puts("Connected");

    //Send some data
       // char message[50] = "GET / HTTP/1.1\r\n\r\n";
     char message[50]={0};
     scanf("%d",&message[0]);
        if( send(s , message , strlen(message) , 0) , 0)
        {
            puts("Send failed");
            return 1;
        }
        char server_reply[2000];
        int recv_size;
    /*
        //Receive a reply from the server
            if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
            {
                puts("recv failed");
            }
        */

            //Add a NULL terminating character to make it a proper string before printing
            puts(server_reply);
            closesocket(s);
}

    return 0;
}
