/*
 * ====================================
 * =          CGUI - by rdbo          =
 * =      Universal Graphics API      =
 * ====================================
 */

#ifndef CGUI_HPP
#define CGUI_HPP

/* Includes */
#include <cmath>
#include <string>
#include <array>
#include <vector>

/* Defines */
#define CGUI_FALSE false
#define CGUI_TRUE  true
#define CGUI_PI 3.141592654f
#define CGUI_CIRCLE_VERTICES 10

/* Helpers */
#define CGUI_SIN(ang) sin(ang)
#define CGUI_SIN2(ang) CGUI_SIN(ang / 180.0f * CGUI_PI)
#define CGUI_COS(ang) cos(ang)
#define CGUI_COS2(ang) CGUI_COS(ang / 180.0f * CGUI_PI)

/* Types */
typedef void                                     cgui_void;
typedef bool                                     cgui_bool;
typedef char                                     cgui_char;
typedef unsigned char                            cgui_byte;
typedef short                                    cgui_short;
typedef int                                      cgui_int;
typedef unsigned int                             cgui_uint;
typedef float                                    cgui_float;
typedef double                                   cgui_double;
typedef cgui_uint                                cgui_size;
typedef std::basic_string<cgui_char>             cgui_string;

/* Classes */
template <typename cgui_type, cgui_size _length>
class cgui_array : public std::array<cgui_type, _length>
{
	/*
	 * Generic array with
	 * static length
	 */
};

template <typename cgui_type>
class cgui_vector : public std::vector<cgui_type>
{
	/*
	 * Generic vector with
	 * dynamic length
	 */
};

class cgui_color
{
	/*
	 * Generic color class
	 */

private:
	cgui_byte red   = 0;
	cgui_byte green = 0;
	cgui_byte blue  = 0;
	cgui_byte alpha = 0;
public:
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

	inline cgui_color(cgui_uint color)
	{
		this->red   = (cgui_byte)(color & (0xFF >> 0));
		this->green = (cgui_byte)(color & (0xFF >> 8));
		this->blue  = (cgui_byte)(color & (0xFF >> 16));
		this->alpha = (cgui_byte)(color & (0xFF >> 24));
	}

	inline cgui_byte Red()
	{
		return this->red;
	}

	inline cgui_byte Green()
	{
		return this->green;
	}

	inline cgui_byte Blue()
	{
		return this->blue;
	}

	inline cgui_byte Alpha()
	{
		return this->alpha;
	}

	inline cgui_uint Hex()
	{
		cgui_uint hex = 0;
		hex |= (this->red   >>  0);
		hex |= (this->green >>  8);
		hex |= (this->blue  >> 16);
		hex |= (this->blue  >> 24);
		return hex;
	}
};

class cgui_font : public cgui_vector<cgui_byte>
{
	/*
	 * Generic font
	 */
};

class cgui_handle
{
	/*
	 * This class is a portable
	 * handle for any graphics
	 * API. It constains draw
	 * functions and some of them
	 * must be defined manually
	 * by the implementation. These
	 * functions are marked after
	 * 'Mandatory Override' and
	 * before 'Optional Override'.
	 */
public:
	/* Mandatory Override */
	virtual inline cgui_void DrawLine(cgui_array<cgui_float, 2> point0, cgui_array<cgui_float, 2> point1, cgui_color color, cgui_float thickness) {  }
	virtual inline cgui_void DrawFilledTriangle(cgui_array<cgui_float, 2> vertex0, cgui_array<cgui_float, 2> vertex1, cgui_array<cgui_float, 2> vertex2, cgui_color color) {  }
	virtual inline cgui_void DrawText(cgui_string text, cgui_font font, cgui_array<cgui_float, 2> position, cgui_color color, cgui_size size) {  }

	/* Optional Override */
	virtual inline cgui_void DrawRectangle(cgui_array<cgui_float, 2> min, cgui_array<cgui_float, 2> max, cgui_color color, cgui_float thickness = 1.0f)
	{
		cgui_array<cgui_float, 2> p0, p1, p2, p3;
		p0 = min;
		p1 = p0;
		p1[1] = max[1];
		p2 = p1;
		p2[0] = max[0];
		p3 = max;

		this->DrawQuad(p0, p1, p2, p3, color, thickness);
	}

	virtual inline cgui_void DrawFilledRectangle(cgui_array<cgui_float, 2> min, cgui_array<cgui_float, 2> max, cgui_color color)
	{
		cgui_array<cgui_float, 2> p0, p1, p2, p3;
		p0 = min;
		p1 = p0;
		p1[1] = max[1];
		p2 = p1;
		p2[0] = max[0];
		p3 = max;

		this->DrawFilledQuad(p0, p1, p2, p3, color);
	}

	virtual inline cgui_void DrawQuad(cgui_array<cgui_float, 2> point0, cgui_array<cgui_float, 2> point1, cgui_array<cgui_float, 2> point2, cgui_array<cgui_float, 2> point3, cgui_color color, cgui_float thickness = 1.0f)
	{
		this->DrawLine(point0, point1, color, thickness);
		this->DrawLine(point1, point2, color, thickness);
		this->DrawLine(point2, point3, color, thickness);
		this->DrawLine(point3, point0, color, thickness);
	}

	virtual inline cgui_void DrawFilledQuad(cgui_array<cgui_float, 2> point0, cgui_array<cgui_float, 2> point1, cgui_array<cgui_float, 2> point2, cgui_array<cgui_float, 2> point3, cgui_color color)
	{
		this->DrawFilledTriangle(point0, point1, point2, color);
		this->DrawFilledTriangle(point1, point2, point3, color);
		this->DrawFilledTriangle(point0, point1, point3, color);
	}

	virtual inline cgui_void DrawTriangle(cgui_array<cgui_float, 2> vertex0, cgui_array<cgui_float, 2> vertex1, cgui_array<cgui_float, 2> vertex2, cgui_color color, cgui_float thickness = 1.0f)
	{
		this->DrawLine(vertex0, vertex1, color, thickness);
		this->DrawLine(vertex1, vertex2, color, thickness);
		this->DrawLine(vertex2, vertex0, color, thickness);
	}

	virtual inline cgui_void DrawCircle(cgui_array<cgui_float, 2> center, cgui_float radius, cgui_color color, cgui_float thickness = 1.0f)
	{
		cgui_int vertices = (cgui_int)(CGUI_CIRCLE_VERTICES * radius);
		if (!vertices) return;
		cgui_float angle = (360.0f / vertices);
		cgui_array<cgui_float, 2> old_point;
		for (cgui_float cur_angle = 0.0f; cur_angle < 360.0f; cur_angle += angle)
		{
			cgui_float dist_sin = CGUI_SIN2(cur_angle) * radius;
			cgui_float dist_cos = CGUI_COS2(cur_angle) * radius;
			cgui_array<cgui_float, 2> cur_point;
			cur_point[0] = old_point[0] + dist_sin;
			cur_point[1] = old_point[1] + dist_cos;
			if (cur_angle != 0.0f)
				this->DrawLine(old_point, cur_point, color, thickness);
			old_point = cur_point;
		}
	}

	virtual inline cgui_void DrawFilledCircle(cgui_array<cgui_float, 2> center, cgui_float radius, cgui_color color)
	{
		cgui_int vertices = (cgui_int)(CGUI_CIRCLE_VERTICES * radius);
		if (!vertices) return;
		cgui_float angle = (360.0f / vertices);
		cgui_array<cgui_float, 2> old_point = {  };
		for (cgui_float cur_angle = 0.0f; cur_angle < 360.0f; cur_angle += angle)
		{
			cgui_float dist_sin = CGUI_SIN2(cur_angle) * radius;
			cgui_float dist_cos = CGUI_COS2(cur_angle) * radius;
			cgui_array<cgui_float, 2> cur_point = {  };
			cur_point[0] = old_point[0] + dist_sin;
			cur_point[1] = old_point[1] + dist_cos;
			if (cur_angle != 0.0f)
				this->DrawFilledTriangle(center, old_point, cur_point, color);
			old_point = cur_point;
		}
	}

	virtual inline cgui_void DrawPolygon(cgui_vector<cgui_array<cgui_float, 2>> vertices, cgui_color color, cgui_float thickness = 1.0f)
	{
		for (cgui_size i = 0; i < vertices.size() && i > 0; ++i)
		{
			cgui_array<cgui_float, 2> &vertex0 = vertices[i - 1];
			cgui_array<cgui_float, 2> &vertex1 = vertices[i];

			this->DrawLine(vertex0, vertex1, color, thickness);
		}
	}

	virtual inline cgui_void DrawFilledPolygon(cgui_vector<cgui_array<cgui_float, 2>> vertices, cgui_color color)
	{
		for (cgui_size i = 0; i < vertices.size() && i >= 2; ++i)
		{
			cgui_array<cgui_float, 2> &vertex0 = vertices[i - 2];
			cgui_array<cgui_float, 2> &vertex1 = vertices[i - 1];
			cgui_array<cgui_float, 2> &vertex2 = vertices[i];

			this->DrawFilledTriangle(vertex0, vertex1, vertex2, color);
		}
	}
};

#endif
