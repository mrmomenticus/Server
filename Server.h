#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H
#define  BUFFER_SIZE 16
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <sys/poll.h>
#include <signal.h>
class Server {
    char  *buffer = new char(BUFFER_SIZE);
    struct sockaddr_in addr;
    void recording(int &client);
    void receiving();
public:
    static void signalHandler(int sig);
    void connection();
    static inline int sock = socket(AF_INET, SOCK_STREAM, 0);
};




#endif //SERVER_SERVER_H
