#include "control/input.h"
#include <iostream>
#include <assert.h>
#include "control/key_code.h"

std::unordered_map<unsigned short, unsigned char> Input::key_event_map_;
vec2_ushort Input::mouse_position_ = { 0,0 };
short Input::mouse_scroll_ = 0;

bool Input::GetKey(unsigned short key_code)
{
	return key_event_map_.count(key_code) > 0;
}

bool Input::GetKeyDown(unsigned short key_code)
{
	if (key_event_map_.count(key_code) == 0) {
		return false;
	}
	return key_event_map_[key_code] != KEY_ACTION_UP;
}

bool Input::GetKeyUp(unsigned short key_code)
{
	if (key_event_map_.count(key_code) == 0) {
		return false;
	}
	return key_event_map_[key_code] == KEY_ACTION_UP;
}

void Input::RecordKey(int key_code, unsigned char key_action)
{
	if (key_code < 0) {
		assert(false);
		return;
	}
	key_event_map_[key_code] = key_action;
}

bool Input::GetMouseButton(unsigned short mouse_button_index)
{
	return GetKey(mouse_button_index);
}

bool Input::GetMouseButtonDown(unsigned short mouse_button_index)
{
	return GetKeyDown(mouse_button_index);
}

bool Input::GetMouseButtonUp(unsigned short mouse_button_index)
{
	return GetKeyUp(mouse_button_index);
}

void Input::Update()
{
	for (auto iterator = key_event_map_.begin(); iterator != key_event_map_.end();) {
		if (iterator->second == KEY_ACTION_UP) {
			iterator = key_event_map_.erase(iterator);    //ɾ��Ԫ�أ�����ֵָ����ɾ��Ԫ�ص���һ��λ��
		}
		else {
			++iterator;    //ָ����һ��λ��
		}
	}
	mouse_scroll_ = 0;
}