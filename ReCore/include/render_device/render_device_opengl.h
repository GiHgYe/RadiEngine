#pragma once
#include "render_device/render_device.h"

class RenderDeviceOpenGL : public RenderDevice
{
public:
	void Enable(RenderState render_state) override;

	void Disable(RenderState render_state) override;
};