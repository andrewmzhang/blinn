#include "color.h"
#include <cmath>
#include <iostream>
#include <string>
#include "render.h"
#include "dbg.h"

using namespace std;


render::render(const int h, const int w) {

	this->height = h;
	this->width = w;

	this->frame = new color *[h];

	for (int i = 0; i < h; i++) {
		this->frame[i] = new color[w];
	}

}


void render::render_frame() const {

	cout << "No render function available" << endl;

	return;
}


int render::get_width() const {

	return this->width;

}

int render::get_height() const {

	return this->height;

}

void render::set_color(color *color) {
	this->r = color->r();
	this->g = color->g();
	this->b = color->b();
}

void render::set_point(float x, float y) {

	if (x > 1 || x < 0 || y > 1 || y < 0) {
		log_info("Error: set_point invalid!");
	}

	int point_x = (int) round(x * height);
	int point_y = (int) round(y * width);

	this->frame[point_x][point_y].set_rgb(this->r, this->g, this->b);

}

void render::set_height(int h) {

	this->height = h;

}

void render::set_width(int w) {

	this->width = w;

}

const char* to_string() {


	return "Hard coded string";

}

render::~render() {
	
	int i = 0;
	for (i = 0; i < height; i++) {
		delete[] frame[i];
		frame[i] = NULL;
	}
	delete[] frame;
	frame = NULL;

}

void render::test() {

	cout << "Test function" << endl;

}

string render::int_to_five_digit_string(int frame_number) {

	ostringstream strm;

	strm << setfill('0') << setw(5) << frame_number;

	return strm.str();

}

void render::write_bmp_header_file(ofstream& output_file, int px, int pz) {
	unsigned short int bfType;
	bfType = 0x4D42;
	output_file.write ((char*)&bfType, sizeof (short int));   

	unsigned int bfSize;
	int rem;
	rem=3*px%4;
	int padding;
	if(rem==0)
	{
		padding=0;
	}
	else
	{
		padding=4-rem;
	}

	bfSize = 14 + 40 + (3 * px+padding) * pz;   
	output_file.write ((char*)&bfSize, sizeof (int));   

	unsigned short int bfReserved1;
	bfReserved1 = 0;
	output_file.write ((char*)&bfReserved1, sizeof (short int));   

	unsigned short int bfReserved2;
	bfReserved2 = 0;
	output_file .write ((char*)&bfReserved2, sizeof (short int));   

	unsigned int bfOffsetBits;
	bfOffsetBits = 14 + 40;
	output_file.write ((char*)&bfOffsetBits, sizeof (int));   

	unsigned int biSize;
	biSize=40;
	output_file.write ((char*)&biSize, sizeof (int));   

	int biWidth;
	biWidth=px;
	output_file.write ((char*)&biWidth, sizeof (int));   

	int biHeight;
	biHeight=pz;
	output_file.write ((char*)&biHeight, sizeof (int));   

	unsigned short int biPlanes;
	biPlanes=1;
	output_file.write ((char*)&biPlanes, sizeof (short int));   

	unsigned short int biBitCount;
	biBitCount=24;
	output_file.write ((char*)&biBitCount, sizeof (short int));   

	unsigned int biCompression;

	unsigned int bi_rgb = 0;
	biCompression=bi_rgb;
	output_file.write ((char*)&biCompression, sizeof (int));   

	unsigned int biSizeImage;
	biSizeImage=0;
	output_file.write ((char*)&biSizeImage, sizeof (int));   

	unsigned int biXPelsPerMeter;
	biXPelsPerMeter=0;
	output_file.write ((char*)&biXPelsPerMeter, sizeof (int));   

	unsigned int biYPelsPerMeter;
	biYPelsPerMeter=0;
	output_file.write ((char*)&biYPelsPerMeter, sizeof (int));   

	unsigned int biClrUsed;
	biClrUsed = 0;
	output_file.write ((char*)&biClrUsed, sizeof (int));   

	unsigned int biClrImportant;
	biClrImportant = 0;
	output_file.write ((char*)&biClrImportant, sizeof (int));   
}

void render::write_bmp_file(int f_number, string output_file_name, unsigned char * * * output_buffer, int px, int pz)
{
	ofstream ostrm_1;
	string o_file_name = int_to_five_digit_string(f_number)+output_file_name;
	ostrm_1.open(o_file_name.c_str(), ios::out | ios::binary);
	if(ostrm_1.fail())
	{
		cout << "Error.  Can't open output file " << o_file_name << "." << endl;
		return;
	}
	cout << "Opening output file " << o_file_name <<"." << endl;

	int rem;
	rem=3*px%4;
	int padding;
	if(rem==0)
	{
		padding=0;
	}
	else
	{
		padding=4-rem;
	}
	write_bmp_header_file(ostrm_1, px, pz);

	unsigned char p_buffer[4];
	p_buffer[0]=0;
	p_buffer[1]=0;
	p_buffer[2]=0;
	p_buffer[3]=0;

	unsigned char * line_buffer = new unsigned char[px*3];

	int i;
	int j;
	for(i=pz-1;i>=0;i--)
	{
		for(j=0;j<px;j++)
		{
			line_buffer[3*j+0]=output_buffer[i][j][2];
			line_buffer[3*j+1]=output_buffer[i][j][1];
			line_buffer[3*j+2]=output_buffer[i][j][0];         
		}
		ostrm_1.write ((char*)line_buffer, px*3*sizeof (unsigned char));      
		ostrm_1.write ((char*)p_buffer, padding*sizeof (unsigned char));      
	}
	delete[] line_buffer;
	line_buffer = NULL;
	ostrm_1.close();   
}
