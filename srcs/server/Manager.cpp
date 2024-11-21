#include "../../includes/webserv.hpp"

// =============================================================================
// Constructors & Destructors
// =============================================================================

Manager::Manager() {};

Manager::~Manager() {};

// =============================================================================
// Public Methods
// =============================================================================

void    Manager::initialise(Config& config)
{
    // Server Block Loop:
    for (int i = 0; i < config.getNumber(); i++) 
    {
        Server      serverBlock(this);
        int         serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        
        serverBlock.applyConfig(config, i);

        if (serverSocket == 0)
        {
            std::cerr << "Socket failed" << std::endl;
            exit(EXIT_FAILURE);
        }
        serverBlock.setServerSock(serverSocket);
        serverBlock.bindSocket();
        serverBlock.listenOnPort();
        serverVect.push_back(serverBlock);

        // Add a pollfd for the server socket to the pollfd vector 
        pollfd      serverPollFd;

        serverPollFd.fd = serverSocket;
        serverPollFd.events = POLLIN; // POLLIN means that there is data to read on this fd
        pollRequests.push_back(serverPollFd);

        // Set server to non blocking:
        // Set O_NONBLOCK and FD_CLOEXEC (close on exec) flags at the same time using F_SETFL
        if (fcntl(serverSocket, F_SETFL, O_NONBLOCK | FD_CLOEXEC) == -1) 
        {
            std::cerr << "fcntl failed" << std::endl;
            exit(EXIT_FAILURE);
        }
        // the bitwise OR operator makes sure that the existing flags are not modified, just the O_NONBLOCK and FD_CLOEXEC added.
    }
}

// This function handles the read and write events on the respective server blocks
void    Manager::handleEvent(std::size_t *i)
{
    std::size_t j;

    for (j = 0; j < serverVect.size(); ++j)
    {
        if (serverVect[j].ownsClient(pollRequests[(*i)].fd))
            break;
    }
    // Handle client socket events
    std::cout << "Handle client socket events for server " << j << std::endl;
    if (pollRequests[(*i)].revents & POLLIN)
        serverVect[j].handleClientRead(i);
    if (pollRequests[(*i)].revents & POLLOUT)
        serverVect[j].handleClientWrite(i);
    if (pollRequests[(*i)].revents & POLLHUP)
        serverVect[j].closeClient(i, "Client disconnected (POLLHUP)");
    if (pollRequests[(*i)].revents & POLLERR)
        serverVect[j].closeClient(i, "Error in socket (POLLERR)");
}

// The Manager::run() function serves as the main server event loop. 
// It first sets up the server and then continuously waits for events on a set of file descriptors using the poll() system call. 
// The function processes incoming connections and data from clients by iterating over the array of pollfd structures, 
// checking the revents field to determine if a file descriptor is ready for reading / writing, has been disconnected, or encountered an error.
void    Manager::run()
{
    while (true)
    {
        int poll_count = poll(pollRequests.data(), pollRequests.size(), -1); // -1 means infinite timeout

        if (poll_count < 0)
        {
            std::cerr << "Poll failed" << std::endl;
            break;
        }
        for (std::size_t i = 0; i < pollRequests.size(); i++)
        {
            // Check if the fd belongs to a server socket
            bool            isServerSocket = false;
            std::size_t     j;

            // skip if no events
            if (pollRequests[i].revents == 0)
                continue;
            for (j = 0; j < serverVect.size(); ++j)
            {
                if (pollRequests[i].fd == serverVect[j].getServerSock())
                {
                    isServerSocket = true;
                    break;
                }
            }
            if (isServerSocket)
            {
                if (pollRequests[i].revents & POLLIN)
                    serverVect[j].connectNewClientToServer();
            }
            else
                handleEvent(&i);
        }
    }
}


// =============================================================================
// Private Methods
// =============================================================================



// ·············································································
// Setup Methods
// ·············································································



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

Handling the Server Socket (serverSocket):
If the server socket (serverSocket) is ready, it means a new client is trying to connect.
The server calls accept() to establish the connection and create a new client socket FD (clientSocket).
This new client FD is added to pollRequests, and a new entry is created in clientMap to store information about the client.

Handling Existing Client FDs:
If the ready FD is not the server socket, it means an existing client has sent data.
The server reads data from the client socket using read().
If read() returns 0 or less, the client has disconnected, so the server closes the connection and removes the client FD from pollRequests.
Otherwise, it processes the received data and displays it.


    The first pollfd is tied to the server socket (serverSocket), and is set up to monitor
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