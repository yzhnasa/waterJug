#include "Main.h"

int main(int argc, char *argv[]){
	if (argc != 3){
		printf("Please provide input file and output filename.\n");
		exit(EXIT_FAILURE);
	}

	StateExpansion stateExpression;
	vector<State *> results = stateExpression.stateExpension(string(argv[1]), string(argv[2]));
	for (int i = 0; i < results.size(); i++){
		cout << "(" << results.at(i)->getJugA() << ", " << results.at(i)->getJugB() << ")" << endl;
	}
	return 0;
}