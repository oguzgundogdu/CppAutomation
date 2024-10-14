#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Student
{
    private:
        int m_id;
        string m_name;
        int m_status;
        tm m_created_at;
        tm m_updated_at;

    public:
        void setId (const int t_id) {
            this->m_id = t_id;
        }
        int getId() const {
            return this->m_id;
        }
        void setName (const string t_name) {
            this->m_name = t_name;
        }
        string getName() const {
            return this->m_name;
        }
        void setStatus (const int t_status) {
            this->m_status = t_status;
        }
        int getStatus() const {
            return this->m_status;
        }
        void setCreatedAt (const tm t_created_at) {
            this->m_created_at = t_created_at;
        }
        tm getCreatedAt() const {
            return this->m_created_at;
        }
        void setUpdatedAt (const tm t_updated_at) {
            this->m_updated_at = t_updated_at;
        }
        tm getUpdatedAt() const {
            return this->m_updated_at;
        }
        Student();
        Student(int t_id, string t_name, int t_status, tm t_created_at, tm t_updated_at): m_id(t_id), m_name(t_name), m_status(t_status), m_created_at(t_created_at), m_updated_at(t_updated_at) {};
        Student(string t_name, bool t_status): m_id(0), m_name(t_name), m_status(t_status) {};
        ~Student() {
            delete &m_id;
            delete &m_name;
            delete &m_status;
            delete &m_created_at;
            delete &m_updated_at;
        }
};
