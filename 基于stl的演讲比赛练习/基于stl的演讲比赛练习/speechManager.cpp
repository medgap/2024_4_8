#define _CRT_SECURE_NO_WARNINGS
#include"speechManager.h"

void speakerManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->map_Person.clear();
	this->index = 1;
	this->m_Record.clear();
	
}

speakerManager::speakerManager() {
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
}

speakerManager::~speakerManager() {

}

void speakerManager::showMenu() {
	cout << "---------- 1.��ʼ�ݽ����� -----------" << endl;
	cout << "---------- 2.�鿴�����¼ -----------" << endl;
	cout << "---------- 3.��ձ�����¼ -----------" << endl;
	cout << "---------- 0.�˳��������� -----------" << endl;
	cout << endl;

}

void speakerManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void speakerManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "ѡ��";
		name += nameSeed[i];
		Person p;
		p.name = name;
		for (int j = 0; j < 2; j++) {
			p.score[j] = 0;
		}
		this->v1.push_back(i + 10001);
		this->map_Person.insert(make_pair(i + 10001, p));
	}
}

void speakerManager::shuffle() {
	cout << "��" << this->index << "�γ�ǩ��ʼ" << endl;
	cout << "��ǩ���ݽ�˳������ : " << endl;
	if (this->index == 1) {
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "---------------------" << endl;
	system("pause");
	cout << endl;
}

void speakerManager::speechContest() {
	cout << "-------- ��" << this->index << " �ֱ�����ʽ��ʼ ------------" << endl;
	int num = 0;
	vector<int> src;
	multimap<double, int, greater<double>> temp;
	if (this->index == 1)
		src = v1;
	else
		src = v2;
	for (vector<int>::iterator it = src.begin(); it != src.end(); it++) {
		num++;
		deque<double> d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();
		d.pop_front();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		this->map_Person[*it].score[this->index - 1] = avg;
		temp.insert(make_pair(avg, *it));

		if (num % 6 == 0) {
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator itt = temp.begin(); itt != temp.end(); itt++) {
				cout << "���: " << itt->second << "����: " << this->map_Person[itt->second].name << "�ɼ�: " << this->map_Person[itt->second].score[this->index - 1] << endl;
			}

			int count = 0;
			for (multimap<double, int, greater<double>>::iterator itt = temp.begin(); itt != temp.end() && count < 3; itt++,count++) {
				if (this->index == 1) {
					v2.push_back(itt->second);
				}
				else {
					vVictory.push_back(itt->second);
				}
			}
			temp.clear();
			cout << endl;
		}
		
	}
	cout << "------------- ��" << this->index << "�ֱ������  ------------- " << endl;
	system("pause");
}

void speakerManager::showScore() {
	vector<int> v;
	if (this->index == 1)
		v = v2;
	else
		v = vVictory;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "���: " << *it << "����: " << this->map_Person[*it].name << "�ɼ�: " << this->map_Person[*it].score[this->index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	//this->showMenu();
}

void speakerManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << map_Person[*it].score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "��¼�Ѿ�����" << endl;
	this->fileIsEmpty = false;
}

void speakerManager::startSpeech() {
	this->shuffle();
	this->speechContest();
	this->showScore();

	this->index++;

	this->shuffle();
	this->speechContest();
	this->showScore();

	this->saveRecord();

	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();

	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
}

void speakerManager::loadRecord() {
	//��ȡ����
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {
		//cout << "�ı�������" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "�ı�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;
	ifs.putback(ch);
	string data;
	int index = 0; //����ڼ������
	while (ifs >> data) {
		vector<string> v;
		int pos = -1;
		int start = 0;
		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

void speakerManager::showRecord() {
	if (!this->fileIsEmpty) {
		for (int i = 0; i < m_Record.size(); i++) {
			cout << "�� " << i + 1 << " �����: " << "�ھ���� : " << this->m_Record[i][0] << " �ھ��ɼ� : "
				<< this->m_Record[i][1] << "  �Ǿ���� : " << this->m_Record[i][2] << " �Ǿ��ɼ� : " << this->m_Record[i][3]
				<< " ������� : " << this->m_Record[i][4] << " �����ɼ� : " << this->m_Record[i][5] << endl;
		}
		system("pause");
		system("cls");
	}
	else {
		cout << "�ļ������ڻ�Ϊ�� " << endl;
	}
	system("pause");
	system("cls");
}

void speakerManager::clearRecord() {
	cout << "------- 1. r u sure >? -------" << endl;
	cout << "------- 2. no          -------" << endl;
	int choice;
	cin >> choice;
	if (choice == 1) {
		ofstream ofs;
		ofs.open("speech.csv", ios::trunc);
		ofs.close();

		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();

		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}