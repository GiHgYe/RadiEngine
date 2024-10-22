#pragma once

#include "meta/reflection/reflection.h"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

class Component;
class GameObject
{
public:
    GameObject();
    GameObject(const std::string& name);
    ~GameObject();

    std::string& name() { return name_; }
    void set_name(std::string name) { name_ = name; }

    /// 添加组件
    /// \param component_type_name 组件类名
    /// \return Component* 
    Component* TryAddComponent(const std::string& component_type_name);

    template <class TComponent>
    TComponent* TryAddComponent(const std::string& component_type_name) {
        auto component = Reflection::ReflectionPtr(component_type_name, new TComponent);
        component->set_game_object(this);
        if (component_type_instance_map_.find(component_type_name) == component_type_instance_map_.end()) {
            std::vector<Component*> component_vec;
            component_vec.push_back(component.getPtr());
            component_type_instance_map_[component_type_name] = component_vec;
        }
        else {
            component_type_instance_map_[component_type_name].push_back(component.getPtr());
        }
        return static_cast<TComponent*>(component.getPtr());
    }

    /// 获取组件
    /// \param component_type_name 组件类名
    /// \return TComponent* 
    template<class TComponent>
    TComponent* TryGetComponent(const std::string& component_type_name) {
        if (component_type_instance_map_.find(component_type_name) == component_type_instance_map_.end()) 
		    return nullptr;
	    if (component_type_instance_map_[component_type_name].size() == 0) 
		    return nullptr;
	    return static_cast<TComponent*>(component_type_instance_map_[component_type_name][0]);
    }


    std::vector<Component*>& GetComponents(const std::string& component_type_name);


#define AddComponent(COMPONENT_TYPE) TryAddComponent<COMPONENT_TYPE>(#COMPONENT_TYPE)
#define GetComponent(COMPONENT_TYPE) TryGetComponent<COMPONENT_TYPE>(#COMPONENT_TYPE)

private:
    std::string name_;
    std::unordered_map<std::string, std::vector<Component*>> component_type_instance_map_;
};