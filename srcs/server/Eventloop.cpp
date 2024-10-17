#include "../../includes/webserv.hpp"

void    EventLoop::bindSocket()
{
    struct sockaddr_in      serverAddress; // struct defined in <netinet/in.h>
    int                     temp = 1;

    // Bind Socket (link it to an IP address and port)
    serverAddress.sin_family = AF_INET; // use IPv4
    serverAddress.sin_addr.s_addr = INADDR_ANY;  // Bind to any available network interface
    serverAddress.sin_port = htons(port); // convert port number from machine byte order to network byte order 

    // the following code block makes sure that the connection can be made
    // even if the port is still marked as "in use" by the operating system
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &temp, sizeof(temp)) < 0) 
    {
        std::cerr << "setsockopt(SO_REUSEADDR) failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Here "sockaddr" is a generic structure for socket addresses
    // And because we are using a "sockaddr_in" struct (specific to IPv4)
    // we need to cast a pointer to the "higher" struct for functions such a bind(), accept() and connect()
    if (bind(server_fd,  (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cerr << "Bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void    EventLoop::listenOnPort()
{
    // Listen for connections: second parameter = backlog size (max number of incoming queued connections)
    if (listen(server_fd, 5) < 0)
    {
        std::cerr << "Listen failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Server listening on port : " << port << std::endl;
}

// This function creates the server's listening socket, binds it to the given port
// and configures it to listen for incoming connections.
void    EventLoop::setupServer()
{
    // Socket creation: 
    // AF_INET means we're using an IPv4 address, SOCK_STREAM means its a TCP socket, 0 = TCP/IP protocol
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0 )
    {
        std::cerr << "Socket failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    bindSocket();
    listenOnPort();

    // Add a pollfd for the server socket to the pollfd vector 
    pollfd      server_pollfd;

    server_pollfd.fd = server_fd;
    server_pollfd.events = POLLIN; // POLLIN means that there is data to read on this fd
    pollRequests.push_back(server_pollfd);

    // Set server to non blocking 
    int     flags = fcntl(server_fd, F_GETFL, 0);

    fcntl(server_fd, F_SETFL, flags | O_NONBLOCK);

}

// Launches accept function and connects client if socket connection is accepted
void    EventLoop::connectNewClientToServer(std::size_t *i)
{
    int                     clientSocket;
    struct  sockaddr_in     clientAddress;
    socklen_t               addrLen = sizeof(clientAddress);

    // accept function provides clientSocket fd, a pointer to its address and the length of its address
    clientSocket = accept(server_fd, (struct sockaddr *)&clientAddress, &addrLen);

    if (clientSocket < 0)
        std::cerr << "Failed to accept client connection" << std::endl;
    else // if accepted, add new client to pollRequests
    {
        pollfd      clientPollRequest;

        clientPollRequest.fd = clientSocket;
        clientPollRequest.events = POLLIN;
        pollRequests.push_back(clientPollRequest);
        // add new client fd to map (to be changed when other Classes are created)
        clientMap[clientSocket] = "Client " + (*i + '0');
        std::cout << "New client connected" << std::endl;
    }
}

void    EventLoop::closeClient(std::size_t *i)
{
    close(pollRequests[(*i)].fd);
    pollRequests.erase(pollRequests.begin() + *i);
    --(*i);
}

void    EventLoop::run()
{
    setupServer();

    while (true)
    {
        int poll_count = poll(pollRequests.data(), pollRequests.size(), -1); // -1 means infinite timeout

        if (poll_count < 0)
        {
            std::cerr << "Poll failed" << std::endl;
            break;
        }
        //iterate over the pollfd array
        for (std::size_t i = 0; i < pollRequests.size(); i++)
        {
            // check revents field of this pollfd 
            // to check if this fd is ready for reading
            if (pollRequests[i].revents & POLLIN) 
            {
                // if the fd currently being processed is the server socket (listening for new clients)
                // it means a new client is trying to connect to the server
                if (pollRequests[i].fd == server_fd) 
                   connectNewClientToServer(&i);
                else
                {
                    // Else it's a client fd that is ready for reading
                    char    buffer[1024] = {0};
                    int     bytes_read = read(pollRequests[i].fd, buffer, 1024);

                    if (bytes_read <= 0)
                    {
                        closeClient(&i);
                        std::cout << "Client disconnected." << std::endl;
                    } 
                    else // Process the data received from the client and send basic response
                    {
                        std::cout << "Received data from client " << pollRequests[i].fd << " : " << buffer << std::endl;
                            // Send response
                        const char*     http_response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nCiao ragazzi!";
    
                        send(pollRequests[i].fd, http_response, strlen(http_response), 0);
                        std::cout << "Response sent" << std::endl;
                    }
                }
            }
            if (pollRequests[i].revents & POLLHUP) // if one fd has the POLL HANG UP flag 
            {
                closeClient(&i);
                std::cout << "Client disconnecter (hang-up)" << std::endl;
            }
            if (pollRequests[i].revents & POLLERR) // if one fd has the POLL ERROR flag
            {
                std::cerr << "Error in socket (pollfd[" << i << "])" << std::endl;
                closeClient(&i);
            } 
        }
    }
}


/*

Explanation of the Event Loop with Poll():

Setup the Server:
The function starts by calling setupServer(), which initializes the server socket and configures it to listen for incoming connections.

Main Loop: Monitoring FDs with poll():
The loop continuously runs, calling poll() to monitor file descriptors (FDs) stored in pollRequests.
poll() blocks until one or more FDs are ready for an I/O operation, such as a new client connecting or a client sending data. The -1 timeout means it will wait indefinitely until something happens.
If poll() fails (returns a negative value), the loop exits with an error message.

Check Which FDs are Ready:
The loop iterates over each pollfd in the pollRequests array to check if any FDs are ready.
It checks the revents field of each pollfd to see if POLLIN is set, which means the FD is ready for reading.

Handling the Server Socket (server_fd):
If the server socket (server_fd) is ready, it means a new client is trying to connect.
The server calls accept() to establish the connection and create a new client socket FD (clientSocket).
This new client FD is added to pollRequests, and a new entry is created in clientMap to store information about the client.

Handling Existing Client FDs:
If the ready FD is not the server socket, it means an existing client has sent data.
The server reads data from the client socket using read().
If read() returns 0 or less, the client has disconnected, so the server closes the connection and removes the client FD from pollRequests.
Otherwise, it processes the received data and displays it.


    The first pollfd is tied to the server socket (server_fd), and is set up to monitor
    POLLIN events, meaning it will send an alert when a new client attempts to connect.

    Every new connection/client will then add a pollfd to the vector 

    pollRequests are structs: 
    
    struct pollfd 
    {
        int fd;         // The file descriptor to monitor (e.g., a socket)
        short events;   // The types of events you want to monitor 
        short revents;  // The types of events that actually occurred (set by poll())
    };

    events and revents are both bit masks in the form of  shorts 
    each event flag (POLLIN, POLLOUT, POLLERR) is set by a specific bit
    (example: POLLOUT = 0010 and POLLIN = 0100)
    We have to use bitwise operations to detect them. 


void    EventLoop::run()
{
    setupServer();
    // Accept a Client Connection (need to calculate client address size and again cast it to a generic pointer)
    int                     clientSocket;
    struct sockaddr_in      clientAddress;
    unsigned int            addrLen = sizeof(clientAddress);

    if ((clientSocket = accept(server_fd, (struct sockaddr *)&clientAddress, (socklen_t*)&addrLen)) < 0) 
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