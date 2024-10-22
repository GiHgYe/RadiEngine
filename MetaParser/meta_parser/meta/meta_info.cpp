#include "meta_info.h"

MetaInfo::MetaInfo(const Cursor& cursor)
{
	for (auto& child : cursor.GetChildren())
	{
		if (child.GetKind() != CXCursor_AnnotateAttr)
			continue;

		extractProperties(child);
	}
}

std::string MetaInfo::GetProperty(const std::string& key) const
{
	auto search = m_properties.find(key);
	return search == m_properties.end() ? "" : search->second;
}

bool MetaInfo::Exist(const std::string& key) const { return m_properties.find(key) != m_properties.end(); }

void MetaInfo::extractProperties(const Cursor& cursor)
{
	std::vector<Property> ret_list;

	auto propertyList = cursor.GetDisplayName();

	auto&& properties = Utils::split(propertyList, ",");

	static const std::string white_space_string = " \t\r\n";

	for (auto& property_item : properties)
	{
		auto&& item_details = Utils::split(property_item, ":");
		auto&& temp_string = Utils::trim(item_details[0], white_space_string);
		if (temp_string.empty())
		{
			continue;
		}
		m_properties[temp_string] = item_details.size() > 1 ? Utils::trim(item_details[1], white_space_string) : "";
	}
}
