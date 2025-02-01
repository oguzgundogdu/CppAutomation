#include "../../domain/models/Student.cpp"
#include "../postgres/PostgresqlConnection.cpp"
#include "../../extensions/DateTimeExtensions.cpp"
#include "../../extensions/UuidExtensions.cpp"
#include <ctime>
#include <uuid/uuid.h>

class StudentRepository
{
private:
    std::unique_ptr<PostgresqlConnection> m_connection;

public:
    void addStudent(Student &student)
    {
        try
        {
            uuid_t studentId;
            student.getId(studentId);
            m_connection->connect();
            std::string query = "INSERT INTO students (id, name, status, created_at, updated_at) VALUES ('" + UuidExtensions::uuidToString(studentId) + "'::uuid,'" + student.getName() + "', " + std::to_string(student.getStatus()) + ", '" + DateTimeExtensions::tmToString(student.getCreatedAt()) + "'::timestamp, '" + DateTimeExtensions::tmToString(student.getUpdatedAt()) + "'::timestamp)";
            m_connection->executeWrite(query.c_str());
            m_connection->disconnect();
        }
        catch (const std::exception &e)
        {
            m_connection->disconnect();
            std::cerr << e.what() << '\n';
            throw e;
        }
    }
    void updateStudent(Student &student)
    {
        uuid_t studentId;
        student.getId(studentId);
        m_connection->connect();
        std::string query = "UPDATE students SET name = '" + student.getName() + "', status = " + std::to_string(student.getStatus()) + ", updated_at = " + DateTimeExtensions::tmToString(student.getUpdatedAt()) + " WHERE id = '" + UuidExtensions::uuidToString(studentId) + "'::uuid";
        m_connection->executeWrite(query.c_str());
        m_connection->disconnect();
    }
    void deleteStudent(Student &student)
    {
        uuid_t studentId;
        student.getId(studentId);
        m_connection->connect();
        std::string query = "DELETE FROM students WHERE id = '" + UuidExtensions::uuidToString(studentId) + "'::uuid";
        m_connection->executeWrite(query.c_str());
        m_connection->disconnect();
    }
    Student *getStudent(const uuid_t &id)
    {
        m_connection->connect();
        std::string query = "SELECT * FROM students WHERE id = '" + UuidExtensions::uuidToString(id) + "'::timestamp";
        std::vector<std::map<std::string, std::string>> result = m_connection->executeRead(query.c_str());
        m_connection->disconnect();
        if (result.size() == 0)
        {
            return nullptr;
        }
        uuid_t studentId;
        UuidExtensions::stringToUuid(result[0]["id"], studentId);
        return new Student(studentId, result[0]["name"], std::stoi(result[0]["status"]), DateTimeExtensions::stringToTm(result[0]["created_at"]), DateTimeExtensions::stringToTm((result[0]["updated_at"])));
    }
    vector<std::shared_ptr<Student>> getStudents()
    {
        m_connection->connect();
        std::string query = "SELECT * FROM students";
        std::vector<std::map<std::string, std::string>> result = m_connection->executeRead(query.c_str());
        m_connection->disconnect();
        vector<std::shared_ptr<Student>> students;
        for (int i = 0; i < result.size(); i++)
        {
            uuid_t studentId;
            UuidExtensions::stringToUuid(result[i]["id"], studentId);
            shared_ptr<Student> s = make_shared<Student>(studentId, result[0]["name"], std::stoi(result[0]["status"]), DateTimeExtensions::stringToTm(result[0]["created_at"]), DateTimeExtensions::stringToTm((result[0]["updated_at"])));
            students.push_back(s);
        }
        return students;
    }
    StudentRepository()
    {
        m_connection = std::make_unique<PostgresqlConnection>();
    };
};
