#include "render_device/render_device_opengl.h"
#include <glad.h>
#include "utils/debug.h"

void RenderDeviceOpenGL::Enable(RenderState render_state)
{
    if (render_state_map_.find(render_state) != render_state_map_.end() && render_state_map_[render_state] == true) {
        return;
    }
    switch (render_state) {
    case None:
        break;
    case STENCIL_TEST:
        glEnable(GL_STENCIL_TEST);
        break;
    }
    __CHECK_GL_ERROR__;
    RenderDevice::Enable(render_state);
}

void RenderDeviceOpenGL::Disable(RenderState render_state)
{
    if (render_state_map_.find(render_state) != render_state_map_.end() && render_state_map_[render_state] == false) {
        return;
    }
    switch (render_state) {
    case None:
        break;
    case STENCIL_TEST:
        glDisable(GL_STENCIL_TEST);
        break;
    }
    __CHECK_GL_ERROR__;
    RenderDevice::Disable(render_state);
}
