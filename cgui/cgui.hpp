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

/* Defines */
#define CGUI_FALSE false
#define CGUI_TRUE  true
#define CGUI_PI 3.141592654f
#define CGUI_CIRCLE_VERTICES 10

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
template <cgui_size length>
class cgui_array
{
	/*
	 * Generic array with
	 * static length
	 */
private:
	cgui_float data[length];
public:
	cgui_array()
	{

	}

	~cgui_array()
	{

	}
public:
	inline cgui_float operator[](cgui_size pos)
	{
		cgui_float item = 0.0f;
		if (pos < (sizeof(this->data) / sizeof(this->data[0])))
			item = this->data[pos];
		return item;
	}

	inline cgui_bool operator==(cgui_array<length>& arr)
	{
		cgui_bool ret = CGUI_TRUE;

		for (cgui_size i = 0; i < length; ++i)
		{
			ret = ((*this)[i] == arr[i] ? ret : CGUI_FALSE);
			if (ret == CGUI_FALSE) break;
		}

		return ret;
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

	inline ~cgui_vector()
	{
		if (this->buf)
			delete[] this->buf;
	}
public:
	cgui_type operator[](cgui_size pos)
	{
		cgui_type ret = (cgui_type)0;
		if (pos < this->length())
			ret = this->data()[pos];
		return ret;
	}

	cgui_bool operator==(cgui_vector<cgui_type>& vec)
	{
		cgui_bool ret = CGUI_FALSE;
		if (vec.length() != this->length()) return ret;

		ret = CGUI_TRUE;

		for (cgui_size i = 0; i < length; ++i)
		{
			ret = ((*this)[i] == vec[i] ? ret : CGUI_FALSE);
			if (ret == CGUI_FALSE) break;
		}

		return ret;
	}

public:
	inline cgui_size length()
	{
		return this->len;
	}

	inline cgui_type *data()
	{
		return this->buf;
	}

	inline cgui_void push(cgui_type value)
	{
		cgui_type *holder = this->data();
		this->buf = new cgui_type[this->length() + 1];
		if (holder)
		{
			for (cgui_size i = 0; i < this->length(); ++i)
				this->buf[i] = holder[i];
			delete[] holder;
		}

		++this->len;
	}

	inline cgui_type pop()
	{
		cgui_type ret = (cgui_type)0;
		if (this->length() == 0) return ret;

		cgui_type *holder = this->data();
		this->buf = new cgui_type[this->length() - 1];
		if (holder)
		{
			for (cgui_size i = 0; i < this->length() - 1; ++i)
				this->buf[i] = holder[i];
			delete[] holder;
		}
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

class cgui_font
{
private:
	cgui_byte *data = (cgui_byte *)nullptr;
public:
	inline cgui_font()
	{

	}

	inline cgui_font(cgui_byte *buffer, cgui_size size)
	{
		this->Create(buffer, size);
	}

	inline ~cgui_font()
	{
		if(this->data)
			this->Free();
	}
public:
	inline cgui_void Create(cgui_byte *buffer, cgui_size size)
	{
		if (this->data)
			this->Free();
		this->data = new cgui_byte[size];
		for (cgui_size i = 0; i < size; ++i)
			this->data[i] = buffer[i];
	}

	inline cgui_byte *GetData()
	{
		return this->data;
	}

	inline cgui_void Free()
	{
		delete[] this->data;
	}
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
	virtual inline cgui_void DrawLine(cgui_array<2> point0, cgui_array<2> point1, cgui_color color, cgui_float thickness) {  }
	virtual inline cgui_void DrawFilledRectangle(cgui_array<2> min, cgui_array<2> max, cgui_color color) {  }
	virtual inline cgui_void DrawFilledTriangle(cgui_array<2> vertex0, cgui_array<2> vertex1, cgui_array<2> vertex2, cgui_color color) {  }
	virtual inline cgui_void DrawText(cgui_string text, cgui_font font, cgui_array<2> position, cgui_color color, cgui_size size) {  }

	/* Optional Override */
	virtual inline cgui_void DrawRectangle(cgui_array<2> min, cgui_array<2> max, cgui_color color, cgui_float thickness = 1.0f);
	virtual inline cgui_void DrawQuad(cgui_array<2> point0, cgui_array<2> point1, cgui_array<2> point2, cgui_array<2> point3, cgui_color color, cgui_float thickness = 1.0f);
	virtual inline cgui_void DrawFilledQuad(cgui_array<2> point0, cgui_array<2> point1, cgui_array<2> point2, cgui_array<2> point3, cgui_color color);
	virtual inline cgui_void DrawTriangle(cgui_array<2> vertex0, cgui_array<2> vertex1, cgui_array<2> vertex2, cgui_color color, cgui_float thickness = 1.0f);
	virtual inline cgui_void DrawCircle(cgui_array<2> center, cgui_float radius, cgui_color color, cgui_float thickness = 1.0f);
	virtual inline cgui_void DrawFilledCircle(cgui_array<2> center, cgui_float radius, cgui_color color);
	virtual inline cgui_void DrawPolygon(cgui_vector<cgui_array<2>> vertices, cgui_color color, cgui_float thickness = 1.0f);
	virtual inline cgui_void DrawFilledPolygon(cgui_vector<cgui_array<2>> vertices, cgui_color color);
};

#endif
