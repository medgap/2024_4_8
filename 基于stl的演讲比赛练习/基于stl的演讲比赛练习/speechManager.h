#pragma once
#include<iostream>
#include<vector>
#include<deque>
#include<map>
#include<numeric>
#include<functional>
#include<string>
#include<algorithm>
#include"Person.h"
#include<fstream>

using namespace std;

class speakerManager {
public:
	speakerManager();
	
	void initSpeech();

	void showMenu();

	void speechContest();

	void startSpeech();

	void exitSystem();

	void createSpeaker();

	void shuffle();

	void showScore();

	void saveRecord();

	void loadRecord();

	void showRecord();

	void clearRecord();

	~speakerManager();

	vector<int> v1;
	vector<int> v2;
	vector<int> vVictory;
	map<int, Person> map_Person;
	int index;
	bool fileIsEmpty;
	map<int, vector<string>> m_Record;
};