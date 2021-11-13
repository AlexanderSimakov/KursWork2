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

namespace ACCOUNT_ERROR {
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

	void start();
	virtual void update_window();

	void open_edit_account_page(Account account, const bool IS_REMOVABLE = true, const bool IS_STATUS_EDITABLE = true, const bool IS_BACK_TO_ACCOUNTS = true);
	void set_current_account(Account* current_account);

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

	void update_accounts_id();

	void clear_page();
	void clear_account_list();
	void clear_account_edit_page();

	void show_list();
	void show_account(Account* account, const int ROW, const int COLUMN);

	QLabel* get_name_label(const QString NAME);
	QLabel* get_login_label(const QString LOGIN);
	QLabel* get_image_label(const int ROLE, const int ACCESS);

	void create_choise_page_buttons();
	void create_add_button();
	
	Account get_account_by_id(const int ID);

	void edit_account();
	void create_account();

	void open_account_creation_page();
	
	bool check_creation();
	bool check_edition();

	void adjust_fonts();
	void init_pixmaps();
	void init_checks_messages();

	void open_main_page();
	void open_account_edit_widget();
	void open_account_creation_widget();
};

