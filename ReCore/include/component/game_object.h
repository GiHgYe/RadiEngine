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
    GameObject(const std::string& name);
    ~GameObject();

    std::string& name() { return name_; }
    void set_name(std::string name) { name_ = name; }

    /// ������
    /// \param component_type_name �������
    /// \return Component* 
    Component* AddComponentByName(const std::string& component_type_name);

    template <class TComponent>
    TComponent* AddComponentByName(const std::string& component_type_name) {
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
        component->Awake();
        return static_cast<TComponent*>(component.getPtr());
    }

    /// ��ȡ���
    /// \param component_type_name �������
    /// \return TComponent* 
    Component* GetComponentByName(std::string component_type_name);
    
    template<class TComponent>
    TComponent* GetComponentByName(const std::string& component_type_name) {
        if (component_type_instance_map_.find(component_type_name) == component_type_instance_map_.end()) 
		    return nullptr;
	    if (component_type_instance_map_[component_type_name].size() == 0) 
		    return nullptr;
	    return static_cast<TComponent*>(component_type_instance_map_[component_type_name][0]);
    }

    /// ��ȡ����ͬ�����
    /// \param component_type_name �������
    /// \return
    std::vector<Component*>& GetComponents(const std::string& component_type_name);

    unsigned char layer() { return layer_; }
    void set_layer(unsigned char layer) { layer_ = layer; }

    /// ��������Component
    /// \param func
    void ForeachComponent(std::function<void(Component* component)> func);

    /// ��������Camera
    /// \param func
    static void Foreach(std::function<void(GameObject* game_object)> func);

#define AddComponent(COMPONENT_TYPE) AddComponentByName<COMPONENT_TYPE>(#COMPONENT_TYPE)
#define GetComponent(COMPONENT_TYPE) GetComponentByName<COMPONENT_TYPE>(#COMPONENT_TYPE)

private:
    std::string name_;
    std::unordered_map<std::string, std::vector<Component*>> component_type_instance_map_;

    unsigned char layer_;   //������ֲ�ͬ�Ĳ㣬��������ֲ㡢������ײ�ֲ��

    static std::list<GameObject*> game_object_list_;    //�洢���е�GameObject
};