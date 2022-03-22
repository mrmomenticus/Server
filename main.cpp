#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <cstdlib>
#include <thread>
#include <fstream>
#include <mutex>
std::mutex m;
void recording(char *buffer){
    m.lock();
    std::ofstream file ( "file.txt" ) ;
    std::cout << buffer;
    file << buffer;
    m.unlock();
}
void receiving(int &s, char *buffer) {
    while (true) {
        m.lock();
        int rc = recv(s, buffer, 64, 0);
        if (rc < 0) {
            if (errno == EINTR)
                continue;
        }
        m.unlock();
    }
};
int main(){
    char buffer[64];
    std::mutex m;
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
        std::thread t1([&](){receiving(s, buffer);});
        std::thread t2([&](){ recording(buffer);});
        t1.join();
        t2.join();
        }
    }
