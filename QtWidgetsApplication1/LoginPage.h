#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include "SQLWORK.h"
#include "SQLWORK.h"
#include "Account.h"
#include "constants.h"
#include <string>
#include "Check.h"

namespace LOGINERROR {
	const int IS_EMPTY = 0;
	const int NO_ACCESS = -1;
	const int WRONG_INPUT = -2;
}

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
	QCheck* check;

	bool is_account_have_access(QString login);
	QString get_login();
	QString get_password();

	void init_check_message();
	void adjust_fonts();
};

