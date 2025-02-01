#include <iostream>
#include <array>
#include "../../data/repositories/StudentRepository.cpp"
#include "../../extensions/UuidExtensions.cpp"

using namespace std;

class StudentService
{
private:
    std::shared_ptr<StudentRepository> m_repository;

public:
    void addStudent(std::string name, int status) const
    {
        uuid_t studentId;
        UuidExtensions::generateUuid(studentId);

        Student *student = new Student(studentId, name, status, DateTimeExtensions::now(), DateTimeExtensions::now());
        m_repository->addStudent(*student);
        delete student;
    }
    void updateStudent(uuid_t id, std::string name, int status) const
    {
        uuid_t studentId;
        memcpy(studentId, id, sizeof(uuid_t));
        Student *student = m_repository->getStudent(studentId);
        if (student == nullptr)
        {
            throw std::runtime_error("Student not found");
        }
        student->setName(name);
        student->setStatus(status);
        m_repository->updateStudent(*student);

        delete student;
    }
    void deleteStudent(uuid_t &id) const
    {
        uuid_t studentId;
        memcpy(studentId, id, sizeof(uuid_t));
        Student *student = m_repository->getStudent(studentId);
        if (student == nullptr)
        {
            throw std::runtime_error("Student not found");
        }
        m_repository->deleteStudent(*student);

        delete student;
    }
    Student *getStudent(uuid_t &id) const
    {
        uuid_t studentId;
        memcpy(studentId, id, sizeof(uuid_t));
        return m_repository->getStudent(studentId);
    }
    std::vector<std::shared_ptr<Student>> getStudents() const
    {
        return m_repository->getStudents();
    }
    StudentService(const std::shared_ptr<StudentRepository> repository) : m_repository(repository) {}

    ~StudentService()
    {
    }
};
