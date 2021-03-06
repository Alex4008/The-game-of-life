#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <locale> 

using namespace std;

//Max size for a 2k monitor. 150x75

bool screen[150 - 2][75 - 1];

int screenWidth;
int screenLength;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void ShowConsoleCursor()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void PrintScreen(bool screen[150 - 2][75 - 1], int ranGenerations) {
	ShowConsoleCursor();
	CursorPosition.X = 0;
	CursorPosition.Y = 0;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << "Total Generations Ran: " << ranGenerations + 1 << endl;
	cout << endl;

	int sdWidthCounter = 0;
	int sdLengthCounter = 0;

	for (sdWidthCounter = 0; sdWidthCounter < screenWidth; sdWidthCounter++) {
		if (sdWidthCounter == screenWidth - 1) {
			cout << "*";
		}
		else {
			cout << "* ";
		}
	}
	cout << endl;

	sdWidthCounter = 0;
	sdLengthCounter = 0;

	for (sdLengthCounter = 0; sdLengthCounter < screenLength; sdLengthCounter++) {
		cout << "*";
		for (sdWidthCounter = 0; sdWidthCounter < screenWidth - 1; sdWidthCounter++) {
			if (screen[sdWidthCounter][sdLengthCounter] == true) {
				cout << "* ";
			}
			else {
				cout << "  ";
			}
		}
		cout << "*" << endl;
	}

	sdWidthCounter = 0;
	sdLengthCounter = 0;

	for (sdWidthCounter = 0; sdWidthCounter < screenWidth; sdWidthCounter++) {
		if (sdWidthCounter == screenWidth - 1) {
			cout << "*";
		}
		else {
			cout << "* ";
		}
	}
}

void arrayCopy(bool firstArray[150 - 2][75 - 1], bool secondArray[150 - 2][75 - 1]) {
	for (int i = 0; i < screenWidth; i++) {
		for (int j = 0; j < screenLength; j++) {
			secondArray[i][j] = firstArray[i][j];
		}
	}
}

int main() {
	int numGenerations;
	int ranGenerations;
	int randomNum;
	int count = 0;
	bool runAgain = true;
	int choice;
	int screenSize;
	bool validSize = false;
	int randomChance;
	cout << "Hello! Welcome to The Game of Life v1.2 By Alex Gray!" << endl;

	while (runAgain == true) {

		while (validSize == false) {
			cout << "What screen size would you like? (Warning, some sizes may not display properly. Be sure to fullscreen your command prompt.)" << endl;
			cout << "1. Extra Small." << endl; //30x15
			cout << "2. Small." << endl; //50x25
			cout << "3. Medium." << endl; //60x30
			cout << "4. Large." << endl; //90x45
			//cout << "5. Extra Large." << endl; //150x75
			cout << ">> ";
			cin >> screenSize;
			cout << endl;

			switch (screenSize) {
			case 1:
				validSize = true;
				cout << "You picked the Extra Small screen size of 30x15 pixels!" << endl;
				screenWidth = 30;
				screenLength = 15;
				randomChance = 3;
				break;

			case 2:
				validSize = true;
				cout << "You picked the Small screen size of 50x25 pixels!" << endl;
				screenWidth = 50;
				screenLength = 25;
				randomChance = 3;
				break;

			case 3:
				validSize = true;
				cout << "You picked the Medium screen size of 60x30 pixels!" << endl;
				screenWidth = 60;
				screenLength = 30;
				randomChance = 2;
				break;

			case 4:
				validSize = true;
				cout << "You picked the Large screen size of 90x45 pixels!" << endl;
				screenWidth = 90;
				screenLength = 45;
				randomChance = 2;
				break;

			/*case 5:
				validSize = true;
				cout << "You picked the Extra Large screen size of 150x75 pixels!" << endl;
				screenWidth = 150;
				screenLength = 75;
				randomChance = 2;
				break;*/

			default:
				system("CLS");
				cout << "That is not a valid option. Please pick a valid screen size." << endl;
				break;
			}
		}
		validSize = false;
		int const arrayWidthMax = (screenWidth - 2);
		int const arrayLengthMax = (screenLength - 1);

		ranGenerations = 0;
		cout << "How many generations would you like to run?" << endl << ">> ";
		cin >> numGenerations;
		cout << endl;
		int const numGenConst = numGenerations;
		cout << "Running " << numGenerations << " Generations!" << endl;
		cout << "Starting simulation in 2 seconds." << endl;
		Sleep(2000);
		system("CLS");
		//Draw a random set of pixels.
		for (int pWidth = 0; pWidth < arrayWidthMax; pWidth++) {
			for (int pLength = 0; pLength < arrayLengthMax; pLength++) {
				randomNum = (rand() % 8) + 1;
				if (randomNum < randomChance) {
					screen[pWidth][pLength] = true;
				}
				else {
					screen[pWidth][pLength] = false;
				}
			}
		}

		while (ranGenerations < numGenConst) {
			PrintScreen(screen, ranGenerations);
			bool newScreen[150 - 2][75 - 1];
			for (int width = 0; width < screenWidth; width++) {
				for (int length = 0; length < screenLength; length++) {
					count = 0;
					//Checking for corners.
					if (width == 0 && length == 0) { //Top-left corner
						if (screen[width + 1][length] == true) { //Right
							count++;
						}
						if (screen[width + arrayWidthMax][length] == true) { //Left *
							count++;
						}
						if (screen[width][length + arrayLengthMax] == true) { //Above *
							count++;
						}
						if (screen[width][length - 1] == true) { //Below
							count++;
						}
						if (screen[width + 1][length + arrayLengthMax] == true) { //Upper-right *
							count++;
						}
						if (screen[width + arrayWidthMax][length + arrayLengthMax] == true) { //Upper-left *
							count++;
						}
						if (screen[width + 1][length - 1] == true) { //Lower-right
							count++;
						}
						if (screen[width + arrayWidthMax][length - 1] == true) { //Lower-left *
							count++;
						}
					}
					else if (width == 0 && length == (screenLength - 1)) { //Bottom-left corner
						if (screen[width + 1][length] == true) { //Right
							count++;
						}
						if (screen[width + arrayWidthMax][length] == true) { //Left *
							count++;
						}
						if (screen[width][length + 1] == true) { //Above
							count++;
						}
						if (screen[width][0] == true) { //Below *
							count++;
						}
						if (screen[width + 1][length + 1] == true) { //Upper-right
							count++;
						}
						if (screen[width + arrayWidthMax][length + 1] == true) { //Upper-left *
							count++;
						}
						if (screen[width + 1][0] == true) { //Lower-right *
							count++;
						}
						if (screen[width + arrayWidthMax][0] == true) { //Lower-left *
							count++;
						}
					}
					else if (width == (screenWidth - 2) && length == 0) { //Top-right corner
						if (screen[0][length] == true) { //Right *
							count++;
						}
						if (screen[width - 1][length] == true) { //Left
							count++;
						}
						if (screen[width][length + arrayLengthMax] == true) { //Above *
							count++;
						}
						if (screen[width][length - 1] == true) { //Below
							count++;
						}
						if (screen[0][length + arrayLengthMax] == true) { //Upper-right *
							count++;
						}
						if (screen[width - 1][length + arrayLengthMax] == true) { //Upper-left *
							count++;
						}
						if (screen[0][length - 1] == true) { //Lower-right *
							count++;
						}
						if (screen[width - 1][length - 1] == true) { //Lower-left
							count++;
						}
					}
					else if (width == (screenWidth - 2) && length == (screenLength - 1)) { //Bottom-right corner
						if (screen[0][length] == true) { //Right *
							count++;
						}
						if (screen[width - 1][length] == true) { //Left
							count++;
						}
						if (screen[width][length + 1] == true) { //Above
							count++;
						}
						if (screen[width][0] == true) { //Below *
							count++;
						}
						if (screen[0][length + 1] == true) { //Upper-right *
							count++;
						}
						if (screen[width - 1][length + 1] == true) { //Upper-left
							count++;
						}
						if (screen[0][0] == true) { //Lower-right
							count++;
						}
						if (screen[width - 1][0] == true) { //Lower-left *
							count++;
						}
					}
					//Done
					else if (width == 0) {
						if (screen[width + 1][length] == true) { //Right
							count++;
						}
						if (screen[width + arrayWidthMax][length] == true) { //Left *
							count++;
						}
						if (screen[width][length + 1] == true) { //Above
							count++;
						}
						if (screen[width][length - 1] == true) { //Below
							count++;
						}
						if (screen[width + 1][length + 1] == true) { //Upper-right
							count++;
						}
						if (screen[width + arrayWidthMax][length + 1] == true) { //Upper-left *
							count++;
						}
						if (screen[width + 1][length - 1] == true) { //Lower-right
							count++;
						}
						if (screen[width + arrayWidthMax][length - 1] == true) { //Lower-left *
							count++;
						}
					}
					else if (width == arrayWidthMax) {
						if (screen[0][length] == true) { //Right *
							count++;
						}
						if (screen[width - 1][length] == true) { //Left
							count++;
						}
						if (screen[width][length + 1] == true) { //Above
							count++;
						}
						if (screen[width][length - 1] == true) { //Below
							count++;
						}
						if (screen[0][length + 1] == true) { //Upper-right *
							count++;
						}
						if (screen[width - 1][length + 1] == true) { //Upper-left
							count++;
						}
						if (screen[0][length - 1] == true) { //Lower-right *
							count++;
						}
						if (screen[width - 1][length - 1] == true) { //Lower-left
							count++;
						}
					}
					else if (length == 0) {
						if (screen[width + 1][length] == true) { //Right
							count++;
						}
						if (screen[width - 1][length] == true) { //Left
							count++;
						}
						if (screen[width][length + arrayLengthMax] == true) { //Above *
							count++;
						}
						if (screen[width][length - 1] == true) { //Below
							count++;
						}
						if (screen[width + 1][length + arrayLengthMax] == true) { //Upper-right *
							count++;
						}
						if (screen[width - 1][length + arrayLengthMax] == true) { //Upper-left *
							count++;
						}
						if (screen[width + 1][length - 1] == true) { //Lower-right
							count++;
						}
						if (screen[width - 1][length - 1] == true) { //Lower-left
							count++;
						}
					}
					else if (length == arrayLengthMax) {
						if (screen[width + 1][length] == true) { //Right
							count++;
						}
						if (screen[width - 1][length] == true) { //Left
							count++;
						}
						if (screen[width][length + 1] == true) { //Above
							count++;
						}
						if (screen[width][0] == true) { //Below *
							count++;
						}
						if (screen[width + 1][length + 1] == true) { //Upper-right
							count++;
						}
						if (screen[width - 1][length + 1] == true) { //Upper-left
							count++;
						}
						if (screen[width + 1][0] == true) { //Lower-right *
							count++;
						}
						if (screen[width - 1][0] == true) { //Lower-left *
							count++;
						}
					}
					else {
						if (screen[width + 1][length] == true) { //Right
							count++;
						}
						if (screen[width - 1][length] == true) { //Left
							count++;
						}
						if (screen[width][length + 1] == true) { //Above
							count++;
						}
						if (screen[width][length - 1] == true) { //Below
							count++;
						}
						if (screen[width + 1][length + 1] == true) { //Upper-right
							count++;
						}
						if (screen[width - 1][length + 1] == true) { //Upper-left
							count++;
						}
						if (screen[width + 1][length - 1] == true) { //Lower-right
							count++;
						}
						if (screen[width - 1][length - 1] == true) { //Lower-left
							count++;
						}
					}

					if (screen[width][length] == true) {
						if (count < 2) { //1. Less then 2, dies
							newScreen[width][length] = false;
						}
						else if (count == 2 || count == 3) { //2. Lives on.
							newScreen[width][length] = true;
						}
						else if (count > 3) { //3. Dies from over population.
							newScreen[width][length] = false;
						}
					}
					else {
						if (count == 3) {
							newScreen[width][length] = true; //4. Becomes reborn.
						}
					}
				}
			}
			arrayCopy(newScreen, screen);
			Sleep(50);
			ranGenerations++;
		}
		cout << endl;
		cout << "Simulation complete!" << endl;
		cout << "Ran " << ranGenerations << " Generations!" << endl;
		cout << "Would you like to run another simulation? (0 or 1)" << endl << ">> ";
		cin >> choice;
		if (choice == 1) {
			runAgain = true;
		}
		else {
			runAgain = false;
		}
		system("CLS");
	}
	cout << "Thank you for 'playing' !" << endl;
	cout << "Shutting down";
	Sleep(500);
	cout << ".";
	Sleep(500);
	cout << ".";
	Sleep(500);
	cout << ".";
	Sleep(1000);

}