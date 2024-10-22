#include "field.h"
#include "class.h"

Field::Field(const Cursor& cursor, const Namespace& current_namespace, Class* parent)
	: TypeInfo(cursor, current_namespace), m_parent(parent), m_is_const(cursor.GetType().IsConst())
	, m_name(cursor.GetSpelling()), m_display_name(Utils::getNameWithoutFirstM(m_name))
	, m_type(cursor.GetType().GetDisplayName())
{
	Utils::replaceAll(m_name, " ", "");
	//Utils::replaceAll(m_name, "GameEngine::", "");

	auto ret_string = Utils::getStringWithoutQuot(m_meta_info.GetProperty("default"));
	m_default = ret_string;

}

bool Field::ShouldCompile(void) const { return isAccessible(); }

bool Field::isAccessible(void) const
{
	return ((m_parent->m_meta_info.Exist(NativeProperty::All) || m_parent->m_meta_info.Exist(NativeProperty::Fields))
					&& !m_meta_info.Exist(NativeProperty::Disable)) ||
		   (m_parent->m_meta_info.Exist(NativeProperty::WhiteListFields) && m_meta_info.Exist(NativeProperty::Enable));
}
