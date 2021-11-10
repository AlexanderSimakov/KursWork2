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

QCheck::QCheck(Ui::QtWidgetsApplication1Class* ui, QWidget* page) {
	this->ui = ui;
	this->page = page;
}

void QCheck::show_error_message(QString text, const int X, const int Y, const int WIDTH, const int HEIGHT) {
	error_label = new QLabel(text, page);
	error_label->setObjectName(ERROR_MESSAGE_NAME);
	error_label->setStyleSheet(STYLE::COLOR::RED);
	error_label->setFont(FONTS::UBUNTU_12);
	error_label->setGeometry(X, Y, WIDTH, HEIGHT);
	error_label->show();
}

void QCheck::clear_error_message() {
	qDeleteAll(ui->editAccountPage->findChildren<QLabel*>(ERROR_MESSAGE_NAME));
}




