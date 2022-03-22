
#ifndef SERVER_DEMONIZATION_H
#define SERVER_DEMONIZATION_H
#include <cstdlib>
#include <unistd.h>
class Demonization {
    void daemon();

    template<typename T>void examination(const T&value);

    pid_t parpid;
    
public:

};


#endif //SERVER_DEMONIZATION_H
