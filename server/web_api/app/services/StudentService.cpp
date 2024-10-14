#include <iostream>
#include "IStudentRepository.cpp"
#include "StudentRepository.cpp"

class StudentService
{
private:
    std::shared_ptr<IStudentRepository> m_repository;

public:
    void addStudent(std::string name, int status) const
    {
        Student *student = new Student(name, status);
        m_repository->addStudent(*student);

        delete student;
    }
    void updateStudent(int id, std::string name, int status) const
    {
        Student *student = m_repository->getStudent(id);
        if (student == nullptr)
        {
            throw std::runtime_error("Student not found");
        }
        student->setName(name);
        student->setStatus(status);
        m_repository->updateStudent(*student);

        delete student;
    }
    void deleteStudent(int id) const
    {
        Student *student = m_repository->getStudent(id);
        if (student == nullptr)
        {
            throw std::runtime_error("Student not found");
        }
        m_repository->deleteStudent(*student);

        delete student;
    }
    Student *getStudent(int id) const
    {
        return m_repository->getStudent(id);
    }
    std::vector<Student> getStudents() const
    {
        return m_repository->getStudents();
    }
    StudentService(const std::shared_ptr<IStudentRepository> repository) : m_repository(repository) {}

    ~StudentService()
    {
    }
};
