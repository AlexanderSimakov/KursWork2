#pragma once
#include "ui_QtWidgetsApplication1.h"
#include <QtWidgets/QMainWindow>
#include <QString>
#include "constants.h"
#include "regex"

using namespace std;

struct ErrorMessage // структура, содержаща€ все необходимое дл€ вывода сообщени€ об ошибке на экран
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


struct ErrorCheck // структура содержаща€ проверку через регул€рные выражени€
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

	int check_all(); // проверка всего
	int check_by_error_codes(vector<int> error_codes); // проверка по заданному коду ошибки
	void show_error_message(ErrorMessage error_message); // вывод ошибки на экран по структуре
	void show_error_message(int return_num); // вывод ошибки на экран по коду
	ErrorMessage get_error_message_by_return_num(int return_num); // возвращает структуру ErrorMessage  по коду ошибки

	void add_error_message(ErrorMessage error_message); // добавлени€ структуры сообщени€ об ошибке
	void add_error_check(ErrorCheck error_check); // добавлени€ проверки через регул€рные выражени€
	
	void clear_errors(); // очистка векторов содержащих сообщени€ и проверки
	void clear_message_list(); // очистка вектора сообщений об ошибках
	void clear_check_list(); // очистка вектора содержащего проверки
	void clear_error_message(); // очистка выведенного на экран сообщени€ об ошибке

	static bool is_empty(vector<QString> lines); // возвращает true, если хот€ бы один из Qstring обьектов ничего не содержит

private:
	const QString ERROR_MESSAGE_NAME = "error_message";
	Ui::QtWidgetsApplication1Class* ui;
	QLabel* error_label;
	cmatch result;
	QWidget* page;
	
	vector<ErrorMessage> error_messages;
	vector<ErrorCheck> error_checks;
};

