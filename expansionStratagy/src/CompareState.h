#ifndef __COMPARE_STATE_H__
#define __COMPARE_STATE_H__
#include "State.h"
using namespace std;

class CompareState{
public:
	bool operator()(State *s1, State *s2);
};
#endif