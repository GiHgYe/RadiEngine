#pragma once
#include "type_info.h"
#include <memory>

#include "field.h"
#include "method.h"

struct BaseClass {
	BaseClass(const Cursor& cursor);
	std::string name;
};

class Class : public TypeInfo
{
	friend class Field;
	friend class Method;
	friend class MetaParser;

public:
    Class(const Cursor& cursor, const Namespace& current_namespace);

    virtual bool ShouldCompile(void) const;

    bool ShouldCompileFields(void) const;
    bool ShouldCompileMethods(void) const;

    template<typename T>
    using SharedPtrVector = std::vector<std::shared_ptr<T>>;

    std::string GetClassName(void);

    SharedPtrVector<BaseClass> m_base_classes;

public:
    std::string m_name;

    std::string m_qualified_name;

    SharedPtrVector<Field> m_fields;
    SharedPtrVector<Method> m_methods;

    std::string m_display_name;

    bool isAccessible(void) const;
};

