#include "method.h"
#include "class.h"

Method::Method(const Cursor& cursor, const Namespace& current_namespace, Class* parent)
	:TypeInfo(cursor, current_namespace), m_parent(parent), m_name(cursor.GetSpelling())
{
    
}

bool Method::ShouldCompile(void) const { return isAccessible(); }

bool Method::isAccessible(void) const
{
    return (  ( m_parent->m_meta_info.Exist(NativeProperty::Methods) ||
                m_parent->m_meta_info.Exist(NativeProperty::All) ) &&
                !m_meta_info.Exist(NativeProperty::Disable)                       )   ||
                (m_parent->m_meta_info.Exist(NativeProperty::WhiteListMethods) &&
                m_meta_info.Exist(NativeProperty::Enable));
}
