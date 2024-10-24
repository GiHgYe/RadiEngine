#pragma once
#include <iostream>
#include <vector>
#include "component/component.h"

class Texture2D;

REFLECTION_TYPE(UIImage)
CLASS(UIImage : public Component, WhiteListFields)
{
	REFLECTION_BODY(UIImage)
public:
	UIImage();
	~UIImage() override;

	Texture2D* texture2D() { return texture2D_; }
	void set_texture(Texture2D * texture2D) { texture2D_ = texture2D; }

public:
	void Awake() override;
	void Update() override;

private:
	Texture2D* texture2D_ = nullptr;
};
