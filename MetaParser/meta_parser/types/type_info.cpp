#include "type_info.h"

TypeInfo::TypeInfo(const Cursor& cursor, const Namespace& current_namespace)
	: m_meta_info(cursor) , m_root_cursor(cursor) , m_namespace(current_namespace), is_enabled(m_meta_info.Exist(NativeProperty::Enable))
{}

const MetaInfo& TypeInfo::GetMetaData(void) const { return m_meta_info; }

std::string TypeInfo::GetSourceFile(void) const { return m_root_cursor.GetSourceFile(); }

Namespace TypeInfo::GetCurrentNamespace() const { return m_namespace; }

Cursor& TypeInfo::GetCurosr() { return m_root_cursor; }
