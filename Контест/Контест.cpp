#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;


bool Compare(pair <string, int> &a, pair<string, int> &b)
{
	return (a.second < b.second);
}

bool Compare_2(pair <int, int> &a, pair<int, int> &b)
{
	return (a.second > b.second);
}

class PriceOfTasks
{
private:
	vector<int> Base;

public:

	PriceOfTasks(int n)
	{
		Base.assign(n, 0);
	}
	int findPrice(int i) const
	{
		if (i <= Base.size())
			return Base[i - 1];
		else
			return 0;
	}

	int size() const
	{
		return Base.size();
	}

	friend istream& operator >> (istream& is, PriceOfTasks &a);
};

class StudentsRezults
{
private:
	map< string, vector<int> > StudentsBase;

public:

	void addRezult(const string &stud, int rez)
	{
		if (StudentsBase.find(stud) == StudentsBase.end())
			StudentsBase[stud].push_back(rez);
		else
		{
			int Parametr = 1;
			for (int i = 0; i < StudentsBase[stud].size(); i++)
				if (StudentsBase[stud][i] == rez)
					Parametr = 0;
			if (Parametr)
				StudentsBase[stud].push_back(rez);
		}

	}
	
	int showCountTasks(const string &stud)
	{
		if (StudentsBase.find(stud) == StudentsBase.end())
			return -1;
		else
			return StudentsBase[stud].size();
	}
	
	int pointsSumm(const string &stud, const PriceOfTasks &A)
	{
		if (StudentsBase.find(stud) == StudentsBase.end())
			return -1;
		else
		{
			int Sum = 0;
			for (int i = 0; i < StudentsBase[stud].size(); i++)
				Sum += A.findPrice(StudentsBase[stud][i]);

			return Sum;
		}
	}
	
	void showRezByTask(int n)
	{
		vector<pair<string, int>> Rez;
		pair<string, int> Help;
		map< string, vector<int> >::iterator cur;
		for (cur = StudentsBase.begin(); cur != StudentsBase.end(); cur++)
		{

			Help.first = (*cur).first;
			Help.second = (*cur).second.size();
			Rez.push_back(Help);
		}
		sort(Rez.begin(), Rez.end(), Compare);
		for (int i = 0; i < Rez.size(); i++)
			if (Rez[i].second >= n)
				cout << Rez[i].first << " " << Rez[i].second << endl;
	}
	
	void TaskPartyHard(const PriceOfTasks &A)
	{
		pair<int, int> Help;
		vector<pair<int, int>> Rez;
		for (int i = 0; i < A.size(); i++)
		{
			Help.first = i + 1;
			Help.second = 0;
			Rez.push_back(Help);
		}
		map< string, vector<int> >::iterator cur;
		for (cur = StudentsBase.begin(); cur != StudentsBase.end(); cur++)
		{
			for (int i = 0; i < (*cur).second.size(); i++)
			{
				//cout << (*cur).second.size() << " " << ((*cur).second)[i] << endl;
				Rez[((*cur).second)[i] - 1].second++;
			}
		}
		sort(Rez.begin(), Rez.end(), Compare_2);
		for (int i = 0; i < Rez.size(); i++)
		{			
			cout << Rez[i].first << " " << Rez[i].second << endl;
		}
			
	}

	void showRezByPoints(int n, const PriceOfTasks &A)
	{
		vector<pair<string, int>> Rez;
		pair<string, int> Help;
		map< string, vector<int> >::iterator cur;
		for (cur = StudentsBase.begin(); cur != StudentsBase.end(); cur++)
		{

			Help.first = (*cur).first;
			Help.second = this->pointsSumm((*cur).first, A);
			Rez.push_back(Help);
		}
		sort(Rez.begin(), Rez.end(), Compare);
		for (int i = 0; i < Rez.size(); i++)
			if (Rez[i].second >= n)
				cout << Rez[i].first << " " << Rez[i].second << endl;
	}
};

istream& operator >> (istream& is, PriceOfTasks &a)
{
	for (int i = 0; i < a.Base.size(); i++)
		is >> a.Base[i];
	return is;
}

void getCommand(PriceOfTasks &Razb, StudentsRezults &Catalog, string &adress)
{
	string comm, name;
	int number, summ;
	ifstream infile(adress);
	for (;;)
	{
		infile >> comm;
		if (comm == "EXIT") break;
		if (comm == "SOLVED")
		{
			infile >> name >> number;
			Catalog.addRezult(name, number);
			continue;
		}
		if (comm == "STUD_STAT")
		{
			infile >> name;
			int Count, Sum;
			Count = Catalog.showCountTasks(name);
			Sum = Catalog.pointsSumm(name, Razb);
			cout << ((Count == -1) ? 0 : Count) << " " << ((Sum == -1) ? 0 : Sum);
			cout << endl;
			continue;
		}
		if (comm == "STUDS_BY_TASKS")
		{
			Catalog.showRezByTask(0);
			continue;
		}
		if (comm == "STUDS_BY_BALLS")
		{
			Catalog.showRezByPoints(0, Razb);
			continue;
		}
		if (comm == "STUDS_MORE_TASKS")
		{
			infile >> number;
			Catalog.showRezByTask(number);
			continue;
		}
		if (comm == "STUDS_MORE_BALLS")
		{
			infile >> number;
			Catalog.showRezByPoints(number, Razb);
			continue;
		}
		if (comm == "TASKS_BY_SOLUTIONS")
		{
			Catalog.TaskPartyHard(Razb);
			continue;
		}
		cout << endl;
	}
}

int main()
{
	ifstream infile("Points.txt");
	int n;
	infile >> n;
	PriceOfTasks A(n);
	infile >> A;
	StudentsRezults Basa;
	string adress = ("Contest.txt");
	getCommand(A, Basa, adress);
	return 0;
}