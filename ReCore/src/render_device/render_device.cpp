#include "render_device/render_device.h"

RenderDevice* RenderDevice::instance_;

void RenderDevice::Enable(RenderState render_state)
{
    render_state_map_[render_state] = true;
}

void RenderDevice::Disable(RenderState render_state)
{
    render_state_map_[render_state] = false;
}

void RenderDevice::Init(RenderDevice* instance)
{
    instance_ = instance;
}
