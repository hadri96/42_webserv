#include "../../includes/webserv.hpp"

// This function creates the server's listening socket, binds it to the given port
// and configures it to listen for incoming connections.
void    EventLoop::setupServer()
{
    struct sockaddr_in      serverAddress; // struct defined in <netinet/in.h>

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

    // Add a pollfd for the server socket to the pollfd vector 
    pollfd      server_pollfd;

    server_pollfd.fd = server_fd;
    server_pollfd.events = POLLIN; // POLLIN means that there is data to read on this fd
    pollfds.push_back(server_pollfd);

    /*
    The first pollfd is tied to the server socket (server_fd), and is set up to monitor
    POLLIN events, meaning it will send an alert when a new client attempts to connect.

    Every new connection/client will then add a pollfd to the vector 

    pollfds are structs: 
    
    struct pollfd 
    {
        int fd;         // The file descriptor to monitor (e.g., a socket)
        short events;   // The types of events you want to monitor 
        short revents;  // The types of events that actually occurred
    };

    events and revents are both shorts and each event flag (POLLIN, POLLOUT, POLLERR)
    is set by a specific bit (example: POLLOUT = 0010 and POLLIN = 0100)
    We have to use bitwise operations to detect them. 
    */

}


void    EventLoop::run()
{
    setupServer();

    while (true)
    {
        int poll_count = poll(pollfds.data(), pollfds.size(), -1)

        if (poll_count < 0)
        {
            std::cerr << "Poll failed" << std::endl;
            break;
        }
    }
    for (std::size_t i = 0; i < pollfds.size(); i++)
    {
        if (pollfds[i].revents & POLLIN) // if there is data available to read on this fd (and if )
        {
            if (pollfds[i].fd == server_fd) // if the fd currently being processed is the server socket
            {
                int                     clientSocket;
                struct  sockaddr_in     clientAddress;
                socklen_t               addrlen = sizeof(client_addr);

                clientSocket = accept(server_fd, (struct sockaddr *)&clientAddress, &addrlen);
                if (clientSocket >= 0) // if accepted, add new client to pollfds
                {
                    pollfd      client_pollfd;
                    
                    client_pollfd.fd = clientSocket;
                    client_pollfd.events = POLLIN;
                    pollfds.push_back(client_pollfd);
                
                    // add new client fd to map 
                    clientMap[clientSocket] = "Client " + std::to_string(clientSocket);
                    std::cout << "New client connected" << std::endl;
                }
            }
            else
            {

            }
        }

    }
}


/*
void    EventLoop::run()
{
    setupServer();
    // Accept a Client Connection (need to calculate client address size and again cast it to a generic pointer)
    int                     clientSocket;
    struct sockaddr_in      clientAddress;
    unsigned int            addrlen = sizeof(clientAddress);

    if ((clientSocket = accept(server_fd, (struct sockaddr *)&clientAddress, (socklen_t*)&addrlen)) < 0) 
    {
        std::cerr << "Accept failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Connection accepted on fd: " << clientSocket << std::endl;

    // Read data from client 
    char        buffer[2048] = {0}; // sets all bytes to 0 (bzero equivalent in c++)

    std::cerr << buffer << std::endl;
    int         bytes_read = read(clientSocket, buffer, 2048);
    
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

*/