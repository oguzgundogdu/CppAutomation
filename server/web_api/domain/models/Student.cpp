#include <iostream>
#include <string>
#include <ctime>
#include <uuid/uuid.h>
#include <cstring>
#include <json/json.h>
#include "../../extensions/DateTimeExtensions.cpp"
#include "../../extensions/UuidExtensions.cpp"

using namespace std;

class Student
{
private:
    uuid_t m_id;
    string m_name;
    int m_status;
    tm m_created_at;
    tm m_updated_at;

public:
    void setId(const uuid_t &t_id)
    {
        memcpy(m_id, t_id, sizeof(uuid_t));
    }
    void getId(uuid_t &t_id)
    {
        memcpy(t_id, m_id, sizeof(uuid_t));
    }
    void setName(const string t_name)
    {
        this->m_name = t_name;
    }
    string getName() const
    {
        return this->m_name;
    }
    void setStatus(const int t_status)
    {
        this->m_status = t_status;
    }
    int getStatus() const
    {
        return this->m_status;
    }
    void setCreatedAt(const tm t_created_at)
    {
        this->m_created_at = t_created_at;
    }
    tm getCreatedAt() const
    {
        return this->m_created_at;
    }
    void setUpdatedAt(const tm t_updated_at)
    {
        this->m_updated_at = t_updated_at;
    }
    tm getUpdatedAt() const
    {
        return this->m_updated_at;
    }
    Json::Value toJson() const
    {
        Json::Value json;
        json["id"] = UuidExtensions::uuidToString(m_id);
        json["name"] = m_name;
        json["status"] = m_status;
        json["created_at"] = DateTimeExtensions::tmToString(m_created_at);
        json["updated_at"] = DateTimeExtensions::tmToString(m_updated_at);
        return json;
    }
    Student() {};
    Student(uuid_t &t_id, string t_name, int t_status, tm t_created_at, tm t_updated_at) : m_name(t_name), m_status(t_status), m_created_at(t_created_at), m_updated_at(t_updated_at)
    {
        memcpy(m_id, t_id, sizeof(uuid_t));
    };
    Student(string t_name, bool t_status) : m_name(t_name), m_status(t_status) {};
};
