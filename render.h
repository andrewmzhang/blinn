#ifndef __render_h__
#define __render_h__

#include "color.h"

class render {


private:
	int width;
	int height;
	color **frame;
	void clean();

public:

	render(const int h = 0, const int w = 0);

	void render_frame() const;
	
	int get_width() const;
	int get_height() const;

	void set_height(int h);
	void set_width(int w);

	static void test();
	const char* to_string() const;

};
#endif
