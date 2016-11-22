#pragma once
#include<iostream>
#include<fstream>
#include<conio.h>
#include<cstdlib>
#include<time.h> 
#include<string.h>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::cin;

namespace Scaactk {
	int Check_ID(int);
	int Get_Passwords();
	int Compare(int, int);
	int Check_Mon(double);
	//int Append_User(User&);
	int Get_ID();
	//int Get_Info();
	void Print_Record(string);
	//void Record(string);
	string Int_To_String(int);
	string Get_time();
	
	string getInfo(string _fileName, string _id);
	int splitString(char dst[][10], char* str, const char* spl);
	double charToDbl(char *p);
	int Time_show();
}

int Scaactk::Check_ID(int id) {
	string _name;
	int _id;
	int _pw;
	double _Mon;
	int _statue;

	ifstream infile("sql.txt", std::ios::in);
	if(infile.fail()) {
		std::cerr << "FAIL_TO_OPEN" << endl;
		return false;
	}
	while (infile) {
		infile >> _name >> _id >> _pw >> _Mon >> _statue;//���ж�ȡ

		if (_id == id) {
			cerr << "This ID has been used!" << endl;
			infile.close();
			return false;
		}
	}
	cout << "This ID can be used!" << endl;
	infile.close();
	return true;
}

int Scaactk::Get_Passwords() {
	char pin[7];
	int temp = 0;
	for (int i = 0; i < 6; i++) {
		pin[i] = _getch();
		cout << "*";
		temp *= 10;
		temp += pin[i] - '0';
	}
	_getch();
	return temp;//����֮ǰ�����pw
}

int Scaactk::Compare(int t1, int t2) {
	if (t1 == t2) {
		return true;
	}
	else {
		return false;
	}
}

int Scaactk::Check_Mon(double m) {
	if (m < 0) {
		cerr << "Eroor Number!" << endl;
		return false;
	}
	else {
		return true;
	}
}
 
int Scaactk::Get_ID() {
	int _inid;
	cout << "Please input ID:" << endl;
	cin >> _inid;
	return _inid;
}

void Scaactk::Print_Record(string id) {
	ifstream record(id.c_str(), std::ios::in);
	//�����fstream ��������벻���Ĵ����Ʋ��ǻ���ͬʱ���ʺͶ�д�ĳ�ͻ
	string line;
	while (!record.eof()) {
		getline(record, line);
		std::cout << line << endl;
	}
	record.close();
}

string Scaactk::Int_To_String(int id) {
	char temp[100];
	itoa(id, temp, 10);
	return (string)temp;
}

string Scaactk::Get_time() {
	time_t t;
	tm* local;
	char buf[128];
	t = time(NULL);
	
	local = localtime(&t);
	strftime(buf, 64, "%Y_%m_%d %H:%M:%S", local);//��ʽ����ʱ
	return (string)buf;
} 

/*           һ���ֽ�������          */

string Scaactk::getInfo(string _fileName, string _id) {
	//	string temp;
	//	FILE *fp;
	//	ifstream infile(_fileName.c_str());
	//	while (getline(infile, temp));
	//	return temp;//���ַ�������ʽ�����ļ��е�ȫ������
	char temp[100];
	ifstream infile;
	string sp_id;
	string sp_pw;
	string sp_mon;
	infile.open(_fileName.c_str(), std::ios::in);
	if (!infile.fail()) {
		while (infile.getline(temp, 100, '\n')) {
			string temp1 = temp;
			char dst[5][10];//ÿ�еĲ�����������ݣ�ÿ�����Ȳ�����10
			int count = Scaactk::splitString(dst, temp, ",");
			sp_id = dst[0];//���ָ����idת����string
			if (_id == sp_id) {
				//std::cout << temp1;
				//std::cout << dst[0];
				//std::cout << dst[1];
				infile.close();
				return temp1;
			}
		}
		infile.close();
		std::cerr << "NOT_FOUND_ID";
		return "NOT_FOUND_ID";
	}
	else {
		infile.close();
		std::cerr << "FAIE_TO_OPEN";
		return "FAIE_TO_OPEN";
	}
}

int Scaactk::splitString(char dst[][10], char* str, const char* spl) {
	int n = 0;//�ָ��ַ����������Ϊ�ָ�����һ�е�char[]��
	//char *buf;
	char* result = NULL;
	result = strtok(str,spl);
	while (result != NULL) {
		strcpy(dst[n++], result);
		result = strtok(NULL, spl);
	}
	return n;
}


//����С������ַ���ת��Ϊdouble
//�������ʹ��sstreamֱ��ת��
//����дһ��������
double Scaactk::charToDbl(char* src) {
	char *p = src;//���þֲ������Ǹ��ܺõ�ϰ��
	double temp = 0;

	while (*p != '\0'&&*p != '.') {
		temp *= 10;
		temp += (*p) - '0';//���ַ�ת��Ϊ����
		p++;
	}

	if (*p == '.') {
		double step = 0.1;
		p++;//����С����
		while (*p != '\0') {
			temp += step*((*p) - '0');
			step /= 10;
			p++;
		}
	}
	return temp;
}

int Scaactk::Time_show() {
	string num[11] = { "0","һ","��","��","��","��","��","��","��","��","ʮ" };

	time_t t = time(0);
	char tyear[5];
	char tm[3];
	char td[3];
	char tH[3];
	char tM[3];

	char tAll[1024];//�����㹻��Ŀռ� �洢���������ʽ

	//������localtime���ø��ˣ����ֻ��dev�汾�������

	strftime(tAll, sizeof(tAll), "%Y %x %A %X \t", localtime(&t));

	puts(tAll);

	strftime(tyear, sizeof(tyear), "%Y", localtime(&t));
	strftime(tm, sizeof(tm), "%m", localtime(&t));
	strftime(td, sizeof(td), "%d", localtime(&t));
	strftime(tH, sizeof(tH), "%H", localtime(&t));
	strftime(tM, sizeof(tM), "%M", localtime(&t));

	string result = "";

	// ��ʽ�� ��
	int year = 0;
	year = atoi(tyear);
	int y[4];

	y[0] = year / 1000;
	year %= 1000;
	y[1] = year / 100;
	year %= 100;
	y[2] = year / 10;
	year %= 10;
	y[3] = year / 1;
	result = num[y[0]] + num[y[1]] + num[y[2]] + num[y[3]] + "��";

	// ��ʽ�� ��
	int month = atoi(tm);
	int m[2];
	m[0] = month / 10;
	m[1] = month % 10;
	if (m[0] != 0)
	{
		result += num[m[0]];
		if (m[1] == 0)
		{
			result += num[10];
		}
		else
		{
			result += num[m[1]];
		}
	}
	else
	{
		result += num[m[1]];
	}
	result += "��";

	// ��ʽ�� ��
	int day = atoi(td);
	int d[2];
	d[0] = day / 10;
	d[1] = day % 10;
	if (d[0] != 0)
	{
		result += num[d[0]];
		if (d[1] == 0)
		{
			result += num[10];
		}
		else
		{
			result += num[d[1]];
		}
	}
	else
	{
		result += num[d[1]];
	}
	result += "��	";

	// ��ʽ�� ʱ
	int hour = atoi(tH);
	int H[2];
	H[0] = hour / 10;
	H[1] = hour % 10;
	if (H[0] != 0)
	{
		result += num[H[0]];
		if (d[1] == 0)
		{
			result += num[10];
		}
		else
		{
			result += "ʮ" + num[H[1]];
		}
	}
	else
	{
		result += num[H[1]];
	}


	// ��ʽ�� ��
	int min = atoi(tM);

	if (min == 0)
	{
		result += "��";
	}
	else
	{
		result += "ʱ";
		int M[2];

		M[0] = hour / 10;
		M[1] = hour % 10;
		if (M[0] != 0)
		{
			result += num[M[0]];
			if (d[1] == 0)
			{
				result += num[10];
			}
			else
			{
				result += "ʮ" + num[M[1]];
			}
		}
		else
		{
			result += num[M[1]];
		}
	}

	result += "��";

	cout << result << endl;

	return 0;
}

