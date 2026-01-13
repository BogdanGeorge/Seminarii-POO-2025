#include<iostream>
#include<vector>
#include<list>
#include<deque>
#include<map>
#include<queue>
#include<stack>

using namespace std;

int main()
{
	cout << endl << "STL ---- VECTOR" << endl;


	vector<int> v1;

	v1.push_back(1);

	cout << v1.capacity() << " " << v1.size() << endl;
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	v1.push_back(6);
	cout << v1.capacity() << " " << v1.size() << endl;

	v1.push_back(7);
	cout << v1.capacity() << " " << v1.size() << endl;


	v1.pop_back();

	cout << v1.capacity() << " " << v1.size() << endl;

	v1.insert(v1.begin() + 2, 100);


	for (int i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << " ";
	}

	cout << endl << "STL ---- LIST" << endl;

	list<int> l1;

	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);

	l1.push_front(0);


	auto l1Iterator = l1.begin();
	l1Iterator++;
	l1.insert(l1Iterator, 100);


	l1.pop_back();
	l1.pop_front();

	for (auto it = l1.begin(); it != l1.end(); it++)
	{
		cout << *it << " ";
	}

	cout << endl << "STL ---- DEQUE" << endl;

	deque<int> d1;

	d1.push_back(1);
	d1.push_back(2);
	d1.push_back(3);

	d1.push_front(0);

	d1.insert(d1.begin() + 1, 100);

	d1.pop_back();
	d1.pop_front();

	for (int i = 0; i < d1.size(); i++)
	{
		cout << d1[i] << " ";
	}

	map<string, int> catalog;

	catalog.insert(pair<string, int>("Vasile", 10));
	catalog.insert(pair<string, int>("Ana", 9));
	catalog.insert(pair<string, int>("Robert", 8));

	catalog.insert(pair<string, int>("Ana", 4));
	catalog["Ana"] = 3;

	for (auto it = catalog.begin(); it != catalog.end(); it++)
	{
		cout << it->first << " " << it->second << endl;
	}


	cout << endl << "STL ---- QUEUE" << endl;
	queue<int> q1; // FIFO

	q1.push(1);
	q1.push(2);
	q1.push(3);
	q1.push(4);

	while (!q1.empty())
	{
		cout << q1.front() << endl;

		q1.pop();
	}

	cout << endl << "STL ---- STACK" << endl;


	stack<int> s1;

	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.push(4);

	while (!s1.empty())
	{
		cout << s1.top() << endl;

		s1.pop();
	}

	return 0;
}