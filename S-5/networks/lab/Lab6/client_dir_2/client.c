#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 1024
#define PORT 8080
#define SERVER_IP "127.0.0.1"

void download_file(SOCKET sock, const char *filename) {
    char buffer[BUFFER_SIZE];
    FILE *file = fopen(filename, "wb");
    int bytes_received;

    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    while ((bytes_received = recv(sock, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytes_received, file);
        if (bytes_received < BUFFER_SIZE) break;  // Assume the file is fully received
    }

    fclose(file);
    printf("File %s downloaded successfully\n", filename);
}

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE], command[BUFFER_SIZE];

    // Initialize Winsock
    printf("Initializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    // Connect to remote server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connection failed. Error: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    printf("Connected to server.\n");

    // Command loop
    while (1) {
        printf(">> ");
        fgets(command, sizeof(command), stdin);

        if (strncmp(command, "listall", 7) == 0) {
            send(sock, command, strlen(command), 0);
            memset(buffer, 0, BUFFER_SIZE);
            recv(sock, buffer, BUFFER_SIZE, 0);
            printf("Files in server:\n%s", buffer);
        } else if (strncmp(command, "send", 4) == 0) {
            char filename[50];
            sscanf(command + 5, "%s", filename);
            send(sock, command, strlen(command), 0);
            download_file(sock, filename);
        } else {
            printf("Invalid command. Use 'listall' or 'send <filename>'\n");
        }
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
