#include "helper.h"
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

bool isSplitterSuggestion(const char& ch) {
	return ch == '.' || ch == '?' || ch == '!' || ch == '-' || ch == '\n' || ch == '\0';
}

bool isSpase(const char& ch) {
	return ch == ' ' || ch == '\n' || ch == '\0';
}

string task(const string& s) {
	string ans;
	bool isWord = false, isSuggestion = false;
	int startSuggestoin = 0;
	for (int i = 1; i < s.size(); i++)
		if (isSplitterSuggestion(s[i])) {
			if (s[startSuggestoin] == '-' && (startSuggestoin == 0 || isSpase(s[startSuggestoin - 1]))) {
				if (startSuggestoin != 0 && s[startSuggestoin - 1] == ' ')
					ans.append(s.substr(startSuggestoin - 1, i + 2 - startSuggestoin));
				else
					ans.append(s.substr(startSuggestoin , i + 1 - startSuggestoin));
				if (s[i] == '-')
					ans.pop_back();
			}
			startSuggestoin = i;
		}
	return !ans.empty() ? ans : "В файле нет таких предложений\n";
}

string readFile(ifstream& input) {
	string s = "";
	string tmpS;
	while (getline(input, tmpS))
		s.append(tmpS).append("\n");
	return s;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string filename;
	processInputNameOfInputFile(filename);
	ifstream input(filename);
	cout << "Результат работы:\n" << task(readFile(input));
	input.close();
}