#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include "SQLWORK.h"
#include "SQLWORK.h"
#include "Account.h"
#include <string>

class LoginPage : QMainWindow
{
	Q_OBJECT
public:
	LoginPage(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, SQLWork* account_db);
	void open();
	void clear_error_message();
	void clear_password_input();
	void clear_login_input();
	Account get_authorized_account();


private:
	Ui::QtWidgetsApplication1Class* ui;
	QWidget* page;
	SQLWork* account_db;
	QLabel* error_message;

	const int PAGE_WIDTH;
	const int PAGE_HEIGHT;

	void init_error_message();
	void adjust_fonts();

	bool is_account_have_access(string login);
	string get_login();
	string get_password();
	void show_error_message(string text);

};

