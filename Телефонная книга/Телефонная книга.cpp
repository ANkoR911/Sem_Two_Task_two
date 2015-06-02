#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

class PersonalBase
{
private:
	string Email;
	vector<string> PersNumbers;

public:
	PersonalBase() : Email("Unknown")
	{};

	void addEmail(const string &_email)
	{
		Email = _email;
	}

	int findInBase(const string &_number) const
	{
		int Parametr = -1;
		for (int i = 0; i < PersNumbers.size(); i++)
			if (PersNumbers[i] == _number)
				Parametr = i;
		return Parametr;
	}

	int sizeBase() const
	{
		return PersNumbers.size();
	}

	void addNumber(const string &_number)
	{
		int Parametr = this->findInBase(_number);
		if (Parametr == -1)
			PersNumbers.push_back(_number);
	}

	void deleteNumber(const string &_number)
	{
		int del = this->findInBase(_number);
		int siz = this->sizeBase();
		PersNumbers[del].swap(PersNumbers[siz - 1]);
		PersNumbers.pop_back();
	}

	string ShowEmail() const
	{
		return Email;
	}

	void printAllNumbers() const
	{
		for (int i = 0; i < PersNumbers.size(); i++)
			cout << "PhoneNumber " << (i + 1) << " - " << PersNumbers[i] << endl;
	}

	void printNumber(int i) const
	{
		if (i < PersNumbers.size())
			cout << "PhoneNumber " << (i + 1) << " - " << PersNumbers[i];
	}

	void printEmail() const
	{

		cout << "Email: " << Email;
	}


};

class PhoneBase
{
private:
	map <string, PersonalBase> Base;

public:
	void addPhone(const string &Name, const string &p_number)
	{
		Base[Name].addNumber(p_number);
	}

	void addEmail(const string &Name, const string &p_email)
	{
		Base[Name].addEmail(p_email);
	}

	void deletePerson(const string &Name)
	{
		if (Base.find(Name) != Base.end())
			Base.erase(Base.find(Name));
	}

	void deleteNumber(const string &Name, const string &number)
	{
		if (Base.find(Name) != Base.end())
			Base[Name].deleteNumber(number);
	}

	void printNumbers(const string &Name)
	{
		if (Base.find(Name) != Base.end())
			(Base[Name]).printAllNumbers();
	}

	void printEmail(const string &Name)
	{
		if (Base.find(Name) != Base.end())
			Base[Name].printEmail();
	}

	void printAllPhoneBase()
	{
		int i, siz;
		map<string, PersonalBase>::iterator cur;
		for (cur = Base.begin(); cur != Base.end(); cur++)
		{
			if (((*cur).second.ShowEmail()) != "Unknown")
			{
				cout << (*cur).first << " ";
				(*cur).second.printEmail();
				cout << endl;
			}

			siz = (*cur).second.sizeBase();
			for (i = 0; i < siz; i++)
			{
				cout << (*cur).first << " ";
				(*cur).second.printNumber(i);
				cout << endl;
			}
		}
	}

	void findName(const string &number)
	{
		map<string, PersonalBase>::iterator cur;
		for (cur = Base.begin(); cur != Base.end(); cur++)
		{
			if ((*cur).second.findInBase(number) != -1)
				cout << (*cur).first;
		}
		cout << endl;
	}
};

int main()
{
	PhoneBase Test;
	Test.addPhone("Vasilii", "+789456");
	Test.addPhone("Nicolia", "165166651");
	Test.addPhone("Kostia", "4111561");
	Test.addPhone("Vasilii", "+45");
	Test.addPhone("Nicolia", "1651525");
	Test.addPhone("Kostia", "532542");
	Test.addPhone("Nicolia", "165166651");
	Test.addPhone("Kostia", "41113655356353");
	Test.addPhone("Kostia", "4");
	Test.addEmail("Nicolia", "krachmaliev-rediska@mail.ru");
	Test.printEmail("Nicolia");
	cout << endl;
	Test.printEmail("Jule");
	cout << endl;
	Test.deleteNumber("Kostia", "41113655356353");
	Test.deletePerson("Nicolia");
	Test.printAllPhoneBase();

	return 0;
}
