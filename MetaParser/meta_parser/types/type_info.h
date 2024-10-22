#pragma once

#include "../meta/meta_info.h"
#include "../meta/meta_config.h"


class MetaInfo;

class TypeInfo
{
public:
    TypeInfo(const Cursor& cursor, const Namespace& current_namespace);
    virtual ~TypeInfo(void) {}

    const MetaInfo& GetMetaData(void) const;

    std::string GetSourceFile(void) const;

    Namespace GetCurrentNamespace() const;

    Cursor& GetCurosr();

protected:
    MetaInfo m_meta_info;

	Namespace m_namespace;

	bool is_enabled;

private:
	Cursor m_root_cursor;
};

