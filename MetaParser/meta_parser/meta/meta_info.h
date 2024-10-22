#pragma once

#include <unordered_map>
#include "../cursor/cursor.h"

class MetaInfo
{
public:
	MetaInfo(const Cursor& cursor);

    std::string GetProperty(const std::string& key) const;

    bool Exist(const std::string& key) const;

private:
    typedef std::pair<std::string, std::string> Property;

    std::unordered_map<std::string, std::string> m_properties;

private:
    void extractProperties(const Cursor& cursor);


};

