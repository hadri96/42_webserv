#ifndef HTTP_STATUS_CODE_HPP
# define HTTP_STATUS_CODE_HPP

# include <string>
# include <vector>

class   HttpStatusCode
{
    public:
        // --- Constructors and Destructor ---
                                    HttpStatusCode(void);
                                    HttpStatusCode(const HttpStatusCode& other);

                                    ~HttpStatusCode(void);

        // --- Operators Overload ---
        HttpStatusCode&             operator=(const HttpStatusCode& rhs);

        // --- Public Methods ---
        std::string                 getStatusLine(int code);
        std::string                 getMessage(int code);

    private:
        // --- Private Attributes ---
        std::vector<int>            code_;
        std::vector<std::string>    statusLine_;
        std::vector<std::string>    message_;

        // --- Private Methods ---
        void                        addStatusCode(int code, std::string statusLine, std::string message);
};

#endif
