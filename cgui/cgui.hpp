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
#include <initializer_list>

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
#define CGUI_STRLEN(str) strlen(str)

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

/* Classes */
template <typename cgui_type, cgui_size _length>
class cgui_array
{
	/*
	 * Generic array with
	 * static length
	 */
private:
	cgui_type buf[_length];
public:
	inline cgui_array()
	{

	}

	inline cgui_array(std::initializer_list<cgui_type> list)
	{
		cgui_size index = 0;
		for (cgui_type *it = (cgui_type *)list.begin(); it != (cgui_type *)list.end() && index < _length; ++index, it = &it[1])
			this->buf[index] = *it;
	}

	inline ~cgui_array()
	{

	}
public:
	inline cgui_type &operator[](cgui_size index)
	{
		return this->buf[index];
	}
public:
	inline cgui_size length()
	{
		return _length;
	}

	inline cgui_size size()
	{
		return this->length() * sizeof(cgui_type);
	}

	inline cgui_type *data()
	{
		return this->buf;
	}
};

template <typename cgui_type>
class cgui_vector
{
	/*
	 * Generic vector with
	 * dynamic length
	 */
private:
	cgui_size len = 0;
	cgui_type *buf = (cgui_type *)nullptr;
public:
	inline cgui_vector()
	{

	}

	inline cgui_vector(std::initializer_list<cgui_type>& list)
	{
		this->len = list.size();
		this->buf = new cgui_type[this->len];
		cgui_size index = 0;
		for (cgui_type *it = (cgui_type *)list.begin(); it != (cgui_type *)list.end(); ++index, it = &it[1])
			this->buf[index] = *it;
	}

	inline ~cgui_vector()
	{
		if (this->buf)
			delete[] this->buf;
	}
public:
	inline cgui_type &operator[](cgui_size index)
	{
		if (index > this->length())
			this->resize(index + 1);
		return this->buf[index];
	}

	inline cgui_void operator+=(cgui_type value)
	{
		this->push(value);
	}

	inline cgui_void operator+=(cgui_vector<cgui_type>& vec)
	{
		cgui_size old_length = this->length();
		this->resize((old_length + 1) + (vec.length() + 1));
		
		for (cgui_size i = 0; i < vec.length(); ++i)
		{
			(*this)[old_length + i] = vec[i];
		}
	}
public:
	inline cgui_size length()
	{
		return this->len;
	}

	inline cgui_size size()
	{
		return this->length() * sizeof(cgui_type);
	}

	inline cgui_type *data()
	{
		return this->buf;
	}

	inline cgui_type *begin()
	{
		return &this->buf[0];
	}

	inline cgui_type *end()
	{
		return &this->buf[this->len - 1];
	}

	inline cgui_void resize(cgui_size size)
	{
		cgui_type *holder = this->buf;
		this->buf = new cgui_type[size];
		if (holder)
		{
			for (cgui_size i = 0; i < this->len; ++i)
				this->buf[i] = holder[i];
			delete[] holder;
		}

		this->len = size;
	}

	inline cgui_void push(cgui_type value)
	{
		this->resize(this->len + 1);
		this->buf[this->len] = value;
		++this->len;
	}

	inline cgui_type pop()
	{
		--this->len;
		cgui_type value = this->buf[this->len];
		this->resize(this->len);
		return value;
	}
};

class cgui_string : public cgui_vector<cgui_char>
{
	/*
	 * Generic string
	 */

public:
	cgui_string(const cgui_char *string)
	{
		cgui_size str_len = CGUI_STRLEN(string);
		for (cgui_size i = 0; i < str_len; ++i)
			this->push(string[i]);
	}

	cgui_string(cgui_char *string)
	{
		cgui_size str_len = CGUI_STRLEN(string);
		for (cgui_size i = 0; i < str_len; ++i)
			this->push(string[i]);
	}
public:
	cgui_char *c_str()
	{
		return this->data();
	}
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

	inline cgui_color(cgui_uint r, cgui_uint g, cgui_uint b, cgui_uint a = 255)
	{
		this->red   = (cgui_byte)r;
		this->green = (cgui_byte)g;
		this->blue  = (cgui_byte)b;
		this->alpha = (cgui_byte)a;
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

	inline ~cgui_color()
	{

	}
public:
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
	 * Portable handle for any graphics
	 * API. It constains draw functions
	 * and some of them must be defined
	 * manually by the implementation,
	 * as they're API specific. These
	 * functions are marked after
	 * 'Mandatory Override' and
	 * before 'Optional Override'.
	 */
public:
	/* Mandatory Override */
	virtual inline cgui_void DrawLine(cgui_array<cgui_float, 2> point0, cgui_array<cgui_float, 2> point1, cgui_color color, cgui_float thickness) {  }
	virtual inline cgui_void DrawFilledTriangle(cgui_array<cgui_float, 2> vertex0, cgui_array<cgui_float, 2> vertex1, cgui_array<cgui_float, 2> vertex2, cgui_color color) {  }
	virtual inline cgui_void DrawFont(cgui_string text, cgui_font font, cgui_array<cgui_float, 2> position, cgui_color color, cgui_size size) {  }

	/* Optional Override */
	virtual inline cgui_void DrawRectangle(cgui_array<cgui_float, 2> min, cgui_array<cgui_float, 2> max, cgui_color color, cgui_float thickness = 1.0f)
	{
		cgui_array<cgui_float, 2> p0, p1, p2, p3;
		p0 = min;
		p1 = p0;
		p1[1] = max[1];
		p2 = max;
		p3 = p2;
		p3[1] = p0[1];

		this->DrawQuad(p0, p1, p2, p3, color, thickness);
	}

	virtual inline cgui_void DrawFilledRectangle(cgui_array<cgui_float, 2> min, cgui_array<cgui_float, 2> max, cgui_color color)
	{
		cgui_array<cgui_float, 2> p0, p1, p2, p3;
		p0 = min;
		p1 = p0;
		p1[1] = max[1];
		p2 = max;
		p3 = p2;
		p3[1] = p0[1];

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
			cur_point[0] = center[0] + dist_sin;
			cur_point[1] = center[1] + dist_cos;
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
			cur_point[0] = center[0] + dist_sin;
			cur_point[1] = center[1] + dist_cos;
			if (cur_angle != 0.0f)
				this->DrawFilledTriangle(center, old_point, cur_point, color);
			old_point = cur_point;
		}
	}

	virtual inline cgui_void DrawPolygon(cgui_vector<cgui_array<cgui_float, 2>> vertices, cgui_color color, cgui_float thickness = 1.0f)
	{
		for (cgui_size i = 0; i < vertices.length() && i > 0; ++i)
		{
			cgui_array<cgui_float, 2> &vertex0 = vertices[i - 1];
			cgui_array<cgui_float, 2> &vertex1 = vertices[i];

			this->DrawLine(vertex0, vertex1, color, thickness);
		}
	}

	virtual inline cgui_void DrawFilledPolygon(cgui_vector<cgui_array<cgui_float, 2>> vertices, cgui_color color)
	{
		for (cgui_size i = 0; i < vertices.length() && i >= 2; ++i)
		{
			cgui_array<cgui_float, 2> &vertex0 = vertices[i - 2];
			cgui_array<cgui_float, 2> &vertex1 = vertices[i - 1];
			cgui_array<cgui_float, 2> &vertex2 = vertices[i];

			this->DrawFilledTriangle(vertex0, vertex1, vertex2, color);
		}
	}
};

#endif
