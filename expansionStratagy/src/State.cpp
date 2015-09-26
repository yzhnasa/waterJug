#include "State.h"

State::State(){
	jugA = 0;
	jugB = 0;
	treeLevel = 0;
	differenceWithGoal = 0;
	distance = 0;
}

State::State(int jugA, int jugB){
	this->jugA = jugA;
	this->jugB = jugB;
	treeLevel = 0;
	differenceWithGoal = 0;
	distance = 0;
}

State::State(int jugA, int jugB, int treeLevel, int differenceWithGoal){
	this->jugA = jugA;
	this->jugB = jugB;
	this->treeLevel = treeLevel;
	this->differenceWithGoal = differenceWithGoal;
	this->distance = treeLevel + differenceWithGoal;
}

void State::setJugA(int jugA){
	this->jugA = jugA;
}

int State::getJugA(){
	return this->jugA;
}

void State::setJugB(int jugB){
	this->jugB = jugB;
}

int State::getJugB(){
	return this->jugB;
}

void State::setTreeLevel(int treeLevel){
	this->treeLevel = treeLevel;
}

int State::getTreeLevel(){
	return this->treeLevel;
}

void State::setDifferenceWithGoal(int differenceWithGoal){
	this->differenceWithGoal = differenceWithGoal;
}

int State::getDifferenceWithGoal(){
	return this->differenceWithGoal;
}

void State::calculateDistance(){
	distance = treeLevel + differenceWithGoal;
}

int State::getDistance(){
	return this->distance;
}

State::~State(){

}