#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// coordinate start from 1
const int boardSizeX = 8;
const int boardSizeY = 8;

void goToTarget(int currentX, int currentY, int direction, int targetX, int targetY, int targetDirection, vector<char> path, int remainActions);

int main() {
	int currentX = -1, currentY = -1, targetX = -1, targetY = -1;
	int direction = -1, targetDirection = -1;
	int actionsNumber = -1;

	string temp;
	// input the initial coordinate
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
	// input the target coordinate
	while (true) {
		printf("Please enter your target coordinate: [X,Y]\n");
		cin >> temp;
		targetX = atoi(temp.substr(1, temp.find(",") - 1).c_str());
		targetY = atoi(temp.substr(temp.find(",") + 1, temp.find("]") - temp.find(",") - 1).c_str());
		if (targetX <= 0 || targetX > boardSizeX || targetY <= 0 || targetY > boardSizeY)
			printf("The coordinate is out of board, please enter again.\n");
		else
			break;
	}
	// input the initial direction
	while (true) {
		printf("Please enter your target direction: W/S/N/E\n");
		cin >> temp;
		if (temp == "N")
			targetDirection = NORTH;
		else if (temp == "E")
			targetDirection = EAST;
		else if (temp == "S")
			targetDirection = SOUTH;
		else if (temp == "W")
			targetDirection = WEST;
		else {
			printf("Unknown direction, please enter again.\n");
			continue;
		}
		break;
	}
	// input the maximum number of actions
	printf("Please enter maximum number of actions:\n");
	cin >> actionsNumber;

	// printf("%d %d %d %d %d %d %d\n", currentX, currentY, direction, targetX, targetY, targetDirection, actionsNumber);

	// calculate all possible actions
	vector<char> path;
	goToTarget(currentX, currentY, direction, targetX, targetY, targetDirection, path, actionsNumber);
	printf("No more possible actions!\n");

	return 0;
}

void goToTarget(int currentX, int currentY, int direction, int targetX, int targetY, int targetDirection, vector<char> path, int remainActions) {
	// determine if arrived
	if (currentX == targetX && currentY == targetY && direction == targetDirection) {
		for (int i = 0; i < path.size(); i++)
			printf("%c ", path[i]);
		printf("\n");
		// return;
	}

	if (remainActions <= 0)
		return;

	// determine if possible to arrive the target position, there are 2 possible turning ways
	int directionX = (targetX >= currentX) ? EAST : WEST;
	int directionY = (targetY >= currentY) ? NORTH : SOUTH;
	int currentDirection = direction;
	int steps1 = 0, steps2 = 0;

	if (currentX != targetX) {
		steps1 += ((abs(currentDirection - directionX) == 3) ? 1 : abs(currentDirection - directionX));
		steps1 += abs(targetX - currentX);
		currentDirection = directionX;
	}
	if (currentY != targetY) {
		steps1 += ((abs(currentDirection - directionY) == 3) ? 1 : abs(currentDirection - directionY));
		steps1 += abs(targetY - currentY);
		currentDirection = directionY;
	}
	if (currentDirection != targetDirection) {
		steps1 += ((abs(currentDirection - targetDirection) == 3) ? 1 : abs(currentDirection - targetDirection));
	}

	currentDirection = direction;
	if (currentY != targetY) {
		steps2 += ((abs(currentDirection - directionY) == 3) ? 1 : abs(currentDirection - directionY));
		steps2 += abs(targetY - currentY);
		currentDirection = directionY;
	}
	if (currentX != targetX) {
		steps2 += ((abs(currentDirection - directionX) == 3) ? 1 : abs(currentDirection - directionX));
		steps2 += abs(targetX - currentX);
		currentDirection = directionX;
	}
	if (currentDirection != targetDirection) {
		steps2 += ((abs(currentDirection - targetDirection) == 3) ? 1 : abs(currentDirection - targetDirection));
	}

	// printf("needs %d\n", min(steps1, steps2));
	if (min(steps1, steps2) > remainActions) // not enough remain actions
		return;


	// if remain actions enough, do Move/Turn Left/Turn Right
	path.push_back('M');
	if (!(currentX == 1 && direction == WEST) && !(currentX == boardSizeX && direction == EAST) && !(currentY == 1 && direction == SOUTH) && !(currentY == boardSizeY && direction == NORTH)) {
		// if not move toward the board boundary
		switch (direction) {
			case NORTH:
				goToTarget(currentX, currentY + 1, direction, targetX, targetY, targetDirection, path, remainActions - 1);
				break;
			case EAST:
				goToTarget(currentX + 1, currentY, direction, targetX, targetY, targetDirection, path, remainActions - 1);
				break;
			case SOUTH:
				goToTarget(currentX, currentY - 1, direction, targetX, targetY, targetDirection, path, remainActions - 1);
				break;
			case WEST:
				goToTarget(currentX - 1, currentY, direction, targetX, targetY, targetDirection, path, remainActions - 1);
				break;
		}
	}

	path.pop_back();
	path.push_back('L');
	goToTarget(currentX, currentY, (direction + 4 - 1) % 4, targetX, targetY, targetDirection, path, remainActions - 1);

	path.pop_back();
	path.push_back('R');
	goToTarget(currentX, currentY, (direction + 1) % 4, targetX, targetY, targetDirection, path, remainActions - 1);
}
