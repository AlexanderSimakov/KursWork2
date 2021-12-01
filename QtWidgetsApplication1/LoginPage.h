#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include "SQLWORK.h"
#include "SQLWORK.h"
#include "Account.h"
#include "constants.h"
#include <string>
#include "Check.h"

namespace LOGIN_ERROR 
{
	const int IS_EMPTY = 0;
	const int NO_ACCESS = -1;
	const int WRONG_INPUT = -2;
}

class LoginPage : QMainWindow
{
	Q_OBJECT
public:
	LoginPage(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, SQLWork* account_db);
	void open(); // открытие страницы авторизации
	void clear_error_message(); // очистка сообщений об ошибке
	void clear_password_input(); // очистка поля ввода пароля
	void clear_login_input(); // очистка поля ввода логина
	Account get_authorized_account(); // возвращенает авторизированный аккаунт

private:
	Ui::QtWidgetsApplication1Class* ui;
	QWidget* page;
	SQLWork* account_db;
	QCheck* check;

	bool is_account_have_access(QString login); // возвращает true, если аккаунт подтвержден
	QString get_login(); // возвращает логин
	QString get_password(); // возвращает пароль

	void init_check_message(); // инициализация сообщений об ошибках
	void adjust_fonts(); // настройка стиля шрифтов страницы
};

