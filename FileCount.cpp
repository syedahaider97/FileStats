#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void display(int lineCount, int wordCount, int charCount, string fileName);
void display(int lineCount, int caseCount, string fileName);
void wordCounter(char* file, string search);
void characterCounter(char* file, char search);
void Stats(istream &stream, string file);

int totalLines = 0;
int totalWords = 0;
int totalChars = 0;

int totalSingleLines = 0;
int totalSingleWords = 0;
int totalSingleChars = 0;

int totalWordLines = 0;
int totalWordWords = 0;

int main(int argc, char *argv[]) {

	vector<char*> files;
	vector<char> searchChars;
	vector<string> searchStrings;

	string fileName;

	string findChar = "-findchar";
	string findWord = "-findword";

	bool fail;

	if (argc == 1) {
		Stats(cin, "");
	}

	for (int i = argc - 1; i >= 1; i--) {
		fail = false;
		fileName = argv[i];
		ifstream file(argv[i]);
		if (file.is_open()) {
			files.push_back(argv[i]);
		} else if (fileName.substr(0, 9) == findChar) {
			if (fileName.at(fileName.length() - 2) != '=') {
				fail = true;
				break;
			}
			char searchChar = fileName.at(fileName.length() - 1);
			if (!(find(searchChars.begin(), searchChars.end(), searchChar)
					!= searchChars.end()))
				searchChars.push_back(searchChar);
		} else if (fileName.substr(0, 9) == findWord) {
			string searchWord;
			int pos = fileName.find('=');
			if (pos == -1) {
				fail = true;
				break;
			} else
				searchWord = fileName.substr(pos + 1);
			if (searchWord == "") {
				fail = true;
				break;
			}
			if (!(find(searchStrings.begin(), searchStrings.end(), searchWord)
					!= searchStrings.end()))
				searchStrings.push_back(searchWord);
		} else {
			if (fileName[0] == '-') {
				cout << "Argument " << fileName << " is not recognized" << endl;
			} else {
				cout << "File " << fileName << " is not found" << endl;
			}
			return 1;
		}
	}
	if (fail) {
		cout << "Argument " << fileName << " is poorly formed" << endl;
		return 1;
	}

	for (int i = files.size() - 1; i >= 0; i--) {
		ifstream myfile;
		myfile.open(files[i]);
		Stats(myfile, files[i]);
	}
	if (files.size() > 1) {
		display(totalLines, totalWords, totalChars, "totals");
	}

	sort(searchChars.begin(), searchChars.end());
	for (int i = 0; i < searchChars.size(); i++) {
		for (int j = files.size() - 1; j >= 0; j--) {
			characterCounter(files[j], searchChars[i]);
		}
		if (files.size() > 1) {
			cout << searchChars[i] << ":";
			display(totalSingleLines, totalSingleWords, totalSingleChars,
					"totals");
		}
		totalSingleLines = totalSingleWords = totalSingleChars = 0;
	}
	sort(searchStrings.begin(), searchStrings.end());
	for (int i = 0; i < searchStrings.size(); i++) {
		for (int j = files.size() - 1; j >= 0; j--) {
			wordCounter(files[j], searchStrings[i]);
		}
		if (files.size() > 1) {
			cout << searchStrings[i] << ":";
			display(totalWordLines, totalWordWords, "totals");
		}
		totalWordLines = totalWordWords = totalChars = 0;
	}

}

void display(int lineCount, int wordCount, int charCount, string fileName) {
	cout << setw(12) << lineCount << setw(12) << wordCount << setw(12)
			<< charCount << " " << fileName << endl;
}
void display(int lineCount, int caseCount, string fileName) {
	cout << setw(12) << lineCount << setw(12) << caseCount << " " << fileName
			<< endl;
}

void Stats(istream &stream, string file) {

	string line;

	int lineCount = 0;
	int wordCount = 0;
	int charCount = 0;
	char c;

	while (stream.get(c)) {
		line += c;
		charCount++;
		if (isspace(c) && line.length() != 1)
			wordCount++;

		if (c == '\n') {
			lineCount++;
			line = "";
		}
	}
	if (line.length() > 1 && line.at(line.length() - 1) != '\n')
		wordCount++;

	display(lineCount, wordCount, charCount, file);

	totalLines += lineCount;
	totalWords += wordCount;
	totalChars += charCount;
}

void characterCounter(char* file, char search) {

	int lines = 0;
	int words = 0;
	int chars = 0;
	ifstream myfile;
	myfile.open(file);
	string line;

	while (getline(myfile, line)) {
		int temp = 0;
		string word;
		line += '\n';
		for (int i = 0; i < line.length(); i++) {
			if (line[i] == search)
				temp += 1;
			word += line[i];
			if (isspace(line[i])) {
				if (word.find(search) != -1)
					words += 1;
				word = "";
			}
		}
		if (temp > 0)
			lines += 1;
		chars += temp;
	}
	cout << search << ":";
	display(lines, words, chars, file);

	totalSingleLines += lines;
	totalSingleWords += words;
	totalSingleChars += chars;
}

void wordCounter(char* file, string search) {

	int linecount = 0;
	int wordcount = 0;
	ifstream myfile;
	myfile.open(file);
	string line;

	while (getline(myfile, line)) {
		string word;
		int temp = 0;
		for (int i = 0; i < line.size(); i++) {

			if (isspace(line[i])) {
				if (word == search)
					temp += 1;
				word = "";
				continue;
			}
			word += line[i];
		}
		if (temp > 0) {
			linecount += 1;
		}
		wordcount += temp;
	}
	cout << search << ":";
	display(linecount, wordcount, file);

	totalWordLines += linecount;
	totalWordWords += wordcount;
}
