#include <iostream>
#include "system.h"
#include "dbg.h"
#include <sstream>

using namespace std;

system::system(int time, int freeze, int n) :time(time), freeze(freeze), n(n) {


}

int system::get_time(void) const {
	return this->time;
}
int system::get_freeze(void) const {
	return this->freeze;
}

int system::get_n(void) const {
	return this->n;
}

const char* system::to_string(void) const {
	stringstream stringStream;
	stringStream << "time: " << this->time << " G: " << this->freeze << " B: " << this->n << "\0";
	string copyOfStr = stringStream.str();

	return copyOfStr.c_str();
}

void system::test(void) {


}
