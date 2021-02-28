#ifndef CGUI_IMPL_DX9_HPP
#define CGUI_IMPL_DX9_HPP
#include <d3d9.h>
#include <d3dx9.h>
#include "cgui.hpp"

class cgui_handle_dx9 : public cgui_handle
{
private:
    IDirect3DDevice9 *pD3DDevice = (IDirect3DDevice9 *)nullptr;
public:
    cgui_handle_dx9(IDirect3DDevice9 *pD3DDevice9)
    {
        this->pD3DDevice = pD3DDevice9;
    }

    ~cgui_handle_dx9()
    {

    }
public:
    inline cgui_void DrawLine(cgui_array<cgui_float, 2> point0, cgui_array<cgui_float, 2> point1, cgui_color color, cgui_float thickness) final
    {
        ID3DXLine *pD3DXLine = (ID3DXLine *)nullptr;
        D3DXCreateLine(this->pD3DDevice, &pD3DXLine);
        if (pD3DXLine)
        {
            D3DXVECTOR2 points[2] = {};
            points[0] = { (FLOAT)point0[0], (FLOAT)point0[1] };
            points[1] = { (FLOAT)point1[0], (FLOAT)point1[1] };

            pD3DXLine->SetWidth(thickness);
            pD3DXLine->Draw(points, 2, D3DCOLOR_RGBA(color.Red(), color.Green(), color.Blue(), color.Alpha()));
            pD3DXLine->Release();
        }
    }
};

#endif