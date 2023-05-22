//ЮФУ, ИКТИБ, МОП ЭВМ
//ПиОТА 2
//ИЗ 4
//КТБО1-7
//Тимошенко Глеб Романович
//22.05.2023

#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
using namespace std;

typedef struct table {
	string replacingSymbol;
	string pastingSymbol;
	bool isEndPoint;
}table;

vector <table> readIpnut(string fileName) {
	ifstream fin(fileName);
	int numOfOperations;

	fin >> numOfOperations;
	vector <table> inputTable(numOfOperations);

	for (int i = 0; i < numOfOperations; i++) {
		fin >> inputTable[i].replacingSymbol >> inputTable[i].pastingSymbol >> inputTable[i].isEndPoint;
		if (inputTable[i].replacingSymbol == "spc") inputTable[i].replacingSymbol = " ";
		if (inputTable[i].pastingSymbol == "nth") inputTable[i].pastingSymbol = "";
	}

	return inputTable;
}

bool readConsole(string a) {
	int inputIsCorrect = 1;

	for (int i = 0; i < a.size(); i++) {
		if (a[i] != '-' && 
			a[i] != '0' && 
			a[i] != '1' && 
			a[i] != '2' && 
			a[i] != '3') {
			inputIsCorrect = 0;
			break;
		}
	}

	return inputIsCorrect;
}

void processSimulator(vector<table>& inputTable, string& inputString, int& endPointOccured) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < inputTable.size(); i++) {

		int doesExist = inputString.find(inputTable[i].replacingSymbol);

		if (doesExist!=-1) {

			cout << "(" << i << ")";

			for (int j = 0; j < inputString.size(); j++) {
				if (j == doesExist) SetConsoleTextAttribute(hConsole, 4);
				if (j == doesExist + inputTable[i].replacingSymbol.size())	SetConsoleTextAttribute(hConsole, 7);
				cout << inputString[j];
			}

			SetConsoleTextAttribute(hConsole, 7);
			cout << " ->";

			inputString.replace(
				inputString.find(inputTable[i].replacingSymbol),
				inputTable[i].replacingSymbol.size(),
				inputTable[i].pastingSymbol
			);
			endPointOccured = inputTable[i].isEndPoint;

			break;
		}	
	}

	cout << inputString << endl;
}

int main() {
	setlocale(LC_ALL, "Russian");

	string inputString;

	vector <table> inputTable = readIpnut("input.txt");
	int inputIsCorrect, stop = 0;

	while (!stop) {
		int endPointOccured = 0;
		cout << "Введите строку: ";
		cin >> inputString;
		inputIsCorrect = readConsole(inputString);
		if (!inputIsCorrect) {
			cout << "Введена некорректная строка." << endl;
		}
		else {
			while (!endPointOccured) {
				if (inputString[0] != ' ') {
					inputString = " " + inputString;
				}
				processSimulator(inputTable, inputString, endPointOccured);
			}
		}
		cout << endl << "Программа завершила работу." << endl << "Введите:"
			<< endl << "1 - Если хотите ввести строку заново."
			<< endl << "2 - Если хотите выйти из программы." << endl;

		int ans;
		cin >> ans; cout << endl;

		if (ans == 1) continue;
		else if (ans == 2)
		{
			cout << "Программа закончила работу." << endl;
			stop = 1;
		}
		else {
			cout << "Такой комманды не существует!" << endl;
			cout << "Программа закончила работу." << endl;
			stop = 1;
		}
	}
	return 0;
}

