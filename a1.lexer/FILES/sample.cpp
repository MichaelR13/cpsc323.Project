// place holder
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <string.h>

using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");
//=========================================================================
// Function to check if a key value matches a value in an array
//=========================================================================
bool in_array(char key, char* arr, int size) {
	for (int i = 0; i < size; i++) {
		if (key == arr[i]) {
			return true;
		}
	}
	return false;
}
//=========================================================================a
// Function to check if a number:integer or a real number
//=========================================================================
string getNumOrReal(char number) {

	//====================================================================
	//Finite state machine that can tell if int or real number or invalid
	// States:
	//		1 - Integer
	//		2 - Real
	//		3 - Invalid
	//====================================================================
	int finiteStateMachine[4][3] = {
				/*Initial State 0*/	 {1, 3, 3},
				/*State 1*/		 {1, 2, 3},
				/*State 2*/		 {2, 3, 3},
				/*State 3*/		 {3, 3, 3}
									};


	//====================================================================
	// Pointer keeping track of position in finite state machine
	// Starts at State 1 because we already know the first char is a number
	//====================================================================
	int position = 1;

	char buf[100];
	buf[0] = number;
	int index = 1;

	char nextChar;
	while (nextChar = fin.peek()) {
		if (isdigit(nextChar)) {
			position = finiteStateMachine[position][0];
		}
		else if (nextChar == '.') {
			position = finiteStateMachine[position][1];
		}
		else {
			position = finiteStateMachine[position][2];
		}

		if (position == 3) {
			buf[index] = '\0';
			break;
		}
		else {
			buf[index++] = nextChar;
		}
		fin.get();
	}
	return buf;
}

string isKeyword(char buffer[]) {
	string keywords[14] = { "real", "int", "function", "if", "fi", "for", "while", "return", "get", "put", "otherwise", "boolean", "true", "false" };
	int i, flag = 0;

	for (i = 0; i < 14; ++i) {
		if (strcmp(keywords[i].c_str(), buffer) == 0) {
			return keywords[i];
		}
	}
	return "-1";
}

void lex() {
	char ch;

	if (!fin.is_open()) {
		cout << "error while opening the file\n";
		exit(0);
	}
	while (!fin.eof()) {
		ch = fin.get();
		char operators[8]= { '+', '-', '/', '*', '=', '<', '!' };
		char seperators[10] = { '%', ')', '(', ';', '{', '}', '[', ',', ']', '*' };

		if (isalpha(ch)) {
			int finiteStateMachine[4][3] = {
						/*Initial State 0*/{1, 3, 3},
						/*State 1 id*/		 {1, 2, 3},
						/*State 2 key*/		 {2, 3, 3},
						/*State 3 inv*/		 {3, 3, 3}
			};
			int index = 0;
			char identifier[100];
			identifier[0] = ch;
			char next = fin.peek();
			while (isalnum(next) || next == '_') {
				index++;
				identifier[index] = next;
				fin.get();
				next = fin.peek();
			}
			identifier[++index] = '\0';
			string keyword = isKeyword(identifier);
			if (keyword != "-1") {
				cout << keyword << ":keyword\n";
				fout << keyword << ":keyword\n";
			}
			else {
				cout << identifier << ":identifier\n";
				fout << identifier << ":identifier\n";
			}
		}

		else if (isdigit(ch)) {
			string number = getNumOrReal(ch);
			if (number.find(".") != -1) {
				cout << number << ":real\n";
				fout << number << ":real\n";
			}
			else {
				cout << number << ":integer\n";
				fout << number << ":integer\n";
			}
		}

		else if (in_array(ch, seperators, 10)) {
			char next = fin.peek();
			if (next == '%') {
				cout << ch << next << ":seperator\n";
				fout << ch << next << ":seperator\n";
				fin.get();
			}
			else if (next == ']') { //handles *]
				cout << ch << next << ":seperator\n";
				fout << ch << next << ":seperator\n";
				fin.get();
			}
			else if (next == '*') { //handles [*
				cout << ch << next << ":seperator\n";
				fout << ch << next << ":seperator\n";
				fin.get();
				char seeker;
				while(seeker != '*'){
					fin.get(seeker);
				}
				fin.unget();
			}
			else if (ch == '*'){ //Since * can be an operator or beginning of sep, we need this to handle it being an op.
				cout << ch << ":operator\n";
				fout << ch << ":operator\n";
			}
			else {
				cout << ch << ":seperator\n";
				fout << ch << ":seperator\n";
			}
		}

		else if (in_array(ch, operators, 8)) {
			char next = fin.peek();
			if (next == '>') {
				cout << ch << next << ":operator\n";
				fout << ch << next << ":operator\n";
				fin.get();
			}
			else if (next == '=') {
				cout << ch << next << ":operator\n";
				fout << ch << next << ":operator\n";
				fin.get();
			}
			else {
				cout << ch << ":operator\n";
				fout << ch << ":operator\n";
			}
		}
	}
	fout.close();
	fin.close();
}
int main(){
	lex();
	return 0;
}