#include "../../includes/webserv.hpp"


void    EventLoop::run()
{
    struct sockaddr_in      serverAddress; // struct defined in <netinet/in.h>
    const int               port = 8080; // start with localhost:8080
    int                     clientSocket;

    // Socket creation: 
    // AF_INET means we're using an IPv4 address, SOCK_STREAM means its a TCP socket, 0 = TCP/IP protocol
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0 )
    {
        std::cerr << "Socket failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Bind Socket (link it to an IP address and port)
    serverAddress.sin_family = AF_INET; // use IPv4
    serverAddress.sin_addr.s_addr = INADDR_ANY;  // Bind to any available network interface
    serverAddress.sin_port = htons(port); // convert port number from machine byte order to network byte order 

    // Here "sockaddr" is a generic structure for socket addresses
    // And because we are using a "sockaddr_in" struct (specific to IPv4)
    // we need to cast a pointer to the "higher" struct for functions such a bind(), accept() and connect()
    if (bind(server_fd,  (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cerr << "Bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Listen for connections: second parameter = backlog size (max number of incoming queued connections)
    if (listen(server_fd, 5) < 0)
    {
        std::cerr << "Listen failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port : " << port << std::endl;

    // Accept a Client Connection (need to calculate client address size and again cast it to a generic pointer)
    struct sockaddr_in      clientAddress;
    unsigned int            addrlen = sizeof(clientAddress);

    if ((clientSocket = accept(server_fd, (struct sockaddr *)&clientAddress, (socklen_t*)&addrlen)) < 0) 
    {
        std::cerr << "Accept failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Connection accepted" << std::endl;

    // Read data from client 
    char        buffer[1024] = {0}; // sets all bytes to 0 (bzero equivalent in c++)
    int         bytes_read = read(clientSocket, buffer, 1024);
    
    if (bytes_read > 0)
        std::cout << "Received: " << buffer << std::endl;

    // Send response
    const char*     http_response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nCiao ragazzi!";
    
    send(clientSocket, http_response, strlen(http_response), 0);
    std::cout << "Response sent" << std::endl;

    // Close the connection
    close(clientSocket);
    std::cout << "Connection closed" << std::endl;

}