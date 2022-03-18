#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <cstdlib>

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        std::cout << "Не получилось создать сокет\n";
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if( bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0 )
    {
        std::cout << "Не получилось привязать\n";
        exit(0);
    }

    if( listen(sock, 5) )
    {
        std::cout << "Не получилось начать слушать\n";
        exit(0);
    }

    while(true)
    {
        int s = accept(sock, NULL, NULL);
        if( s < 0 )
        {
            std::cout << "Не получилось принять\n";
            exit(0);
        }

        char buffer[1024];

        for(;;)
        {
            memset(buffer, 0, 1024);
            int rc = recv(s, buffer, 1024, 0);
            std::cout << buffer;
            if( rc < 0 )
            {
                if( errno == EINTR )
                    continue;
                return 0;
            }

        }
    }
    return 0;
}