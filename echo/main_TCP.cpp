#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

void errHandler(const char* why, const int exitCode = 1)
{
    cerr << why << endl;
    exit(exitCode);
}
int main(int argc, char **argv)
{
    // Подготовка структуры с адрессом нашего клиента
    sockaddr_in * selfAddr = new (sockaddr_in);
    selfAddr->sin_family = AF_INET; 
    selfAddr->sin_port = 0;
    selfAddr->sin_addr.s_addr = 0;

    // подготовка структуры с адрессом "на той стороне" (сервера)
    sockaddr_in * remoteAddr = new (sockaddr_in);
    remoteAddr->sin_family = AF_INET;
    remoteAddr->sin_port = htons(7);
    remoteAddr->sin_addr.s_addr = inet_addr("82.179.90.69");

    // подготовка буфера для передачи и приема данных
    char *buf = new char [256];
    strcpy(buf, "Hello, Echo!\n");
    int msgLen = strlen(buf);

    // создание сокета
    int mySocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mySocket == -1) {
        errHandler("Error open socket!", 11);
    }

    // привязка сокета к адресу
    int rc = bind(mySocket, (const sockaddr*) selfAddr, sizeof (sockaddr_in));
    if (rc== -1) {
        close(mySocket);
        errHandler("Error bind socket with locale addres", 12);
    }

    // установка соедиение
    rc = connect(mySocket, (const sockaddr*) remoteAddr, sizeof (sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        errHandler("Error connect socket with remote server", 13);
    }

    // передача данных
    rc = send(mySocket, buf, msgLen, 0);
    if (rc == -1) {
        close(mySocket);
        errHandler("Error send massage", 14);
    }
    cout << "We send: " << buf << endl;

    // принять ответ
    rc = recv(mySocket, buf, 256, 0);
    if (rc == -1) {
        close(mySocket);
        errHandler("Error receive ansver", 15);
    }
    buf[rc] = '\0';
    cout << "We receive: " << buf << endl;

    // закрыть сокет
    close(mySocket);

    delete selfAddr;
    delete remoteAddr;
    delete[] buf;
    return 0;
}