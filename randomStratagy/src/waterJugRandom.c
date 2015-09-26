#define _CRT_SECURE_NO_DEPRECATE
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_STATE   0
#define FULL_JUG_A      1
#define FULL_JUG_B      2
#define EMPTY_JUG_A     3
#define EMPTY_JUG_B     4
#define POUR_A_TO_B     5
#define POUR_B_TO_A     6


void setInitJug(int *jug, int initValue){
	*jug = initValue;
}

void fullJug(int currentState, int *jug, int capacityA, int capacityB){
	if (currentState == FULL_JUG_A)
		*jug = capacityA;
	if (currentState == FULL_JUG_B)
		*jug = capacityB;
}

void emptyJug(int *jug){
	*jug = 0;
}

void pourJug(int currentState, int *jugA, int *jugB, int capacityA, int capacityB){
	if (currentState == POUR_A_TO_B){
		if (*jugA + *jugB > capacityB){
			*jugA = *jugA - (capacityB - *jugB);
			*jugB = capacityB;
		}
		else{
			*jugB = *jugB + *jugA;
			*jugA = 0;
		}
	}

	if (currentState == POUR_B_TO_A){
		if (*jugA + *jugB > capacityA){
			*jugB = *jugB - (capacityA - *jugA);
			*jugA = capacityA;
		}
		else{
			*jugA = *jugA + *jugB;
			*jugB = 0;
		}
	}
}

void updateState(int *currentState){
	*currentState = 1 + rand() % 6;
}

void solveWaterJugPuzzle(int currentState, int *jugA, int *jugB, int initA, int initB, int capacityA, int capacityB, FILE *outputFile){
	switch (currentState){
	case INITIAL_STATE:
		setInitJug(jugA, initA);
		setInitJug(jugB, initB);
		fprintf(outputFile, "Strategy A\n");
		fprintf(outputFile, "Starting out with  %d-gallon jug and a  %d-gallon jug              -- state:(%d,%d)\n", capacityA, capacityB, initA, initB);
		break;
	case FULL_JUG_A:
		fullJug(currentState, jugA, capacityA, capacityB);
		fprintf(outputFile, "Fill the  %d-gallon jug                                           -- state:(%d,%d)\n", capacityA, *jugA, *jugB);
		break;
	case FULL_JUG_B:
		fullJug(currentState, jugB, capacityA, capacityB);
		fprintf(outputFile, "Fill the  %d-gallon jug                                           -- state:(%d,%d)\n", capacityB, *jugA, initB);
		break;
	case EMPTY_JUG_A:
		emptyJug(jugA);
		fprintf(outputFile, "Empty the  %d-gallon jug                                          -- state:(%d,%d)\n", capacityA, *jugA, *jugB);
		break;
	case EMPTY_JUG_B:
		emptyJug(jugB);
		fprintf(outputFile, "Empty the  %d-gallon jug                                          -- state:(%d,%d)\n", capacityB, *jugA, *jugB);
		break;
	case POUR_A_TO_B:
		pourJug(currentState, jugA, jugB, capacityA, capacityB);
		fprintf(outputFile, "Pour water from the  %d-gallon jug into the  %d-gallon jug         -- state:(%d,%d)\n", capacityA, capacityB, *jugA, *jugB);
		break;
	case POUR_B_TO_A:
		pourJug(currentState, jugA, jugB, capacityA, capacityB);
		fprintf(outputFile, "Pour water from the  %d-gallon jug into the  %d-gallon jug         -- state:(%d,%d)\n", capacityB, capacityA, *jugA, *jugB);
		break;
	}
}

void readInputFile(FILE *file, int *capacityA, int *capacityB, int *initA, int *initB, int *goalA, int *goalB){
	char line[30];
	int dataIndex = 0;
	int len = 30;
	fgets(line, 30, file);
	dataIndex = strchr(line, ':') - line + 2;
	*capacityA = line[dataIndex] - '0';

	fgets(line, 30, file);
	dataIndex = strchr(line, ':') - line + 2;
	*capacityB = line[dataIndex] - '0';

	fgets(line, 30, file);
	dataIndex = strchr(line, ':') - line + 2;
	*initA = line[dataIndex] - '0';
	*initB = line[dataIndex + 2] - '0';

	fgets(line, 30, file);
	dataIndex = strchr(line, ':') - line + 2;
	if (line[dataIndex] == '-'){
		*goalA = -(line[dataIndex + 1] - '0');
		*goalB = line[dataIndex + 3] - '0';
	}else{
		*goalA = line[dataIndex] - '0';
		if (line[dataIndex + 2] == '-')
			*goalB = -(line[dataIndex + 3] - '0');
		else
			*goalB = line[dataIndex + 2] - '0';
	}
}

int main(int argc, char *argv[]){
	if (argc != 3){
		printf("Please provide input file and output filename.\n");
		exit(EXIT_FAILURE);
	}

	FILE *inputFile = fopen(argv[1], "r");
	if (NULL == inputFile){
		fprintf(stderr, "File %s not exit.\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	int capacityA;
	int capacityB;
	int initA;
	int initB;
	int goalA;
	int goalB;
	int currentState = INITIAL_STATE;
	int jugA;
	int jugB;
	readInputFile(inputFile, &capacityA, &capacityB, &initA, &initB, &goalA, &goalB);
	fclose(inputFile);

	FILE *outputFile = fopen(argv[2], "w");
	if (NULL == outputFile){
		fprintf(stderr, "Output data to file %s fail.\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	int i;
	for (i = 0; i < 250; i++){
		solveWaterJugPuzzle(currentState, &jugA, &jugB, initA, initB, capacityA, capacityB, outputFile);
		if (goalA >= 0 && jugA == goalA){
			printf("Water jug puzzle finished.\n");
			return 0;
		}
		if (goalB >= 0 && jugB == goalB){
			printf("Water jug puzzle finished.\n");
			return 0;
		}
		updateState(&currentState);
	}
	printf("Haven't finished or not found solution.\n");
	fclose(outputFile);
	return 0;
}
