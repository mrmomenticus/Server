#include "Server.h"
template<typename T>
void Server::examination(const T &value) { //шаблон для проверки значений
    if (value <0){
        std::cout <<"Ошибка";
        exit(0);
    }
}

void Server::recording(int &client) { //запись в файл
    std::ofstream file ( "file.txt", std::ios_base::app ) ;
    file << buffer;
}

void Server::connection() { //метод для создания соединения
    int sock = socket(AF_INET, SOCK_STREAM, 0);
//    fds[0].fd = sock;
//    fds[0].fd = POLLHUP;
//    int rev = poll(fds, 1, 10000);
    examination(sock);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if( bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0 )
    {
        std::cout << "Не получилось привязать\n";
        exit(0);
    }
    listen(sock, 10);
    int client = accept(sock, NULL, NULL);
    examination(client);
    while(true) {
        int rc   = recv(client, buffer, 256, 0);
        recording(client);
        if(rc <=0  ){
            std::cout << buffer;
            close(client);
            break;
        }
    }

}




