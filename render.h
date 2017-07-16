/*
 * I have modified Dr. Matt Lazar's animate_rectangle_sv.cpp file
 * so that it works as a unit box renderer. 
 */


#ifndef __render_h__
#define __render_h__

#include "color.h"


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>


class render {


private:
	int width;
	int height;

	int r;
	int g;
	int b;

	color** frame;

	std::string int_to_five_digit_string(int frame_number);
	int string_to_int(std::string s);
	void write_bmp_header_file(std::ofstream& output_file, int px, int pz);
	void write_bmp_file(int f_number, std::string output_file_name, unsigned char ***output_buffer, int px, int pz);


public:

	render(const int h = 0, const int w = 0);

	void render_frame() const;
	
	int get_width() const;
	int get_height() const;

	void set_color(color* color);
	void set_point(float x, float y);

	void set_height(int h);
	void set_width(int w);

	static void test();
	const char* to_string();

	~render();

};
#endif
