#pragma once
#include <QtWidgets/QMainWindow>
#include <regex>
#include "ui_QtWidgetsApplication1.h"
#include "ChoisePageButtons.h"
#include "SQLWORK.h"
#include "Page.h"
#include "Account.h"
#include "constants.h"
#include "Check.h"

namespace ACCOUNT_ERROR 
{
	const int ALL_GOOD = 1;
	const int IS_EMPTY = 0;
	const int WRONG_NAME = -1;
	const int WRONG_LOGIN = -2;
	const int LOGIN_EXIST = -3;
	const int WRONG_PASSWORD = -4;
	const int PASSWORDS_NOT_SAME = -5;
}


class AccountPage : public QMainWindow, public Page
{
	Q_OBJECT
public:
	AccountPage(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, SQLWork* account_db);

	void start(); // запуск страницы аккаунтов
	virtual void update_window(); // обновление экрана

	void open_edit_account_page(Account account, const bool IS_REMOVABLE = true, const bool IS_STATUS_EDITABLE = true, const bool IS_BACK_TO_ACCOUNTS = true); // открытие страницы редактирования аккаунта
	void set_current_account(Account* current_account); // установка аккаунта из которого был произведен вход

private:
	Ui::QtWidgetsApplication1Class* ui;
	QWidget* parent;
	QWidget* page;
	SQLWork* account_db;

	const int NUMBER_OF_ACCOUNTS_ON_PAGE = 24;
	int current_page = 0;

	QPixmap admin_pixmap;
	QPixmap user_pixmap;
	QCheck* _check;
	Account* current_account;
	vector<int> accounts_id;

	void update_accounts_id(); // обновление вектора id аккаунтов

	void clear_page(); // очистка страницы
	void clear_account_list(); // очистка выведенных на экран аккаунтов
	void clear_account_edit_page(); // очистка страницы редактирования аккаунта

	void show_list(); // вывод списка аккаунтов на экран
	void show_account(Account* account, const int ROW, const int COLUMN); // вывод отдельного аккаунта

	QLabel* get_name_label(const QString NAME); // инициализирует и возвращает виджет, содержащий имя
	QLabel* get_login_label(const QString LOGIN); // инициализирует и возвращает виджет, содержащий логин
	QLabel* get_image_label(const int ROLE, const int ACCESS); // инициализирует и возвращает виджет, содержащий изображение

	void create_choise_page_buttons(); // инициализация кнопок переключения страниц
	void create_add_button(); // создание кнопки добавления аккаунта
	
	Account get_account_by_id(const int ID); // возвращение аккаунта по id

	void edit_account(); // редактирование аккаунта
	void create_account(); // создание аккаунта

	void open_account_creation_page(); // открытие страницы добавления аккаунта
	
	bool check_creation(); // проверка при добавлении аккаунта
	bool check_edition(); // проверка при редактировании аккаунта

	void adjust_fonts(); // настройка шрифтов
	void init_pixmaps(); // инициализация изображений
	void init_checks_messages(); // инициализация сообщений об ошибках

	void open_main_page(); // открытие главной страницы
	void open_account_edit_widget(); // открытие виджета редактирования аккаунта
	void open_account_creation_widget(); // открытие виджета добавления аккаунта
};

