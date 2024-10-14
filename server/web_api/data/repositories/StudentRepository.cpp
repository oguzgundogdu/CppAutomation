#include "../../domain/repositories/IStudentRepository.cpp"
#include "../../domain/models/Student.cpp"
#include "../DatabaseConnection.cpp"
#include "DataTimeExtensions.cpp"
#include <ctime>

class StudentRepository : public IStudentRepository
{
private:
    vector<Student> *m_students;
    std::shared_ptr<DatabaseConnection> m_connection;

public:
    void addStudent(Student &student) const override
    {
        try
        {
            m_connection->connect();
            std::string query = "INSERT INTO students (name, status, created_at, updated_at) VALUES ('" + student.getName() + "', " + std::to_string(student.getStatus()) + ", " + DataTimeExtensions::tmToString(student.getCreatedAt()) + ", " + DataTimeExtensions::tmToString(student.getUpdatedAt()) + ")";
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
    void updateStudent(Student &student) const override
    {
        m_connection->connect();
        std::string query = "UPDATE students SET name = '" + student.getName() + "', status = " + std::to_string(student.getStatus()) + ", updated_at = " + DataTimeExtensions::tmToString(student.getUpdatedAt()) + " WHERE id = " + std::to_string(student.getId());
        m_connection->executeWrite(query.c_str());
        m_connection->disconnect();
    }
    void deleteStudent(Student &student) const override
    {
        m_connection->connect();
        std::string query = "DELETE FROM students WHERE id = " + std::to_string(student.getId());
        m_connection->executeWrite(query.c_str());
        m_connection->disconnect();
    }
    Student *getStudent(int id) const override
    {
        m_connection->connect();
        std::string query = "SELECT * FROM students WHERE id = " + std::to_string(id);
        std::vector<std::map<std::string, std::string>> result = m_connection->executeRead(query.c_str());
        m_connection->disconnect();
        if (result.size() == 0)
        {
            return nullptr;
        }
        return new Student(std::stoi(result[0]["id"]), result[0]["name"], std::stoi(result[0]["status"]), DataTimeExtensions::stringToTm(result[0]["created_at"]), DataTimeExtensions::stringToTm((result[0]["updated_at"])));
    }
    vector<Student> getStudents() const override
    {
        m_connection->connect();
        std::string query = "SELECT * FROM students";
        std::vector<std::map<std::string, std::string>> result = m_connection->executeRead(query.c_str());
        m_connection->disconnect();
        vector<Student> students;
        for (int i = 0; i < result.size(); i++)
        {
            students.push_back(new Student(std::stoi(result[0]["id"]), result[0]["name"], std::stoi(result[0]["status"]), DataTimeExtensions::stringToTm(result[0]["created_at"]), DataTimeExtensions::stringToTm((result[0]["updated_at"]))));
        }
        return students;
    }
    StudentRepository(std::shared_ptr<DatabaseConnection> t_connection) : m_connection(t_connection) {};
    ~StudentRepository()
    {
        delete m_students;
        m_students = nullptr;
        delete this;
    }
};
