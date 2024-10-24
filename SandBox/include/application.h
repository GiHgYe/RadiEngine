#pragma once
#include <string>

class Application
{
public:
    static const std::string& data_path() { return data_path_; }
    static void set_data_path(std::string data_path) { data_path_ = data_path; }
private:
    static std::string data_path_;
};