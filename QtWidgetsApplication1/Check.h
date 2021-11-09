#pragma once
#include <QString>
#include "regex"

using namespace std;

class Check
{
public:
//	Check();

	static bool is_math(QString line, QString rule);
	static bool is_empty(vector<QString> lines);

private:
	cmatch result;
	vector<regex> rules;
	vector<QString> lines;

};

