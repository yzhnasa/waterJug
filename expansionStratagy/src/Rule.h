#ifndef __RULE_H__
#define __RULE_H__
#include <vector>
#include <cmath>
#include <cstdlib>
#include "State.h"
using namespace std;

#define INITIAL_STATE   0
#define FULL_JUG_A      1
#define FULL_JUG_B      2
#define EMPTY_JUG_A     3
#define EMPTY_JUG_B     4
#define POUR_A_TO_B     5
#define POUR_B_TO_A     6

class Rule{
private:
	int capacityA;
	int capacityB;
	State *initState;
	State *goalState;
	bool isAllowFullJugA(State *state);
	bool isAllowFullJugB(State *state);
	bool isAllowEmptyJugA(State *state);
	bool isAllowEmptyJugB(State *state);
	bool isAllowPourA2B(State *state);
	bool isAllowPourB2A(State *state);
public:
	vector<int> allowedOperation(State *state);
	void setCapacityA(int capacityA);
	int getCapacityA();
	void setCapacityB(int capacityB);
	int getCapacityB();
	void setInitState(State *initState);
	void setGoalState(State *goalState);
	bool isGoalState(State *state);
	bool isSameWithExpandedState(vector<State *> &expandedState, State *state);
	int calculateDifferenceWithGoal(State *state);
};
#endif
