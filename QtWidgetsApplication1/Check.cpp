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



// -----------------------------------------------------------------



QCheck::QCheck(Ui::QtWidgetsApplication1Class* ui, QWidget* page) {
	this->ui = ui;
	this->page = page;
}

int QCheck::check_all() {
	clear_error_message();
	
	for (auto check : error_checks) {
		if (!regex_match(check.LINE.toUtf8().constData(), result, check.RULE)) {
			return check.RETURN_NUM;
		}
	}

	return 1;
}

int QCheck::check_by_error_codes(vector<int> error_codes) {
	clear_error_message();
	
	for (auto check : error_checks) {
		if (!regex_match(check.LINE.toUtf8().constData(), result, check.RULE)) {
			if (find(error_codes.begin(), error_codes.end(), check.RETURN_NUM) != error_codes.end())
				return check.RETURN_NUM;
		}
	}

	return 1;
}

ErrorMessage QCheck::get_error_message_by_return_num(int return_num) {
	for (auto message : error_messages) {
		if (message.RETURN_NUM == return_num) {
			return message;
		}
	}
}

void QCheck::show_error_message(int return_num) {
	ErrorMessage message = get_error_message_by_return_num(return_num);
	show_error_message(message);
}

void QCheck::show_error_message(ErrorMessage error_message) {
	QLabel* label = new QLabel(error_message.MESSAGE, page);
	label->setGeometry(error_message.X, error_message.Y, error_message.WIDTH, error_message.HEIGHT);
	label->setStyleSheet(STYLE::COLOR::RED);
	label->setFont(FONTS::UBUNTU_12);
	label->setObjectName(ERROR_MESSAGE_NAME);
	label->show();
}
	
void QCheck::add_error_message(ErrorMessage error_message) {
	this->error_messages.push_back(error_message);
}

void QCheck::add_error_check(ErrorCheck error_check) {
	this->error_checks.push_back(error_check);
}

void QCheck::clear_error_message() {
	qDeleteAll(ui->editAccountPage->findChildren<QLabel*>(ERROR_MESSAGE_NAME));
}

void QCheck::clear_errors() {
	this->error_checks.clear();
	this->error_messages.clear();
}


