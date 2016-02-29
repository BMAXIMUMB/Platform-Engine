// color.cpp

#include "color.h"

color4 color4::operator * (float value)
{
	color4 c;
	c.r = r*value;
	c.g = g*value;
	c.b = b*value;
	c.a = a*value;
	return c;
}

color4 color4::operator * (color4 c)
{
	color4 color;
	color.r = r*c.r;
	color.g = g*c.g;
	color.b = b*c.b;
	color.a = a*c.a;
	return color;
}

color4 color4::operator += (color4 c)
{
	r += c.r;
	g += c.g;
	b += c.b;
	a += c.a;

	return *this;
}

color4 color4::operator -= (color4 c)
{
	r -= c.r;
	g -= c.g;
	b -= c.b;
	a -= c.a;

	return *this;
}

color4 color4::operator -= (float value)
{
	r -= value;
	g -= value;
	b -= value;
	a -= value;

	return *this;
}

color4 color4::operator = (int colorRGBA)
{
	*this =  Color(colorRGBA);
	return *this;
}

////////////////////////////////////////////////////////////////////

color4 Color(int colorRGBA)
{
	color4 color;

	BYTE byteR = (colorRGBA & 0xff000000) >> 24;
	BYTE byteG = (colorRGBA & 0x00ff0000) >> 16;
	BYTE byteB = (colorRGBA & 0x0000ff00) >> 8;
	BYTE byteA = (colorRGBA & 0x000000ff);

	color.r = float(byteR) / 255;
	color.g = float(byteG) / 255;
	color.b = float(byteB) / 255;
	color.a = float(byteA) / 255;

	return color;
}

color4 Color(BYTE r, BYTE g, BYTE b, BYTE a)
{
	color4 color;

	color.r = r / 255;
	color.g = g / 255;
	color.b = b / 255;
	color.a = a / 255;

	return color;
}