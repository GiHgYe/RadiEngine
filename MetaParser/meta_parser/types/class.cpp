#include "class.h"

BaseClass::BaseClass(const Cursor& cursor) : name(cursor.GetType().GetDisplayName()) {}

Class::Class(const Cursor& cursor, const Namespace& current_namespace)
	: TypeInfo(cursor, current_namespace), m_name(cursor.GetDisplayName())
	, m_qualified_name(cursor.GetType().GetDisplayName())
	, m_display_name(Utils::getNameWithoutFirstM(m_qualified_name))
{
	Utils::replaceAll(m_name, " ", "");
	//Utils::replaceAll(m_name, "GameEngine::", "");

	auto childrens = cursor.GetChildren();
	for (auto& child : childrens) {
		CXCursorKind kind = child.GetKind();
		switch (kind)
		{
		case CXCursor_CXXBaseSpecifier:
			m_base_classes.emplace_back(new BaseClass(child));
			break;
		case CXCursor_FieldDecl:
			m_fields.emplace_back(new Field(child, current_namespace, this));
			break;
		case CXCursor_CXXMethod:
			m_methods.emplace_back(new Method(child, current_namespace, this));
			break;
		default:
			break;
		}
	}
}

bool Class::ShouldCompile(void) const { return ShouldCompileFields() || ShouldCompileMethods(); }

bool Class::ShouldCompileFields(void) const
{
	return m_meta_info.Exist(NativeProperty::All) || 
		   m_meta_info.Exist(NativeProperty::Fields) ||
		   m_meta_info.Exist(NativeProperty::WhiteListFields);
}

bool Class::ShouldCompileMethods(void) const
{
	return  m_meta_info.Exist(NativeProperty::All) ||
			m_meta_info.Exist(NativeProperty::Methods) ||
			m_meta_info.Exist(NativeProperty::WhiteListMethods);
}

std::string Class::GetClassName(void) { return m_name; }

bool Class::isAccessible(void) const { return is_enabled; }
