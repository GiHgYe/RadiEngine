#include "component/game_object.h"
#include "component/component.h"

std::list<GameObject*> GameObject::game_object_list_;

GameObject::GameObject(const std::string& name)
	: layer_(0x01)
{
	set_name(name);

	game_object_list_.push_back(this);
}

GameObject::~GameObject()
{
}

Component* GameObject::AddComponentByName(const std::string& component_type_name)
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
	component->Awake();
	return component;
}

Component* GameObject::GetComponentByName(std::string component_type_name)
{
	if (component_type_instance_map_.find(component_type_name) == component_type_instance_map_.end()) {
		return nullptr;
	}
	if (component_type_instance_map_[component_type_name].size() == 0) {
		return nullptr;
	}
	return component_type_instance_map_[component_type_name][0];
}

std::vector<Component*>& GameObject::GetComponents(const std::string& component_type_name) {
	return component_type_instance_map_[component_type_name];
}

void GameObject::ForeachComponent(std::function<void(Component* component)> func)
{
	for (auto var : component_type_instance_map_) {
		for (auto iter : var.second) {
			Component* component = iter;
			func(component);
		}
	}
}

void GameObject::Foreach(std::function<void(GameObject* game_object)> func)
{
	for (auto game_object : game_object_list_) {
		func(game_object);
	}
}
