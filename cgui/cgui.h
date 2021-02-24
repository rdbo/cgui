/*
 * ====================================
 * =          CGUI - by rdbo          =
 * =      Universal Graphics API      =
 * ====================================
 */

#ifndef CGUI_HPP
#define CGUI_HPP

/* Implementation Settings */
#define CGUI_IMPL_DX9  0
#define CGUI_IMPL_DX10 0
#define CGUI_IMPL_DX11 0
#define CGUI_IMPL_DX12 0
#define CGUI_IMPL_GL   0
#define CGUI_IMPL_SDL  0
#define CGUI_IMPL_VK   0

#define CGUI_GL_USE_GLES 0
#define CGUI_GL_USE_GLFW 0

/* Common Includes */

#include <math.h>

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

/* Common Types */
typedef enum cgui_api /* Graphics API */
{ 
    CGUI_API_DX9,
    CGUI_API_DX10,
    CGUI_API_DX11,
    CGUI_API_DX12, 
    CGUI_API_GL,
    CGUI_API_SDL,
    CGUI_API_VK
} cgui_api;

typedef struct cgui_handle /* Base Handle */
{
    cgui_api api;
} cgui_handle;

typedef struct cgui_color /* Color Type */
{
    cgui_byte red;
    cgui_byte green;
    cgui_byte blue;
    cgui_byte alpha;
} cgui_color;

typedef struct cgui_vec2 /* Generic 2D Vector Type */
{
    cgui_float x;
    cgui_float y;
} cgui_vec2;

typedef struct cgui_vec3 /* Generic 3D Vector Type */
{
    cgui_float x;
    cgui_float y;
    cgui_float z;
} cgui_vec3;

typedef struct cgui_vec4 /* Generic 4D Vector Type */
{
    cgui_float x;
    cgui_float y;
    cgui_float z;
    cgui_float w;
} cgui_vec4;

typedef struct cgui_font
{
    cgui_data data;
} cgui_font;

/* DirectX 9 Implementation */
#if  CGUI_IMPL_DX9
#include <d3d9.h>

typedef struct cgui_dx9_handle
{
    struct cgui_handle handle;
} cgui_dx9_handle;
#endif

/* DirectX 10 Implementation */
#if  CGUI_IMPL_DX10
#include <d3d10.h>
#include <dxgi.h>

typedef struct cgui_dx10_handle
{
    struct cgui_handle handle;
} cgui_dx10_handle;
#endif

/* DirectX 11 Implementation */
#if  CGUI_IMPL_DX11
#include <d3d11.h>
#include <dxgi.h>

typedef struct cgui_dx11_handle
{
    struct cgui_handle handle;
} cgui_dx11_handle;
#endif

/* DirectX 12 Implementation */
#if  CGUI_IMPL_DX12
#include <d3d12.h>
#include <dxgi.h>

typedef struct cgui_dx12_handle
{
    struct cgui_handle handle;
} cgui_dx12_handle;
#endif

/* OpenGL Implementation */
#if  CGUI_IMPL_GL
#include <GL.h>

typedef struct cgui_gl_handle
{
    struct cgui_handle handle;
} cgui_gl_handle;
#endif

/* SDL Implementation */
#if  CGUI_IMPL_SDL
#include <SDL.h>

typedef struct cgui_sdl_handle
{
    struct cgui_handle handle;
} cgui_sdl_handle;
#endif

/* Vulkan Implementation */
#if  CGUI_IMPL_VK
typedef struct cgui_vk_handle
{
    struct cgui_handle handle;
} cgui_vk_handle;
#endif

/* Common Functions */
cgui_void cgui_draw_rect(   cgui_handle *handle,
                            cgui_vec2 min,
                            cgui_vec2 max,
                            cgui_int thickness,
                            cgui_color color    );
/*===========================================================================*/
cgui_void cgui_draw_filled_rect(    cgui_handle *handle,
                                    cgui_vec2 min,
                                    cgui_vec2 max,
                                    cgui_color color    );
/*===========================================================================*/
cgui_void cgui_draw_circle(     cgui_handle *handle,
                                cgui_vec2 center,
                                cgui_int radius,
                                cgui_int thickness,
                                cgui_color color     );
/*===========================================================================*/
cgui_void cgui_draw_filled_circle(      cgui_handle *handle,
                                        cgui_vec2 center,
                                        cgui_int radius, 
                                        cgui_color color      );
/*===========================================================================*/
cgui_void cgui_draw_triangle(       cgui_handle *handle,
                                    cgui_vec2 vertex0,
                                    cgui_vec2 vertex1,
                                    cgui_vec2 vertex2     );
/*===========================================================================*/
cgui_void cgui_draw_polygon(    cgui_handle *handle,
                                cgui_vec2 *vertices,
                                cgui_int vertex_count,
                                cgui_int thickness,
                                cgui_color color    );
/*===========================================================================*/
cgui_void cgui_draw_filled_polygon(     cgui_handle *handle,
                                        cgui_vec2 *vertices,
                                        cgui_int vertex_count,
                                        cgui_color color     );
/*===========================================================================*/
cgui_void cgui_draw_text(   cgui_handle *handle,
                            cgui_vec2 pos,
                            cgui_font *font,
                            cgui_int size,
                            cgui_color color    );

#endif
