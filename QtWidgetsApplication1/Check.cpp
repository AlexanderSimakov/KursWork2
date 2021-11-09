#include "Check.h"

Check::Check(vector<Check_line> lines) {
	this->lines = lines;
}

int Check::check_all() {
	for (Check_line line : lines) {
		if (!is_math(line.line, line.rule)) {
			return line.return_num;
		}
	}
	return 1;
}

bool Check::is_math(QString line, QString rule) {
	regex _rule(rule.toUtf8().constData());
	cmatch result;

	return regex_match(line.toUtf8().constData(), result, _rule);
}

bool Check::is_math(QString line, regex rule) {
	cmatch result;
	return regex_match(line.toUtf8().constData(), result, rule);
}


bool Check::is_empty(vector<QString> lines) {
	bool _is_empty;

	for (QString line : lines) {
		if (line == "") return true;
	}

	return false;
}

