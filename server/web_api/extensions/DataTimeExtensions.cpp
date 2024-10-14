#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

class DataTimeExtensions
{
public:
    static std::string tmToString(const std::tm &tm)
    {
        std::ostringstream ss;
        ss << (tm.tm_year + 1900) << '-'                                  
           << std::setw(2) << std::setfill('0') << (tm.tm_mon + 1) << '-' 
           << std::setw(2) << std::setfill('0') << tm.tm_mday << ' '
           << std::setw(2) << std::setfill('0') << tm.tm_hour << ':'
           << std::setw(2) << std::setfill('0') << tm.tm_min << ':'
           << std::setw(2) << std::setfill('0') << tm.tm_sec;
        return ss.str();
    }

    static std::tm stringToTm(const std::string &datetimeStr)
    {
        std::tm tm = {};
        std::istringstream ss(datetimeStr);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        return tm;
    }
};