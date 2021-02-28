#ifndef CGUI_IMPL_DX9_HPP
#define CGUI_IMPL_DX9_HPP
#include <d3d9.h>
#include <d3dx9.h>
#include "cgui.hpp"

class cgui_handle_dx9 : public cgui_handle
{
    /*
     * DirectX 9 CGUI Handle
     */
private:
    IDirect3DDevice9 *pD3DDevice = (IDirect3DDevice9 *)nullptr;
public:
    inline cgui_handle_dx9(IDirect3DDevice9 *pD3DDevice9)
    {
        this->pD3DDevice = pD3DDevice9;
    }

    inline ~cgui_handle_dx9()
    {

    }
public:
    inline cgui_void DrawLine(cgui_array<cgui_float, 2> point0, cgui_array<cgui_float, 2> point1, cgui_color color, cgui_float thickness) final
    {
        ID3DXLine *pDXLine = (ID3DXLine *)nullptr;
        D3DXCreateLine(this->pD3DDevice, &pDXLine);
        if (pDXLine)
        {
            D3DXVECTOR2 points[2] = {};
            points[0] = { (FLOAT)point0[0], (FLOAT)point0[1] };
            points[1] = { (FLOAT)point1[0], (FLOAT)point1[1] };

            pDXLine->SetWidth(thickness);
            pDXLine->Draw(points, 2, D3DCOLOR_RGBA(color.Red(), color.Green(), color.Blue(), color.Alpha()));
            pDXLine->Release();
        }
    }

    inline cgui_void DrawFilledRectangle(cgui_array<cgui_float, 2> min, cgui_array<cgui_float, 2> max, cgui_color color) final
    {
        D3DRECT DXRect = { (LONG)min[0], (LONG)min[1], (LONG)max[0], (LONG)max[1] };
        this->pD3DDevice->Clear(1, &DXRect, D3DCLEAR_TARGET, D3DCOLOR_RGBA(color.Red(), color.Green(), color.Blue(), color.Alpha()), 0.0f, 0);
    }
};

#endif