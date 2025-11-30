#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define MAX_BUFFER 1024

void initializeWinsock() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "Failed to initialize Winsock. Error Code : %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
}

SOCKET createSocket() {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "Could not create socket. Error Code : %d\n", WSAGetLastError());
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    return sock;
}

struct sockaddr_in setServerAddress(const char *server_ip, int server_port) {
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &server_address.sin_addr);
    return server_address;
}

void connectToServer(SOCKET sock, struct sockaddr_in *server_address) {
    if (connect(sock, (struct sockaddr *)server_address, sizeof(*server_address)) < 0) {
        fprintf(stderr, "Connect failed. Error Code : %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

void cleanup(SOCKET sock) {
    closesocket(sock);
    WSACleanup();
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_ip> <server_port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *server_ip = argv[1];
    int server_port = atoi(argv[2]);

    initializeWinsock();
    SOCKET sock = createSocket();
    struct sockaddr_in server_address = setServerAddress(server_ip, server_port);
    connectToServer(sock, &server_address);

    char buffer[MAX_BUFFER];
    while (1) {
        printf("Running.....\n\n");
        printf("Enter command for the telnet server('quit' to exit): ");
        fgets(buffer, MAX_BUFFER, stdin);
        
        // Remove newline character from the input
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "quit") == 0) {
            break;
        }

        // Send command to the server
        if (send(sock, buffer, strlen(buffer), 0) < 0) {
            fprintf(stderr, "Send failed. Error Code : %d\n", WSAGetLastError());
            break;
        }

        // Receive output from the server
        int received_bytes = recv(sock, buffer, MAX_BUFFER - 1, 0);
        if (received_bytes < 0) {
            fprintf(stderr, "Receive failed. Error Code : %d\n", WSAGetLastError());
            break;
        } else if (received_bytes == 0) {
            printf("Server disconnected.\n");
            break;
        }

        buffer[received_bytes] = '\0';  // Null-terminate the string
        printf("Output from server:\n%s\n", buffer);
    }

    cleanup(sock);
    return EXIT_SUCCESS;
}
