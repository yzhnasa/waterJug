#include "CompareState.h"

bool CompareState::operator()(State *s1, State *s2){
	if (s1->getDistance() < s2->getDistance())
		return true;
	return false;
}