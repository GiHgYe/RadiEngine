#pragma once

#include <memory>
#include <string>
#include <vector>

#include <mustache.hpp>

namespace Mustache = kainjow::mustache;


class Class;
class Global;
class Function;
class Enum;

struct SchemaMoudle
{
    std::string name;

    std::vector<std::shared_ptr<Class>> classes;
};