#include "component/game_object.h"
#include "component/component.h"

GameObject::GameObject()
{

}

GameObject::GameObject(const std::string& name)
{
	set_name(name);
}

GameObject::~GameObject()
{
}

Component* GameObject::TryAddComponent(const std::string& component_type_name)
{
	Component* component = static_cast<Component*>(Reflection::TypeMeta::newInstance(component_type_name));
	if (!component) return nullptr;

	component->set_game_object(this);
	Reflection::ReflectionPtr ptr(component_type_name, component);
	
	if (component_type_instance_map_.find(component_type_name) == component_type_instance_map_.end()) {
		std::vector<Component*> component_vec;
		component_vec.push_back(component);
		component_type_instance_map_[component_type_name] = component_vec;
	}
	else {
		component_type_instance_map_[component_type_name].push_back(component);
	}
	return component;
}

//Component* GameObject::GetComponent(std::string component_type_name)
//{
//	if (component_type_instance_map_.find(component_type_name) == component_type_instance_map_.end()) {
//		return nullptr;
//	}
//	if (component_type_instance_map_[component_type_name].size() == 0) {
//		return nullptr;
//	}
//	return component_type_instance_map_[component_type_name][0].getPtr();
//}

std::vector<Component*>& GameObject::GetComponents(const std::string& component_type_name)
{
	return component_type_instance_map_[component_type_name];
}
