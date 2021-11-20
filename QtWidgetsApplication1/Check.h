#pragma once
#include "ui_QtWidgetsApplication1.h"
#include <QtWidgets/QMainWindow>
#include <QString>
#include "constants.h"
#include "regex"

using namespace std;

struct ErrorMessage 
{
	const int RETURN_NUM;
	const QString MESSAGE;
	const int X;
	const int Y;
	const int WIDTH;
	const int HEIGHT;

	ErrorMessage(int return_num, QString message, int x, int y, int width, int height) 
		: RETURN_NUM(return_num), MESSAGE(message), X(x), Y(y), WIDTH(width), HEIGHT(height) {	}
};


struct ErrorCheck 
{
	const QString LINE;
	const regex RULE;
	const int RETURN_NUM;

	ErrorCheck(int return_num, QString line, regex rule) 
		: LINE(line), RETURN_NUM(return_num), RULE(rule) { 	}
};

class QCheck {
public:
	QCheck(Ui::QtWidgetsApplication1Class* ui, QWidget* page);

	int check_all();
	int check_by_error_codes(vector<int> error_codes);
	void show_error_message(ErrorMessage error_message);
	void show_error_message(int return_num);
	ErrorMessage get_error_message_by_return_num(int return_num);

	void add_error_message(ErrorMessage error_message);
	void add_error_check(ErrorCheck error_check);
	
	void clear_errors();
	void clear_message_list();
	void clear_check_list();
	void clear_error_message();

	static bool is_empty(vector<QString> lines);

private:
	const QString ERROR_MESSAGE_NAME = "error_message";
	Ui::QtWidgetsApplication1Class* ui;
	QLabel* error_label;
	cmatch result;
	QWidget* page;
	
	vector<ErrorMessage> error_messages;
	vector<ErrorCheck> error_checks;
};

