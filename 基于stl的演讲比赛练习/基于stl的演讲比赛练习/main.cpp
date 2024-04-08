#define _CRT_SECURE_NO_WARNINGS
#include"Person.h"
#include"speechManager.h"
#include<ctime>

int main() {
	srand((unsigned int)time(NULL));
	speakerManager sm;
	int choice;

	while (true) {
		sm.showMenu();
		cout << "ÇëÊäÈëÑ¡Ôñ : " << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 0:
			sm.exitSystem();
			break;
		default:
			break;
		}
	}
	

	system("pause");
	return 0;
}