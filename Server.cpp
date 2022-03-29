
#include "Server.h"
void Server::signalHandler(int sig) {
    close(sock);
    delete buffer;
    exit(sig);
}
void Server::demonization() {
    parpid = fork(); //создаем дочерний процесс
    if(parpid < 0) {
        exit(1);
    } else if(parpid != 0) {
        exit(0);
    }
    umask(0);//даем права на работу с фс
    sid = setsid();//генерируем уникальный индекс процесса
    if(sid < 0) {
        exit(1);
    }
    if((chdir("/")) < 0) {//выходим в корень фс
        exit(1);
    }
    close(STDIN_FILENO);//закрываем доступ к стандартным потокам ввода-вывода
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}
void Server::recording(int &client) { //запись в файл
    std::ofstream file ( "/home/mrmomenticus/CLionProjects/Server/file.txt", std::ios_base::app ) ;
    file << buffer;
}
void Server::receiving() { // получение данных
    while (true) {
        int client = accept(sock, NULL, NULL);
        if (client  <0){
            std::cout <<"Ошибка";
            close (sock);
            exit(0);
        }
        while (true) {
            int rc = recv(client, buffer, BUFFER_SIZE, 0);
            if (rc <= 0) {
                close(client);
                break;
            }
            recording(client);
        }
    }
}
void Server::connection() { //метод для создания соединения
    signal(SIGTERM, signalHandler ) ;
    signal(SIGHUP, signalHandler);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if( bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0 )
    {
        std::cout << "Не получилось привязать\n";
        close (sock);
        exit(0);
    }
    listen(sock, 1);
    receiving();
}








