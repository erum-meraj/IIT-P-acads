#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 1024

void handle_error(const char *msg) {
    fprintf(stderr, "%s: %d\n", msg, WSAGetLastError());
    exit(EXIT_FAILURE);
}

int main() {
    WSADATA wsaData;
    SOCKET sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char *server_ip = "127.0.0.1";  // Change this to the server's IP address
    int server_port = 23;           // Change this to the server's port number

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        handle_error("WSAStartup failed");
    }

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == INVALID_SOCKET) {
        handle_error("socket");
    }

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        handle_error("inet_pton");
    }

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        handle_error("connect");
    }

    printf("Connected to %s:%d\n", server_ip, server_port);

    while (1) {
        // Read user input
        printf("Enter command: ");
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            handle_error("fgets");
        }

        // Remove newline character from the input
        buffer[strcspn(buffer, "\n")] = '\0';

        // Check if the user wants to quit
        if (strcmp(buffer, "quit") == 0) {
            break;
        }

        // Send the command to the server
        if (send(sockfd, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
            handle_error("send");
        }

        // Receive output from the server
        memset(buffer, 0, BUFFER_SIZE);
        int recv_len = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);
        if (recv_len == SOCKET_ERROR) {
            handle_error("recv");
        } else if (recv_len == 0) {
            printf("Server closed the connection.\n");
            break;
        }

        // Print the server response
        printf("Server response:\n%s\n", buffer);
    }

    // Clean up
    closesocket(sockfd);
    WSACleanup();
    printf("Connection closed.\n");

    return 0;
}
