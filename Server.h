#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H
#define  BUFFER_SIZE 16
#include <iostream>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <sys/poll.h>
#include <signal.h>
class Server {
    pid_t parpid, sid;
    static char inline  *buffer = new char(BUFFER_SIZE);
    static inline int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    static void signalHandler(int sig);
    void recording(int &client);
    void receiving();
public:
    void connection();
    void demonization();

};




#endif //SERVER_SERVER_H
