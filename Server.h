#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <sys/poll.h>
class Server {
    char buffer[256];
    struct sockaddr_in addr;
    template<typename T>void examination(const T&value);
    void recording(int &client);

public:
    void connection();

};




#endif //SERVER_SERVER_H
