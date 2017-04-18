#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// coordinate start from 1
const int boardSizeX = 8;
const int boardSizeY = 8;

int main() {
	int currentX = -1, currentY = -1;
	int direction = -1;

	// input the initial coordinate
	string temp;
	while (true) {
		printf("Please enter your initial coordinate: [X,Y]\n");
		cin >> temp;
		currentX = atoi(temp.substr(1, temp.find(",") - 1).c_str());
		currentY = atoi(temp.substr(temp.find(",") + 1, temp.find("]") - temp.find(",") - 1).c_str());
		if (currentX <= 0 || currentX > boardSizeX || currentY <= 0 || currentY > boardSizeY)
			printf("The coordinate is out of board, please enter again.\n");
		else
			break;
	}
	// input the initial direction
	while (true) {
		printf("Please enter your initial direction: W/S/N/E\n");
		cin >> temp;
		if (temp == "N")
			direction = NORTH;
		else if (temp == "E")
			direction = EAST;
		else if (temp == "S")
			direction = SOUTH;
		else if (temp == "W")
			direction = WEST;
		else {
			printf("Unknown direction, please enter again.\n");
			continue;
		}
		break;
	}
	// input the actions
	printf("Please enter a serie of actions(M,L,R): \n");
	cin >> temp;


	// calculate the moving
	for (int i = 0; i < temp.length(); i += 2) {
		switch(temp[i]) {
			case 'M':
				switch (direction) {
					case NORTH:
						currentY = min(currentY + 1, boardSizeY);
						break;
					case EAST:
						currentX = min(currentX + 1, boardSizeX);
						break;
					case SOUTH:
						currentY = max(currentY - 1, 1);
						break;
					case WEST:
						currentX = max(currentX - 1, 1);
						break;
				}
				break;

			case 'L':
				direction = (direction + 4 - 1) % 4;
				break;

			case 'R':
				direction = (direction + 1) % 4;
				break;

			default:
				printf("Unknown action.\n");
				break;
		}
	}
	// print out the result
	printf("Final location: [%d, %d]\n", currentX, currentY);
	printf("Final direction: ");
	switch (direction) {
		case NORTH:
			printf("NORTH\n");
			break;
		case EAST:
			printf("EAST\n");
			break;
		case SOUTH:
			printf("SOUTH\n");
			break;
		case WEST:
			printf("WEST\n");
			break;
	}

	return 0;
}
