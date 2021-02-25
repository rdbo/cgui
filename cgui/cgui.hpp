/*
 * ====================================
 * =          CGUI - by rdbo          =
 * =      Universal Graphics API      =
 * ====================================
 */

#ifndef CGUI_HPP
#define CGUI_HPP

/* Implementation Settings */
#define CGUI_IMPL_DX9     1
#define CGUI_IMPL_DX10    0
#define CGUI_IMPL_DX11    0
#define CGUI_IMPL_DX12    0
#define CGUI_IMPL_SDL     0
#define CGUI_IMPL_GL      0
#define CGUI_IMPL_VK      0

/* Common Includes */
#include <string>
#include <cmath>

/* Common Defines */
#define CGUI_PI PI

/* Base Types */
typedef void                                     cgui_void;
typedef enum cgui_bool { CGUI_TRUE, CGUI_FALSE } cgui_bool;
typedef char                                     cgui_char;
typedef unsigned char                            cgui_byte;
typedef short                                    cgui_short;
typedef int                                      cgui_int;
typedef unsigned int                             cgui_uint;
typedef float                                    cgui_float;
typedef double                                   cgui_double;
typedef cgui_byte                               *cgui_data;
typedef std::basic_string<cgui_char>             cgui_string;

/* Common Types */
typedef enum cgui_api /* Graphics API */
{ 
    CGUI_API_DX9,
    CGUI_API_DX10,
    CGUI_API_DX11,
    CGUI_API_DX12, 
    CGUI_API_GL,
    CGUI_API_SDL,
    CGUI_API_VK,
    CGUI_API_NONE
} cgui_api;

typedef struct cgui_handle /* Base Handle */
{
    cgui_api api = CGUI_API_NONE;
} cgui_handle;

typedef struct cgui_color /* Color Type */
{
    cgui_byte red   = 0;
    cgui_byte green = 0;
    cgui_byte blue  = 0;
    cgui_byte alpha = 0;

    inline cgui_color(cgui_byte r, cgui_byte g, cgui_byte b, cgui_byte a = 255)
    {
        this->red   = r;
        this->green = g;
        this->blue  = b;
        this->alpha = a;
    }

    inline cgui_color(cgui_float r, cgui_float g, cgui_float b, cgui_float a = 1.0f)
    {
        this->red   = (cgui_byte)(r * 255.0f);
        this->green = (cgui_byte)(g * 255.0f);
        this->blue  = (cgui_byte)(b * 255.0f);
        this->alpha = (cgui_byte)(a * 255.0f);
    }
} cgui_color;

typedef struct cgui_vec2 /* Generic 2D Vector Type */
{
    cgui_float x = 0.0f;
    cgui_float y = 0.0f;

    inline cgui_vec2(cgui_float x, cgui_float y)
    {
        this->x = x;
        this->y = y;
    }

    inline cgui_vec2(cgui_int x, cgui_int y)
    {
        this->x = (cgui_float)x;
        this->y = (cgui_float)y;
    }
} cgui_vec2;

typedef struct cgui_vec3 /* Generic 3D Vector Type */
{
    cgui_float x = 0.0f;
    cgui_float y = 0.0f;
    cgui_float z = 0.0f;

    inline cgui_vec3(cgui_float x, cgui_float y, cgui_float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    inline cgui_vec3(cgui_int x, cgui_int y, cgui_int z)
    {
        this->x = (cgui_float)x;
        this->y = (cgui_float)y;
        this->z = (cgui_float)z;
    }
} cgui_vec3;

typedef struct cgui_vec4 /* Generic 4D Vector Type */
{
    cgui_float x;
    cgui_float y;
    cgui_float z;
    cgui_float w;

    inline cgui_vec4(cgui_float x, cgui_float y, cgui_float z, cgui_float w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    inline cgui_vec4(cgui_int x, cgui_int y, cgui_int z, cgui_int w)
    {
        this->x = (cgui_float)x;
        this->y = (cgui_float)y;
        this->z = (cgui_float)z;
        this->w = (cgui_float)w;
    }
} cgui_vec4;

typedef struct cgui_font /* Generic Font Type */
{
    cgui_data data;
} cgui_font;

/* DirectX 9 Implementation */
#if  CGUI_IMPL_DX9
#include <d3d9.h>

typedef struct cgui_dx9_handle : cgui_handle
{
    IDirect3DDevice9 *pD3DDevice;

    cgui_dx9_handle(IDirect3DDevice9 *pD3DDevice9)
    {
        this->api = CGUI_API_DX9;
        this->pD3DDevice = pD3DDevice9;
    }
} cgui_dx9_handle;

cgui_handle *CGUI_Init_DX9(IDirect3DDevice9 *pD3DDevice);
#endif

#if CGUI_IMPL_DX10
typedef struct cgui_dx10_handle : cgui_handle
{
    cgui_dx10_handle()
    {
        this->api = CGUI_API_DX10;
    }
} cgui_dx10_handle;
#endif

#if CGUI_IMPL_DX11
typedef struct cgui_dx11_handle : cgui_handle
{
    cgui_dx11_handle()
    {
        this->api = CGUI_API_DX11;
    }
} cgui_dx11_handle;
#endif

#if CGUI_IMPL_DX12
typedef struct cgui_dx12_handle : cgui_handle
{
    cgui_dx12_handle()
    {
        this->api = CGUI_API_DX12;
    }
} cgui_dx12_handle;
#endif

#if CGUI_IMPL_SDL
typedef struct cgui_sdl_handle : cgui_handle
{
    cgui_sdl_handle()
    {
        this->api = CGUI_API_SDL;
    }
} cgui_sdl_handle;
#endif

#if CGUI_IMPL_GL
typedef struct cgui_gl_handle : cgui_handle
{
    cgui_gl_handle()
    {
        this->api = CGUI_API_GL;
    }
} cgui_gl_handle;
#endif

#if CGUI_IMPL_VK
typedef struct cgui_vk_handle : cgui_handle
{
    cgui_vk_handle()
    {
        this->api = CGUI_API_VK;
    }
} cgui_vk_handle;
#endif

/* Common Implementation */
cgui_void CGUI_Shutdown(cgui_handle *handle);

/* CGUI */
namespace cgui
{
    cgui_void draw_line(cgui_handle *handle, cgui_vec2 point0, cgui_vec2 point1, cgui_color color, cgui_int thickness = 1);
    cgui_void draw_rect(cgui_handle *handle, cgui_vec2 min, cgui_vec2 max, cgui_color color, cgui_int thickness = 1);
    cgui_void draw_filled_rect(cgui_handle *handle, cgui_vec2 min, cgui_vec2 max, cgui_color color);
    cgui_void draw_circle(cgui_handle *handle, cgui_vec2 center, cgui_int radius, cgui_color color, cgui_int thickness = 1);
    cgui_void draw_filled_circle(cgui_handle *handle, cgui_vec2 center, cgui_int radius, cgui_color color);
    cgui_void draw_triangle(cgui_handle *handle, cgui_vec2 vertex0, cgui_vec2 vertex1, cgui_vec2 vertex2, cgui_color color, cgui_int thickness = 1);
    cgui_void draw_filled_triangle(cgui_handle *handle, cgui_vec2 vertex0, cgui_vec2 vertex1, cgui_vec2 vertex2, cgui_color color);
    cgui_void draw_polygon(cgui_handle *handle, cgui_vec2 *vertices, cgui_int vertex_count, cgui_color color, cgui_int thickness = 1);
    cgui_void draw_filled_polygon(cgui_handle *handle, cgui_vec2 *vertices, cgui_int vertex_count, cgui_color color);
    cgui_void draw_text(cgui_handle *handle, cgui_vec2 position, cgui_font font, cgui_int size, cgui_string text, cgui_color color);    
}

#endif