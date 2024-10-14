#include <iostream>
#include <map>

class DatabaseConnection
{
    public:
        virtual void connect() = 0;
        virtual void disconnect() = 0;
        virtual std::vector<std::map<std::string, std::string>> executeRead(const char *query) = 0;
        virtual void executeWrite(const char *query) = 0;
};