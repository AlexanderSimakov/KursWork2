#pragma once
#include <QString>
#include "regex"

using namespace std;

struct Check_line {
	QString line;
	regex rule;
	int return_num = 0;

	Check_line(QString line, int return_num, regex rule) {
		this->line = line;
		this->rule = rule;
		this->return_num = return_num;
	}

	Check_line(QString line, int return_num, QString rule) {
		this->line = line;
		this->rule = rule.toUtf8().constData();
		this->return_num = return_num;
	}

	
};


class Check
{
public:
	Check(vector<Check_line> lines);

	int check_all();

	static bool is_math(QString line, regex rule);
	static bool is_math(QString line, QString rule);
	static bool is_empty(vector<QString> lines);

private:
	vector<Check_line> lines;
	cmatch result;


};

