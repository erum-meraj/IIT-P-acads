#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <dirent.h>
#include <process.h> 

#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 1024
#define PORT 8080

// Function to list files in the server directory
void list_files(char* buffer) {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        strcpy(buffer, "");
        while ((dir = readdir(d)) != NULL) {
            strcat(buffer, dir->d_name);
            strcat(buffer, "\n");
        }
        closedir(d);
    }
}

// Function to send a file to the client
void send_file(SOCKET client_socket, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        char error_msg[] = "File not found\n";
        send(client_socket, error_msg, sizeof(error_msg), 0);
        return;
    }

    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        send(client_socket, buffer, bytes_read, 0);
    }

    fclose(file);
}

// Function to handle individual client communication
void client_handler(void *socket_desc) {
    SOCKET client_socket = *(SOCKET*)socket_desc;
    char buffer[BUFFER_SIZE];

    // Communication loop for each client
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int recv_size = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (recv_size <= 0) {
            printf("Client disconnected.\n");
            break;
        }

        if (strncmp(buffer, "listall", 7) == 0) {
            char file_list[BUFFER_SIZE];
            list_files(file_list);
            send(client_socket, file_list, strlen(file_list), 0);
        } else if (strncmp(buffer, "send", 4) == 0) {
            char filename[BUFFER_SIZE];
            sscanf(buffer + 5, "%s", filename);  // Extract the filename
            send_file(client_socket, filename);
        } else {
            char error_msg[] = "Invalid command\n";
            send(client_socket, error_msg, sizeof(error_msg), 0);
        }
    }

    closesocket(client_socket);
    _endthread();  // End the client handler thread
}

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int client_len;

    // Initialize Winsock
    printf("Initializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Prepare sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind
    if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    // Listen
    listen(server_socket, 5);  // Allow up to 5 clients to queue for connections
    printf("Waiting for incoming connections...\n");

    client_len = sizeof(struct sockaddr_in);

    // Accept multiple client connections
    while ((client_socket = accept(server_socket, (struct sockaddr *)&client, &client_len)) != INVALID_SOCKET) {
        printf("Connection accepted.\n");

        // Create a new thread for each client
        _beginthread(client_handler, 0, (void*)&client_socket);
    }

    if (client_socket == INVALID_SOCKET) {
        printf("Accept failed: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    // Cleanup
    closesocket(server_socket);
    WSACleanup();
    return 0;
}
