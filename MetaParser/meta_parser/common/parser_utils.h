#pragma once

#include <vector>
#include <string>
#include <clang-c/Index.h>
#include <fstream>
#include <sstream>
#include <filesystem>

typedef std::vector<std::string> Namespace;

namespace Utils {

	static std::string toString(const CXString& str) {
		if (str.data == NULL) return "";
		std::string&& to_str = clang_getCString(str);
		clang_disposeString(str);
		return to_str;
	}

    static std::vector<std::string> split(std::string input, std::string pat)
    {
        std::vector<std::string> ret_list;
        while (true)
        {
            size_t      index = input.find(pat);
            std::string sub_list = input.substr(0, index);
            if (!sub_list.empty())
            {

                ret_list.push_back(sub_list);
            }
            input.erase(0, index + pat.size());
            if (index == std::string::npos)
            {
                break;
            }
        }
        return ret_list;
    }

    static std::string trim(const std::string& context)
    {

        std::string ret_string = context;

        ret_string = ret_string.erase(0, ret_string.find_first_not_of(" "));
        ret_string = ret_string.erase(ret_string.find_last_not_of(" ") + 1);

        return ret_string;
    }

    static std::string trim(std::string& source_string, const std::string trim_chars)
    {
        size_t left_pos = source_string.find_first_not_of(trim_chars);
        if (left_pos == std::string::npos)
        {
            source_string = std::string();
        }
        else
        {
            size_t right_pos = source_string.find_last_not_of(trim_chars);
            source_string = source_string.substr(left_pos, right_pos - left_pos + 1);
        }
        return source_string;
    }

    static std::string getNameWithoutFirstM(std::string& name)
    {
        std::string result = name;
        if (name.size() > 2 && name[0] == 'm' && name[1] == '_')
        {
            result = name.substr(2);
        }
        return result;
    }

    static void replaceAll(std::string& resource_str, std::string sub_str, std::string new_str)
    {
        std::string::size_type pos = 0;
        while ((pos = resource_str.find(sub_str)) != std::string::npos)
        {
            resource_str = resource_str.replace(pos, sub_str.length(), new_str);
        }
        return;
    }

    static std::string getStringWithoutQuot(std::string input)
    {
        size_t left = input.find_first_of('\"') + 1;
        size_t right = input.find_last_of('\"');
        if (left > 0 && right < input.size() && left < right)
        {
            return input.substr(left, right - left);
        }
        else
        {
            return input;
        }
    }

    static std::string loadFile(std::string path)
    {
        std::ifstream      iFile(path);
        std::string        line_string;
        std::ostringstream template_stream;
        if (false == iFile.is_open())
        {
            iFile.close();
            return "";
        }
        while (std::getline(iFile, line_string))
        {
            template_stream << line_string << std::endl;
        }
        iFile.close();

        return template_stream.str();
    }

    static void saveFile(const std::string& outpu_string, const std::string& output_file)
    {
        std::filesystem::path out_path(output_file);

        if (!std::filesystem::exists(out_path.parent_path()))
        {
            std::filesystem::create_directories(out_path.parent_path());
        }
        std::fstream output_file_stream(output_file, std::ios_base::out);

        output_file_stream << outpu_string << std::endl;
        output_file_stream.flush();
        output_file_stream.close();
        return;
    }

    static unsigned long formatPathString(const std::string& path_string, std::string& out_string)
    {
        unsigned int                ulRet = 0;
        auto                        local_path_string = path_string;
        std::filesystem::path       local_path;

        local_path = local_path_string;
        if (local_path.is_relative())
        {
            local_path_string = std::filesystem::current_path().string() + "/" + local_path_string;
        }

        replaceAll(local_path_string, "\\", "/");
        std::vector<std::string> subString = split(local_path_string, "/");
        std::vector<std::string> out_sub_string;
        for (auto p : subString)
        {
            if (p == "..")
            {
                out_sub_string.pop_back();
            }
            else if (p != ".")
            {
                out_sub_string.push_back(p);
            }
        }
        for (int i = 0; i < out_sub_string.size() - 1; i++)
        {
            out_string.append(out_sub_string[i] + "/");
        }
        out_string.append(out_sub_string[out_sub_string.size() - 1]);
        return 0;
    }

    static std::filesystem::path makeRelativePath(const std::filesystem::path& from, const std::filesystem::path& to)
    {
        // Start at the root path and while they are the same then do nothing then when they first
        // diverge take the remainder of the two path and replace the entire from path with ".."
        // segments.
        std::string form_complete_string;
        std::string to_complete_string;

        /*remove ".." and "."*/
        (void)formatPathString(from.string(), form_complete_string);
        (void)formatPathString(to.string(), to_complete_string);

        std::filesystem::path form_complete = form_complete_string;
        std::filesystem::path to_complete = to_complete_string;

        auto iter_from = form_complete.begin();
        auto iter_to = to_complete.begin();

        // Loop through both
        while (iter_from != form_complete.end() && iter_to != to_complete.end() && (*iter_to) == (*iter_from))
        {
            ++iter_to;
            ++iter_from;
        }

        std::filesystem::path final_path;
        while (iter_from != form_complete.end())
        {
            final_path /= "..";

            ++iter_from;
        }

        while (iter_to != to_complete.end())
        {
            final_path /= *iter_to;

            ++iter_to;
        }

        return final_path;
    }

    static std::string toUpper(std::string& source_string)
    {
        transform(source_string.begin(), source_string.end(), source_string.begin(), ::toupper);
        return source_string;
    }
    
    static void toUpperChar(char& c) {
        if ('a' <= c && c <= 'z') c -= 32;
    }

    static std::string convertNameToUpperCamelCase(const std::string& name, std::string pat)
    {
        std::string ret_string;
        auto&& name_spilts = split(name, pat);
        for (auto& split_string : name_spilts)
        {
            toUpperChar(split_string[0]);
            ret_string.append(split_string);
        }
        return ret_string;
    }

    static std::string replace(std::string& source_string, std::string sub_string, const std::string new_string)
    {
        std::string::size_type pos = 0;
        while ((pos = source_string.find(sub_string)) != std::string::npos)
        {
            source_string.replace(pos, sub_string.length(), new_string);
        }
        return source_string;
    }

    static std::string replace(std::string& source_string, char taget_char, const char new_char)
    {
        std::replace(source_string.begin(), source_string.end(), taget_char, new_char);
        return source_string;
    }

    static std::string formatQualifiedName(std::string& source_string)
    {
        Utils::replace(source_string, '<', 'L');
        Utils::replace(source_string, ':', 'S');
        Utils::replace(source_string, '>', 'R');
        Utils::replace(source_string, '*', 'P');
        return source_string;
    }

    static std::string getNameWithoutContainer(std::string name)
    {

        size_t left = name.find_first_of('<') + 1;
        size_t right = name.find_last_of('>');
        if (left > 0 && right < name.size() && left < right)
        {
            return name.substr(left, right - left);
        }
        else
        {
            return "";
        }
    }

    static std::string getFileName(std::string path)
    {
        if (path.size() < 1)
        {
            return std::string();
        }
        std::vector<std::string> result = split(path, "/");
        if (result.size() < 1)
        {
            return std::string();
        }
        return result[result.size() - 1];
    }

}