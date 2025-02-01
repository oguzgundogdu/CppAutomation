#include <libpq-fe.h>
#include <iostream>
#include <map>
#include <vector>
#include <stdexcept>

#include "../DatabaseConnection.cpp"

class PostgresqlConnection : public DatabaseConnection
{
private:
    std::string conn_str = "host=localhost port=5432 dbname=cpp user=postgres password=postgres gssencmode=disable";
    PGconn *conn = nullptr;

public:
    PostgresqlConnection() = default;

    void connect() override
    {
        conn = PQconnectdb(conn_str.c_str());
        if (PQstatus(conn) != CONNECTION_OK)
        {
            std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
            PQfinish(conn);
            conn = nullptr;
        }
    }

    void disconnect() override
    {
        if (conn)
        {
            PQfinish(conn);
            conn = nullptr;
        }
    }

    std::vector<std::map<std::string, std::string>> executeRead(const char *query) override
    {
        std::vector<std::map<std::string, std::string>> result;
        if (!conn)
            throw std::runtime_error("No active database connection");

        PGresult *res = PQexec(conn, query);
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
            std::cerr << "Query failed: " << PQerrorMessage(conn) << std::endl;
            PQclear(res);
            return result;
        }

        int rows = PQntuples(res);
        int cols = PQnfields(res);
        for (int i = 0; i < rows; i++)
        {
            std::map<std::string, std::string> row;
            for (int j = 0; j < cols; j++)
            {
                row[PQfname(res, j)] = PQgetvalue(res, i, j);
            }
            result.push_back(row);
        }
        PQclear(res);
        return result;
    }

    void executeWrite(const char *query) override
    {
        if (!conn)
            throw std::runtime_error("No active database connection");

        PGresult *res = PQexec(conn, query);
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            std::string error_msg = PQerrorMessage(conn);
            PQclear(res);
            throw std::runtime_error(error_msg);
        }
        PQclear(res);
    }

    ~PostgresqlConnection()
    {
        disconnect(); // Bağlantıyı güvenli şekilde kapat
    }
};