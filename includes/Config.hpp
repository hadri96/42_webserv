#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <vector>

class Config
{
    public:
    // --- Constructors and Destructor ---
        Config() : numberOfServers(3), ports(3) 
        {
            ports[0] = 8084;
            ports[1] = 8085;
            ports[2] = 8086;
        }
        ~Config() {}

    // --- Public Methods ---
        int getNumber() const { return numberOfServers; }
        int getPort(int i) const 
        { 
            if (i >= 0 && i < numberOfServers)
                return (ports[i]);
            return (-1);
        }

    private:
    // --- Private Attributes ---
        int                 numberOfServers;
        std::vector<int>    ports;
};

#endif
