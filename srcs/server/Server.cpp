#include "../../includes/webserv.hpp"


// =============================================================================
// Constructors & Destructors
// =============================================================================

Server::Server(Manager* manager) : manager(manager) {};

Server::~Server() {};


// ·············································································
// Public Methods
// ·············································································

// Links the socket to an IP address and port
void    Server::bindSocket()
{
    struct sockaddr_in      serverAddress; // struct defined in <netinet/in.h>
    int                     temp = 1;

    // Bind Socket (tells it which IP address family the socket will use)
    serverAddress.sin_family = AF_INET; // use IPv4 (Address Family: Internet)
    serverAddress.sin_addr.s_addr = INADDR_ANY;  // Bind to all available network interfaces
    serverAddress.sin_port = htons(port); // convert port number from machine byte order to network byte order 

    // the following code block makes sure that the connection can be made
    // even if the port is still marked as "in use" by the operating system
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &temp, sizeof(temp)) < 0) 
    {
        std::cerr << "setsockopt(SO_REUSEADDR) failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Here "sockaddr" is a generic structure for socket addresses
    // And because we are using a "sockaddr_in" struct (specific to IPv4)
    // we need to cast a pointer to the "higher" struct for functions such a bind(), accept() and connect()
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cerr << "Bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void    Server::listenOnPort()
{
    // Listen for connections: second parameter = backlog size (max number of incoming queued connections)
    if (listen(serverSocket, 5) < 0)
    {
        std::cerr << "Listen failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Server listening on port : " << port << std::endl;
}


// Calls accept function and connects client if socket connection is accepted
void    Server::connectNewClientToServer()
{
    int                     clientSocket;
    struct  sockaddr_in     clientAddress;
    socklen_t               addrLen = sizeof(clientAddress);

    // accept function provides clientSocket fd, a pointer to its address and the length of its address
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &addrLen);

    if (clientSocket < 0)
    {    
        std::cerr << "Failed to accept client connection" << std::endl;
        return ;
    }
    // if accepted, add new client to manager->getPollRequests()
    pollfd              clientPollRequest;
    Client              clientObj(clientSocket);

    clientPollRequest.fd = clientSocket;
    clientPollRequest.events = POLLIN;
    manager->getPollRequests().push_back(clientPollRequest);

    clientVect.push_back(clientObj);
    std::cout << "New client (fd: " << clientSocket << ") connected" << std::endl;
}


// ·············································································
// Getters and Utils
// ·············································································

Client*    Server::getClientFromSocket(int clientSocket)
{
    std::vector<Client>::iterator it;

    for (it = clientVect.begin(); it != clientVect.end(); it++)
    {
        if (it->getClientSocket() == clientSocket)
            break;
    }
    if (it != clientVect.end())
        return (&(*it));
    else
    {
        std::cerr << "client fd " << clientSocket << " not found in clientVect" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Server::closeClient(std::size_t* i, std::string message)
{
    int fdToDelete = manager->getPollRequests()[*i].fd;

    for (std::vector<Client>::iterator it = clientVect.begin(); it != clientVect.end(); ++it)
    {
        if (it->getClientSocket() == fdToDelete)
        {
            clientVect.erase(it);
            break;
        }
    }
    close(fdToDelete);
    manager->getPollRequests().erase(manager->getPollRequests().begin() + *i);
    --(*i);

    std::cerr << message << std::endl;
}

bool Server::ownsClient(int clientFd)
{
    for (std::vector<Client>::iterator it = clientVect.begin(); it != clientVect.end(); ++it)
    {
        if (it->getClientSocket() == clientFd)
            return (true);
    }
    return (false);
}

// ·············································································
// HTTP handling Methods
// ·············································································


// Sends resource to client via a buffer. Resource comes from HttpResponse object
void    Server::sendResponseBuffer(std::size_t *i, HttpResponse &response)
{
    std::string     body = response.getResponse("example_response.html");
    size_t          buffer_size = 1024;
    size_t          total_size = body.size();
    size_t          bytes_sent = 0;

    while (bytes_sent < total_size) 
    {
        size_t      chunk_size = std::min(buffer_size, total_size - bytes_sent);
        int         sent;
        
        sent = send(manager->getPollRequests()[(*i)].fd, (body.c_str() + bytes_sent), chunk_size, 0);
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
// Function Handles what happens when a socket presents a POLLIN flag 
// indicating that there is data available to read on the file descriptor.
void Server::handleClientRead(std::size_t *i)
{
    char                buffer[1024] = {0};
    int                 bytes_read;
    int                 clientFd = manager->getPollRequests()[(*i)].fd; 
    Client              *client_ptr = getClientFromSocket(clientFd);
    HttpRequest         request;
    
    client_ptr->assignRequest(&request); 
    
    while ((bytes_read = read(clientFd, buffer, sizeof(buffer))) > 0)
    {
        request.appendRequest(buffer);

        if (request.getRawRequest().find("\r\n\r\n") != std::string::npos)
        {
            std::cout << "HTTP Request saved here:\n" << request.getRawRequest() << "\nEND OF REQUEST" << std::endl;
            HttpResponse    response;
            /*
            Here we need a series of functions that parse the request 
            then create a response based on the request and on the ServerConfig values for that socket
            (according to method type, error response codes etc.)

            something like:
                request.parsing();
                response.generateResponse(&request);
            */
            client_ptr->assignResponse(&response);
            sendResponseBuffer(i, client_ptr->getCurrentResponse());
            break;
        }
    }
    if (bytes_read == 0)
        closeClient(i, "Client disconnected: bytes_read = 0");
    else if (bytes_read < 0)
        closeClient(i, "Client disconnected due to read error (bytes_read = -1)");
}

// (SERVER --> CLIENT ) : HTTP Response 
// Access the correct client object 
// in order to send the message that lies in its' write_buffer 
// over the connection of its socket (clientFd) to the server.
void    Server::handleClientWrite(std::size_t *i)
{
    int             clientFd = manager->getPollRequests()[(*i)].fd;
    ssize_t         bytes_sent;
    Client*         clientObj = getClientFromSocket(clientFd);
    
    // Send the bytes contained in the write_buffer to clientFd socket
    bytes_sent = send(clientFd, clientObj->getWriteBuffer().c_str(), clientObj->getWriteBuffer().size(), 0);
    if (bytes_sent > 0)
    {
        std::cerr << "bytes_sent > 0 " << std::endl;
        clientObj->getWriteBuffer().erase(0, bytes_sent);
    }
    if  (bytes_sent < 0)
    {   
        std::cerr << "bytes_sent < 0" << std::endl; 
        return ;
    }
    if (clientObj->getWriteBuffer().empty())
    {
        std::cerr << "write buffer is empty" << std::endl;
        manager->getPollRequests()[(*i)].events &= ~POLLOUT;
        // bitwise AND operation with opposite of POLLOUT (~ = NOT)
    } 
}

