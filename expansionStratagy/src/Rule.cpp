#include "Rule.h"

bool Rule::isAllowFullJugA(State *state){
	if (state->getJugA() < capacityA)
		return true;
	return false;
}

bool Rule::isAllowFullJugB(State *state){
	if (state->getJugB() < capacityB)
		return true;
	return false;
}

bool Rule::isAllowEmptyJugA(State *state){
	if (state->getJugA() > 0)
		return true;
	return false;
}

bool Rule::isAllowEmptyJugB(State *state){
	if (state->getJugB() > 0)
		return true;
	return false;
}

bool Rule::isAllowPourA2B(State *state){
	if (state->getJugA() > 0 && state->getJugB() < capacityB)
		return true;
	return false;
}

bool Rule::isAllowPourB2A(State *state){
	if (state->getJugB() > 0 && state->getJugA() < capacityA)
		return true;
	return false;
}

bool Rule::isSameWithExpandedState(vector<State *> &expandedState, State *state){
	for (int i = 0; i < expandedState.size(); i++){
		if (expandedState.at(i)->getJugA() == state->getJugA()
			&& expandedState.at(i)->getJugB() == state->getJugB())
			return true;
	}
	return false;
}

vector<int> Rule::allowedOperation(State *state){
	vector<int> operations;
	if (isAllowFullJugA(state))
		operations.push_back(FULL_JUG_A);
	if (isAllowFullJugB(state))
		operations.push_back(FULL_JUG_B);
	if (isAllowEmptyJugA(state))
		operations.push_back(EMPTY_JUG_A);
	if (isAllowEmptyJugB(state))
		operations.push_back(EMPTY_JUG_B);
	if (isAllowPourA2B(state))
		operations.push_back(POUR_A_TO_B);
	if (isAllowPourB2A(state))
		operations.push_back(POUR_B_TO_A);
	return operations;
}

void Rule::setCapacityA(int capacityA){
	this->capacityA = capacityA;
}

int Rule::getCapacityA(){
	return capacityA;
}

void Rule::setCapacityB(int capacityB){
	this->capacityB = capacityB;
}

int Rule::getCapacityB(){
	return capacityB;
}

void Rule::setInitState(State *initState){
	this->initState = initState;
}

void Rule::setGoalState(State *goalState){
	this->goalState = goalState;
}

bool Rule::isGoalState(State *state){
	if (goalState->getJugA() == state->getJugA()
		|| goalState->getJugB() == state->getJugB())
		return true;
	return false;
}

int Rule::calculateDifferenceWithGoal(State *state){
	if (goalState->getJugA() > 0)
		return abs(goalState->getJugA() - state->getJugA());
	if (goalState->getJugB() > 0)
		return abs(goalState->getJugB() - state->getJugB());
}