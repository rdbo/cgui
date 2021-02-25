/*
 * ====================================
 * =          CGUI - by rdbo          =
 * =      Universal Graphics API      =
 * ====================================
 */

#include "cgui.hpp"

/* Implementations */
#if CGUI_IMPL_DX9
cgui_handle *CGUI_Init_DX9(IDirect3DDevice9 *pD3DDevice)
{
    cgui_handle *handle = (cgui_handle *)NULL;
    if (!pD3DDevice) return handle;
    cgui_dx9_handle *dx9_handle = new cgui_dx9_handle(pD3DDevice);
    handle = (cgui_handle *)dx9_handle;
    return handle;
}
#endif

/* CGUI */
cgui_void CGUI_Shutdown(cgui_handle *handle)
{
    if (!handle) return;
    delete handle;
}

cgui_void cgui::draw_line(cgui_handle *handle, cgui_vec2 point0, cgui_vec2 point1, cgui_color color, cgui_float thickness)
{
    if (!handle) return;

    switch(handle->api)
    {
#       if CGUI_IMPL_DX9
        case CGUI_API_DX9:
        {
            cgui_dx9_handle *dx9_handle = (cgui_dx9_handle *)handle;
            ID3DXLine *dxline = (ID3DXLine *)NULL;
            D3DXCreateLine(dx9_handle->pD3DDevice, &dxline);
            if (!dxline) break;
            D3DXVECTOR2 points[2] = {};
            points[0] = D3DXVECTOR2(point0.x, point0.y);
            points[1] = D3DXVECTOR2(point1.x, point1.y);
            dxline->SetWidth(thickness);
            dxline->Draw(points, 2, D3DCOLOR_RGBA(color.red, color.green, color.blue, color.alpha));
            dxline->Release();
        }
        break;
#       endif
    }
}

cgui_void cgui::draw_rect(cgui_handle *handle, cgui_vec2 min, cgui_vec2 max, cgui_color color, cgui_float thickness)
{
    if (!handle) return;

    cgui_vec2 p0 = cgui_vec2(min.x, min.y);
    cgui_vec2 p1 = cgui_vec2(min.x, max.y);
    cgui_vec2 p2 = cgui_vec2(max.x, max.y);
    cgui_vec2 p3 = cgui_vec2(max.x, min.y);

    cgui::draw_line(handle, p0, p1, color, thickness);
    cgui::draw_line(handle, p1, p2, color, thickness);
    cgui::draw_line(handle, p2, p3, color, thickness);
    cgui::draw_line(handle, p3, p0, color, thickness);
}

cgui_void cgui::draw_filled_rect(cgui_handle *handle, cgui_vec2 min, cgui_vec2 max, cgui_color color)
{
    if (!handle) return;

    switch (handle->api)
    {
#       if CGUI_IMPL_DX9
        case CGUI_API_DX9:
        {
            cgui_dx9_handle *dx9_handle = (cgui_dx9_handle *)handle;
            D3DRECT dxrect = { min.x, min.y, max.x, max.y };
            dx9_handle->pD3DDevice->Clear(1, &dxrect, D3DCLEAR_TARGET, D3DCOLOR_RGBA(color.red, color.green, color.blue, color.alpha), 0.0f, 0);
        }
        break;
#       endif
    }
}

cgui_void cgui::draw_circle(cgui_handle *handle, cgui_vec2 center, cgui_float radius, cgui_color color, cgui_float thickness)
{
    if (!handle || radius == 0.0f) return;

    switch (handle->api)
    {
#       if CGUI_IMPL_DX9
        case CGUI_API_DX9:
        {
            int sides = (int)(CGUI_CIRCLE_SIDES * radius);
            float angle = D3DX_PI * 2 / sides;
            float cosine = cos(angle);
            float sine = sin(angle);

            float x1 = radius;
            float x2 = 0.0f;
            float y1 = 0.0f;
            float y2 = 0.0f;

            for (int i = 0; i < sides; ++i)
            {
                x2 = cosine * x1 - sine * y1 + center.x;
                y2 = sine * x1 + cosine * y1 + center.y;
                x1 += center.x;
                y1 += center.y;
                cgui::draw_line(handle, cgui_vec2(x1, y1), cgui_vec2(x2, y2), color, thickness);
                x1 = x2 - center.x;
                y1 = y2 - center.y;
            }
        }
        break;
#       endif
    }
}