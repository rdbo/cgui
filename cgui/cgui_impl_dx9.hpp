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

	inline cgui_void DrawFilledTriangle(cgui_array<cgui_float, 2> vertex0, cgui_array<cgui_float, 2> vertex1, cgui_array<cgui_float, 2> vertex2, cgui_color color) final
	{
		struct D3DVERTEX
		{
			FLOAT x;
			FLOAT y;
			FLOAT z;
			FLOAT rhw;
			DWORD color;
		} vertices[3] = {  };

		vertices[0].x = vertex0[0];
		vertices[0].y = vertex0[1];
		vertices[0].z = 0.0f;
		vertices[0].rhw = 1.0f;
		vertices[0].color = D3DCOLOR_RGBA(color.Red(), color.Green(), color.Blue(), color.Alpha());

		vertices[1].x = vertex1[0];
		vertices[1].y = vertex1[1];
		vertices[1].z = 0.0f;
		vertices[1].rhw = 1.0f;
		vertices[1].color = D3DCOLOR_RGBA(color.Red(), color.Green(), color.Blue(), color.Alpha());

		vertices[2].x = vertex2[0];
		vertices[2].y = vertex2[1];
		vertices[2].z = 0.0f;
		vertices[2].rhw = 1.0f;
		vertices[2].color = D3DCOLOR_RGBA(color.Red(), color.Green(), color.Blue(), color.Alpha());

		IDirect3DVertexBuffer9 *pVertexObject = (IDirect3DVertexBuffer9 *)nullptr;
		void *pVertexBuffer = (void **)nullptr;
		this->pD3DDevice->CreateVertexBuffer(3 * sizeof(D3DVERTEX), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &pVertexObject, (HANDLE *)NULL);
		pVertexObject->Lock(0, 3 * sizeof(D3DVERTEX), &pVertexBuffer, 0);

		for (cgui_size i = 0; i < 3; ++i)
			((D3DVERTEX *)pVertexBuffer)[i] = vertices[i];

		pVertexObject->Unlock();
		this->pD3DDevice->SetStreamSource(0, pVertexObject, 0, sizeof(D3DVERTEX));
		this->pD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
		this->pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
		pVertexObject->Release();
	}

	/* Optional Override */
	inline cgui_void DrawFilledRectangle(cgui_array<cgui_float, 2> min, cgui_array<cgui_float, 2> max, cgui_color color) final
	{
		D3DRECT DXRect = { (LONG)min[0], (LONG)min[1], (LONG)max[0], (LONG)max[1] };
		this->pD3DDevice->Clear(1, &DXRect, D3DCLEAR_TARGET, D3DCOLOR_RGBA(color.Red(), color.Green(), color.Blue(), color.Alpha()), 0.0f, 0);
	}
};

#endif