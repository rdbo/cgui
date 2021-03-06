/*
 * ====================================
 * =          CGUI - by rdbo          =
 * =      Universal Graphics API      =
 * ====================================
 */

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
	inline IDirect3DDevice9 *GetDevice()
	{
		return this->pD3DDevice;
	}
public:
	/* Mandatory Override */
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

	inline cgui_void DrawFont(cgui_string text, cgui_font font, cgui_array<cgui_float, 2> position, cgui_color color) final
	{
		LPD3DXFONT DXFont = (LPD3DXFONT)font.data();
		RECT Rect = {  };
		DXFont->DrawTextA((LPD3DXSPRITE)NULL, text.c_str(), text.length(), &Rect, DT_CALCRECT, D3DCOLOR_RGBA(color.Red(), color.Green(), color.Blue(), color.Alpha()));
		DXFont->DrawTextA((LPD3DXSPRITE)NULL, text.c_str(), text.length(), &Rect, DT_NOCLIP, D3DCOLOR_RGBA(color.Red(), color.Green(), color.Blue(), color.Alpha()));
	}

	/* Optional Override */
	inline cgui_void DrawFilledRectangle(cgui_array<cgui_float, 2> min, cgui_array<cgui_float, 2> max, cgui_color color) final
	{
		D3DRECT DXRect = { (LONG)min[0], (LONG)min[1], (LONG)max[0], (LONG)max[1] };
		this->pD3DDevice->Clear(1, &DXRect, D3DCLEAR_TARGET, D3DCOLOR_RGBA(color.Red(), color.Green(), color.Blue(), color.Alpha()), 0.0f, 0);
	}
};

class cgui_font_dx9 : public cgui_font
{
	/*
	 * DirectX 9 Font
	 */
public:
	inline cgui_font_dx9(cgui_handle_dx9 handle, cgui_string font_name, cgui_size size, cgui_bool bold, cgui_bool italic)
	{
		IDirect3DDevice9 *pD3DDevice = handle.GetDevice();
		D3DXCreateFontA(pD3DDevice, size, 0, (bold ? FW_BOLD : FW_REGULAR), 0, (BOOL)italic, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, font_name.c_str(), (LPD3DXFONT *)&this->buf);
	}

	inline ~cgui_font_dx9()
	{
		if (this->buf)
		{
			LPD3DXFONT DXFont = (LPD3DXFONT)this->buf;
			DXFont->Release();
		}
	}
};

#endif
