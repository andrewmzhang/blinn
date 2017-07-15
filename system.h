#include <string>
#include <vector>

#ifndef __system__
#define __system__
class system {

private:
	int time;
	int freeze;
	int n;	


public:

	system(const int time = 0, const int freeze = 0, const int n = 0); 

	int get_time() const;
	int get_freeze() const;
	int get_n() const;

	static void test();
	const char* to_string() const;


};

#endif
	


