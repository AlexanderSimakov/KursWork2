#include "Check.h"



bool Check::is_math(QString line, QString rule) {
	regex _rule(rule.toUtf8().constData());
	cmatch result;

	return regex_match(line.toUtf8().constData(), result, _rule);
}

bool Check::is_empty(vector<QString> lines) {
	bool _is_empty;

	for (QString line : lines) {
		if (line == "") return true;
	}

	return false;
}

