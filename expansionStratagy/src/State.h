#ifndef __STATE_H__
#define __STATE_H__
using namespace std;

class State{
private:
	int jugA;
	int jugB;
	int treeLevel;
	int differenceWithGoal;
	int distance;
public:
	State();
	State(int jugA, int jugB);
	State(int jugA, int jugB, int treeLevel, int differenceWithGoal);
	void setJugA(int jugA);
	int getJugA();
	void setJugB(int jugB);
	int getJugB();
	void setTreeLevel(int treeLevel);
	int getTreeLevel();
	void setDifferenceWithGoal(int differenceWithGoal);
	int getDifferenceWithGoal();
	void calculateDistance();
	int getDistance();
	~State();
};
#endif