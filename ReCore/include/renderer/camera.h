#pragma once
#include <math/math_headers.h>
#include "component/component.h"

REFLECTION_TYPE(Camera)
CLASS(Camera : public Component, WhiteListFields)
{
	REFLECTION_BODY(Camera)
public:
	Camera();
	~Camera();

	/// �������λ�� ����
	/// \param cameraFowrad �����ǰ����
	/// \param cameraUp ������Ϸ���
	void SetView(const Vector3& cameraFowrad, const Vector3& cameraUp);

	/// ���������Ұ
	/// \param fovDegrees   �����Ұ ���ӽǶ�
	/// \param aspectRatio  ���߱�
	/// \param nearClip ���ü���
	/// \param farClip  Զ�ü���
	void SetProjection(float fovDegrees, float aspectRatio, float nearClip, float farClip);

	Matrix4x4& view_mat4() { return view_mat4_; }
	Matrix4x4& projection_mat4() { return projection_mat4_; }

	/// ����������ɫ
	/// \param r
	/// \param g
	/// \param b
	/// \param a
	void set_clear_color(float r, float g, float b, float a) { clear_color_ = Vector4(r, g, b, a); }

	/// ����ˢ֡������������
	/// \param clear_flag
	void set_clear_flag(unsigned int clear_flag) { clear_flag_ = clear_flag; }

	void Clear();

	unsigned char depth() { return depth_; }

	/// ���� depth�������������
	/// \param depth �����ȣ���������Ӻ���ǰ���򣬰�depth��С���������depthԽ���Խ�ϲ㡣
	void set_depth(unsigned char depth);

	unsigned char culling_mask() { return culling_mask_; }
	void set_culling_mask(unsigned char culling_mask) { culling_mask_ = culling_mask; }

	/// ����all_camera_ʱ���ֵ����Ǹ�Camera��
	/// \return
	static Camera* current_camera() { return current_camera_; }

	/// ��������Camera
	/// \param func
	static void Foreach(std::function<void()> func);

	/// �� depth_ ����
	static void Sort();

private:
	Matrix4x4 view_mat4_;//ָ���������ͳ���
	Matrix4x4 projection_mat4_;//ָ�������Χ

	Vector4 clear_color_;//������ɫ
	unsigned int clear_flag_;//ˢ�����ݱ�־

	unsigned char depth_;			//�������
	unsigned char culling_mask_;	//������Ⱦ��ЩLayer������

	static std::vector<Camera*> all_camera_;
	static Camera* current_camera_;
};