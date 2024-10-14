#include <libpq-fe.h>
#include <iostream>
#include <map>
#include "../DatabaseConnection.cpp"

class PostgresqlConnection : public DatabaseConnection
{
    private:
        char *conn_str = nullptr;
        PGconn *conn = nullptr;

    public:
        void connect() override {
            conn = PQconnectdb(conn_str);
            if (PQstatus(conn) != CONNECTION_OK) {
                fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
                PQfinish(conn);
            }
        }
        void disconnect() override {
            PQfinish(conn);
            delete conn;
            conn = nullptr;
        }
        std::vector<std::map<std::string, std::string>> executeRead(const char *query) override {
            std::vector<std::map<std::string, std::string>> result;
            PGresult *res = PQexec(conn, query);
            if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
                PQclear(res);
                return result;
            }
            int rows = PQntuples(res);
            int cols = PQnfields(res);
            for (int i = 0; i < rows; i++) {
                std::map<std::string, std::string> row;
                for (int j = 0; j < cols; j++) {
                    row[PQfname(res, j)] = PQgetvalue(res, i, j);
                }
                result.push_back(row);
            }
            PQclear(res);
            delete res;
            return result;
        }
        void executeWrite(const char *query) override {
            PGresult *res = PQexec(conn, query);
            if (PQresultStatus(res) != PGRES_COMMAND_OK) {
                throw std::runtime_error(PQerrorMessage(conn));
            }
            PQclear(res);
        }
        PostgresqlConnection()
        {
            conn_str = "host=localhost port=5432 dbname=postgres user=postgres password=postgres";
        }
        ~PostgresqlConnection()
        {
            delete conn_str;
            delete conn;

            conn_str = nullptr;
            conn = nullptr;
        }
};