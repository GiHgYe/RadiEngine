#pragma once
#include "component/component.h"
#include "control/input.h"

class Transform;
class Camera;

REFLECTION_TYPE(LoginScene)
CLASS(LoginScene : public Component, WhiteListFields)
{
	REFLECTION_BODY(LoginScene)
public:
	LoginScene();

	void Awake();

	void Update();

private:
    Transform* transform_cube_{};
    Transform* transform_camera_1_{};
    Camera* camera_1_{};
    Transform* transform_camera_2_{};
    Camera* camera_2_;
    vec2_ushort last_frame_mouse_position_;//上一帧的鼠标位置
};