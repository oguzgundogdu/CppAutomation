#include "../models/Student.cpp"

class IStudentRepository
{
    public:
        virtual void addStudent(Student& student) const = 0;
        virtual void updateStudent(Student& student) const = 0;
        virtual void deleteStudent(Student& student) const = 0;
        virtual Student* getStudent(int id) const = 0;
        virtual vector<Student> getStudents() const = 0;
};