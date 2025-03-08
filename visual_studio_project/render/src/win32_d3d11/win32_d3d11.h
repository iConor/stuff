#pragma once

#include <d3d11.h>

extern bool d3d11_init(HWND hwnd);
extern void d3d11_exit();

extern void d3d11_create_render_target();
extern void d3d11_destroy_render_target();

extern void d3d11_vsync(int enable);

extern void d3d11_clear(float* color);
extern void d3d11_swap();



// TODO: Temporary functions for getting ImGui running
extern ID3D11Device* d3d11_get_device();
extern ID3D11DeviceContext* d3d11_get_device_context();
