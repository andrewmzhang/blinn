/*
 * I have modified Dr. Matt Lazar's animate_rectangle_sv.cpp file
 * so that it works as a unit box renderer.
 */


#ifndef __render_h__
#define __render_h__

#include "color.cuh"


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

	
	std::string int_to_five_digit_string(int frame_number);
	void write_bmp_header_file(std::ofstream& output_file, int px, int pz);
	void write_bmp_file(int f_number, std::string output_file_name, unsigned char ***output_buffer, int px, int pz);

	void put_point(int x, int y);
public:
	unsigned char ***frame;

	render(const int h = 0, const int w = 0);

	void set_frame(int*, int);

	void render_frame() const;

	int get_width() const;
	int get_height() const;

	void set_color(color* color);
	void set_point(double x, double y);
	void set_point(double x, double y, color* color);
	void set_circle(double x, double y, double radius);

	void set_height(int h);
	void set_width(int w);

	static void test();
	const char* to_string();

	void print(int num = 0, std::string str = "default");

	~render();

};
#endif
