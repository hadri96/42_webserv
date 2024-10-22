#include "../../includes/webserv.hpp"


// Links the socket to an IP address and port
void    EventLoop::bindSocket()
{
    struct sockaddr_in      serverAddress; // struct defined in <netinet/in.h>
    int                     temp = 1;

    // Bind Socket (tells it which IP address family the socket will use)
    serverAddress.sin_family = AF_INET; // use IPv4 (Address Family: Internet)
    serverAddress.sin_addr.s_addr = INADDR_ANY;  // Bind to all available network interfaces
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




// Makes the server listen for connections on the given port
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

    // Set server to non blocking:
    // Set O_NONBLOCK and FD_CLOEXEC (close on exec) flags at the same time using F_SETFL
    if (fcntl(server_fd, F_SETFL, O_NONBLOCK | FD_CLOEXEC) == -1) 
    {
        std::cerr << "fcntl failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    // the bitwise OR operator makes sure that the existing flags are not modified, just the O_NONBLOCK and FD_CLOEXEC added.
}




// Launches accept function and connects client if socket connection is accepted
void    EventLoop::connectNewClientToServer()
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
        pollfd              clientPollRequest;
        ClientConnection    clientObj(clientSocket);

        clientPollRequest.fd = clientSocket;
        clientPollRequest.events = POLLIN;
        pollRequests.push_back(clientPollRequest);
        clientMap.insert(std::make_pair(clientSocket, clientObj));
        std::cout << "New client (fd: " << clientSocket << ") connected" << std::endl;
    }
}



// This function closes the fd of the given client and erases it from the pollRequest list. 
void    EventLoop::closeClient(std::size_t *i, std::string message)
{
    close(pollRequests[(*i)].fd);
    pollRequests.erase(pollRequests.begin() + *i);
    --(*i);
    std::cerr << message << std::endl;
}

// Sends resource to client via a buffer. Resource comes from HTTPResponse object
void    EventLoop::sendResponseBuffer(std::size_t *i, HTTPResponse &response)
{
    std::string     parsed_string = response.getParsedResponse();
    size_t          buffer_size = 1024;
    size_t          total_size = parsed_string.size();
    size_t          bytes_sent = 0;

    while (bytes_sent < total_size) 
    {
        size_t      chunk_size = std::min(buffer_size, total_size - bytes_sent);
        int         sent;
        
        sent = send(pollRequests[(*i)].fd, (parsed_string.c_str() + bytes_sent), chunk_size, 0);
        if (sent < 0) 
        {
            closeClient(i, "Client disconnected: Error sending response");
            return;
        }
        bytes_sent += sent;
    }
    std::cout << "Response sent in chunks." << std::endl;
}


// (CLIENT --> SERVER)  : HTTP Request 
// Function Handles what happens when a client connects with a POLLIN request (i.e client sends a request to server)
void    EventLoop::handleClientRead(std::size_t *i)
{
    char    buffer[1024] = {0};
    int     bytes_read = read(pollRequests[(*i)].fd, buffer, 1024);

    if (bytes_read <= 0)
        closeClient(i, "Client disconnected: No bytes read");
    else
    {        
        /*
        Here the HTTP response should be created based on the HTTPRequest
        Which can be found by going through the ClientConnection in the ClientMap 
        */
        HTTPResponse    HTTPResponse;

        sendResponseBuffer(i, HTTPResponse);
    }
}


// (SERVER --> CLIENT ) : HTTP Response 
// Access the correct clientConnection object 
// in order to send the message that lies in its' write_buffer 
// over the connection of its socket (client_fd) to the server. 
void    EventLoop::handleClientWrite(std::size_t *i)
{
    int             client_fd = pollRequests[(*i)].fd;
    ssize_t         bytes_sent;
    
    // Find clientConnection object in clientMap according to client_fd:
    std::map<int, ClientConnection>::iterator   it = clientMap.find(client_fd);
    if (it == clientMap.end())
    {
        std::cerr << "client fd " << client_fd << " not found in clientMap" << std::endl;
        exit(EXIT_FAILURE);
    }
    ClientConnection*   clientObj = &it->second;
    
    // Send the bytes contained in the write_buffer to client_fd socket
    bytes_sent = send(client_fd, clientObj->write_buffer.c_str(), clientObj->write_buffer.size(), 0);
    if (bytes_sent > 0)
    {
        std::cerr << "bytes_sent > 0 " << std::endl;
        clientObj->write_buffer.erase(0, bytes_sent);
    }
    if  (bytes_sent < 0)
    {   
        std::cerr << "bytes_sent < 0" << std::endl; 
        return ;
    }
    if (clientObj->write_buffer.empty())
        {
            std::cerr << "write buffer is empty" << std::endl;
            pollRequests[(*i)].events &= ~POLLOUT;
        } // bitwise AND operation with opposite of POLLOUT (~ = NOT)
}


// The EventLoop::run() function serves as the main server event loop. 
// It first sets up the server and then continuously waits for events on a set of file descriptors using the poll() system call. 
// The function processes incoming connections and data from clients by iterating over the array of pollfd structures, 
// checking the revents field to determine if a file descriptor is ready for reading / writing, has been disconnected, or encountered an error.
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
                   connectNewClientToServer();
                else // Else it's a client fd that is ready for reading ==> Read the data into a buffer 
                    handleClientRead(&i);
            }
            if (pollRequests[i].revents & POLLOUT)
                handleClientWrite(&i);
            if (pollRequests[i].revents & POLLHUP) // if one fd has the POLL HANG UP flag 
                closeClient(&i,"Client disconnected (POLLHUP)");
            if (pollRequests[i].revents & POLLERR) // if one fd has the POLL ERROR flag
                closeClient(&i, "Error in socket (POLLERR)");
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

GET: Used to retrieve data from the server. It is safe (does not alter the server state), idempotent (same result for multiple identical requests), cacheable, and can be bookmarked and recorded in browser history.

POST: Used to send data to the server to create a new resource. It is non-idempotent (each request can create a unique resource), not cacheable, and cannot be bookmarked.

PUT: Used to update or replace an existing resource. It is idempotent (repeating the same request has the same effect), not typically cacheable, and cannot be bookmarked.

DELETE: Used to remove a resource from the server. It is idempotent (repeating the request has the same effect), not cacheable, and typically returns an acknowledgment.


*/