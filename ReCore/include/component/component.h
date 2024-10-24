#pragma once
#include "meta/reflection/reflection.h"

class GameObject;
REFLECTION_TYPE(Component)
CLASS (Component, WhiteListFields)
{
	REFLECTION_BODY(Component)
public:
	Component() {}
	virtual ~Component() {}

	GameObject* game_object() { return game_object_; }
	void set_game_object(GameObject* game_object) { game_object_ = game_object; }

	virtual void Awake() {}
	virtual void Update() {}

	/// ��Ⱦ֮ǰ
	virtual void OnPreRender() {}
	/// ��Ⱦ֮��
	virtual void OnPostRender() {}

	virtual void OnEnable() {}
	virtual void OnDisable() {}
private:
	GameObject* game_object_ = nullptr;
};
