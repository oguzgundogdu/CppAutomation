#include <uuid/uuid.h>
#include <string>
#include <array>

#pragma once

using namespace std;

class UuidExtensions
{
public:
    static string uuidToString(const uuid_t &uuid)
    {
        char str[37];
        uuid_unparse(uuid, str);
        return string(str);
    }

    static void stringToUuid(const string &uuidStr, uuid_t &uuid)
    {
        uuid_parse(uuidStr.c_str(), uuid);
    }

    static void generateUuid(uuid_t &uuid)
    {
        uuid_generate(uuid);
    }
};