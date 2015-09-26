#ifndef __STATE_EXPANSION_H__
#define __STATE_EXPANSION_H__
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>
#include "State.h"
#include "CompareState.h"
#include "Rule.h"
using namespace std;

class StateExpansion{
private:
	priority_queue<State, vector<State *>, CompareState> states;
	vector<State *> expandedStates;
	void splitString(string &line, vector<string> &token);
	State *fullJug(int operation, State *state, Rule &rule);
	State *emptyJug(int operation, State *state, Rule &rule);
	State *pourJug(int operation, State *state, Rule &rule);
public:
	void parcingInputFile(string file, State *&initState, State *&goalState, int &capacityA, int &capacityB);
	State *solveWaterJugPuzzle(fstream &outputStream, int operation, State *state, Rule &rule);
	vector<State *> stateExpension(string inputFilename, string outputFilename);
};
#endif
