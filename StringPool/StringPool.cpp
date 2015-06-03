#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class StringPool
{
private:
	unordered_map<int, string> Base;
public:
	StringPool()
	{};

	int GetId(const string& _word)
	{
		int ID = (int)hash<string>()(_word);
		Base[ID] = _word;
		return ID;
	}

	string GetWord(int id)
	{
		return Base[id];
	}
};


int main()
{
	StringPool Test;
	Test.GetId("kvala");
	Test.GetId("doom");
	Test.GetId("k");
	Test.GetId("do");
	Test.GetId("fffv");
	Test.GetId("fbfdgf");
	Test.GetId("dsdfd");
	Test.GetId("dosdcd");
	Test.GetId("kvfddfdf");
	Test.GetId("dfsf");

	cout << Test.GetWord(Test.GetId("dsdfd")) << endl;

	return 0;
}