#include "StateExpansion.h"

void StateExpansion::splitString(string &line, vector<string> &tokens){
	vector<char> token;
	for (int i = 0; i != line.size(); i++){
		if (line[i] == ' '){
			if (!token.empty())
				tokens.push_back(string(token.begin(), token.end()));
			token.clear();
		}
		else
			token.push_back(line[i]);
	}
	tokens.push_back(string(token.begin(), token.end()));
}

State *StateExpansion::fullJug(int operation, State *state, Rule &rule){
	State *newState = new State();
	if (operation == FULL_JUG_A){
		newState->setJugA(rule.getCapacityA());
		newState->setJugB(state->getJugB());
	}

	if (operation == FULL_JUG_B){
		newState->setJugA(state->getJugA());
		newState->setJugB(rule.getCapacityB());
	}

	newState->setTreeLevel(state->getTreeLevel() + 1);
	newState->setDifferenceWithGoal(rule.calculateDifferenceWithGoal(newState));
	newState->calculateDistance();
	return newState;
}

State *StateExpansion::emptyJug(int operation, State *state, Rule &rule){
	State *newState = new State();
	if (operation == EMPTY_JUG_A){
		newState->setJugA(0);
		newState->setJugB(state->getJugB());
	}

	if (operation == EMPTY_JUG_B){
		newState->setJugA(state->getJugA());
		newState->setJugB(0);
	}

	newState->setTreeLevel(state->getTreeLevel() + 1);
	newState->setDifferenceWithGoal(rule.calculateDifferenceWithGoal(newState));
	newState->calculateDistance();
	return newState;
}

State *StateExpansion::pourJug(int operation, State *state, Rule &rule){
	State *newState = new State();
	if (operation == POUR_A_TO_B){
		if (state->getJugA() + state->getJugB() > rule.getCapacityB()){
			newState->setJugA(state->getJugA() - (rule.getCapacityB() - state->getJugB()));
			newState->setJugB(rule.getCapacityB());
		}
		else{
			newState->setJugB(state->getJugA() + state->getJugB());
			newState->setJugA(0);
		}
	}

	if (operation == POUR_B_TO_A){
		if (state->getJugA() + state->getJugB() > rule.getCapacityA()){
			newState->setJugB(state->getJugB() - (rule.getCapacityA() - state->getJugA()));
			newState->setJugA(rule.getCapacityA());
		}
		else{
			newState->setJugA(state->getJugA() + state->getJugB());
			newState->setJugB(0);
		}
	}

	newState->setTreeLevel(state->getTreeLevel() + 1);
	newState->setDifferenceWithGoal(rule.calculateDifferenceWithGoal(newState));
	newState->calculateDistance();
	return newState;
}

void StateExpansion::parcingInputFile(string file, State *&initState, State *&goalState, int &capacityA, int &capacityB){
	fstream inputStream(file.c_str(), ios::in);
	string line;
	vector<string> tokens;
	
	getline(inputStream, line);
	splitString(line, tokens);
	//capacityA = stoi(tokens.at(4));
	capacityA = atoi(tokens.at(4).c_str());
	line.clear();
	tokens.clear();
	
	getline(inputStream, line);
	splitString(line, tokens);
	//capacityB = stoi(tokens.at(4));
	capacityB = atoi(tokens.at(4).c_str());
	line.clear();
	tokens.clear();

	getline(inputStream, line);
	splitString(line, tokens);
	initState = new State();
	//initState->setJugA(stoi(tokens.at(2)));
	//initState->setJugB(stoi(tokens.at(3)));
	initState->setJugA(atoi(tokens.at(2).c_str()));
	initState->setJugB(atoi(tokens.at(3).c_str()));
	line.clear();
	tokens.clear();

	getline(inputStream, line);
	splitString(line, tokens);
	goalState = new State();
	//goalState->setJugA(stoi(tokens.at(2)));
	//goalState->setJugB(stoi(tokens.at(3)));
	goalState->setJugA(atoi(tokens.at(2).c_str()));
	goalState->setJugB(atoi(tokens.at(3).c_str()));
	line.clear();
	tokens.clear();
	inputStream.close();
}

State *StateExpansion::solveWaterJugPuzzle(fstream &outputStream, int operation, State *state, Rule &rule){
	State *newState = NULL;
	switch (operation){
		case INITIAL_STATE:
			outputStream << "Strategy A\n" << endl;
			outputStream << "Starting out with  " << rule.getCapacityA()
				<< "-gallon jug and a  " << rule.getCapacityB() 
				<< "-gallon jug              -- state:(" 
				<< state->getJugA() << "," << state->getJugB() << ")" << endl;
			break;
		case FULL_JUG_A:
			newState = fullJug(operation, state, rule);
			outputStream << "Fill the  " << rule.getCapacityA() 
				<< "-gallon jug                                           -- state:("
				<< newState->getJugA() << "," << newState->getJugB() << ")" << endl;
			break;
		case FULL_JUG_B:
			newState = fullJug(operation, state, rule);
			outputStream << "Fill the  " << rule.getCapacityB()
				<< "-gallon jug                                           -- state:("
				<< newState->getJugA() << "," << newState->getJugB() << ")" << endl;
			break;
		case EMPTY_JUG_A:
			newState = emptyJug(operation, state, rule);
			outputStream << "Empty the  " << rule.getCapacityA() 
				<< "-gallon jug                                          -- state:("
				<< newState->getJugA() << "," << newState->getJugB() << ")" << endl;
			break;
		case EMPTY_JUG_B:
			newState = emptyJug(operation, state, rule);
			outputStream << "Empty the  " << rule.getCapacityB()
				<< "-gallon jug                                          -- state:("
				<< newState->getJugA() << "," << newState->getJugB() << ")" << endl;
			break;
		case POUR_A_TO_B:
			newState = pourJug(operation, state, rule);
			outputStream << "Pour water from the  " << rule.getCapacityA()
				<< "-gallon jug into the  " << rule.getCapacityB()
				<< "-gallon jug         -- state:(" << newState->getJugA() << ","
				<< newState->getJugB() << ")" << endl;
			break;
		case POUR_B_TO_A:
			newState = pourJug(operation, state, rule);
			outputStream << "Pour water from the  " << rule.getCapacityB()
				<< "-gallon jug into the  " << rule.getCapacityA()
				<< "-gallon jug         -- state:(" << newState->getJugA() << ","
				<< newState->getJugB() << ")" << endl;
			break;
	}
	return newState;
}

vector<State *> StateExpansion::stateExpension(string inputFilename, string outputFilename){
	vector<State *> results;
	State *initState = NULL;
	State *goalState = NULL;
	int capacityA;
	int capacityB;
	parcingInputFile(inputFilename, initState, goalState, capacityA, capacityB);
	Rule rule;
	rule.setCapacityA(capacityA);
	rule.setCapacityB(capacityB);
	rule.setInitState(initState);
	rule.setGoalState(goalState);

	fstream outputStream(outputFilename.c_str(), ios::out);
	vector<int> operations;
	State *oldState = NULL;
	State *newState = NULL;
	states.push(initState);
	solveWaterJugPuzzle(outputStream, INITIAL_STATE, initState, rule);
	while (!states.empty()){
		oldState = states.top();
		expandedStates.push_back(oldState);
		states.pop();
		operations = rule.allowedOperation(oldState);
		for (unsigned int i = 0; i < operations.size(); i++){
			newState = solveWaterJugPuzzle(outputStream, operations.at(i), oldState, rule);
			if (rule.isGoalState(newState))
				results.push_back(newState);
			else{
				if (!rule.isSameWithExpandedState(expandedStates, newState)){
					states.push(newState);
				}
				else
					delete newState;
			}
		}
	}
	outputStream.close();
	return results;
}
