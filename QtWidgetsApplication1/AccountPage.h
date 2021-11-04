#pragma once
#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include "ui_QtWidgetsApplication1.h"
#include "SQLWORK.h"
#include "Account.h"
#include "Page.h"
#include "ChoisePageButtons.h"

class AccountPage : public QMainWindow, public Page
{
	Q_OBJECT
public:
	AccountPage(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, SQLWork* account_db);

	virtual void update_window() {
		show_list();
	}

	void start();

	void open_edit_account_page(Account account, bool is_removable = true, bool is_status_editable = true, bool is_back_to_accounts = true);

private:
	QWidget* _parent;
	Ui::QtWidgetsApplication1Class* ui;
	QWidget* page;
	SQLWork* account_db;

	

	const int NUMBER_OF_ACCOUNTS_ON_PAGE = 24;
	const int ADD = 50;
	const int ADD_X = 265;
	const int ADD_Y = 100;
	const int MARGIN = 10;
	const int PAGE_WIDTH;
	const int PAGE_HEIGHT;
	int current_page = 0;

	QPixmap admin_pixmap;
	QPixmap user_pixmap;

	vector<int> accounts_id;

	void update_accounts_id();

	void clear_page();
	void clear_account_list();
	void clear_account_edit_page();

	void show_list();
	void show_account(Account* account, int row, int column);

	void create_choise_page_buttons();
	void create_add_button();
	
	Account get_account_by_id(int id);

	void edit_account();

	void create_account();
	void open_account_creation_page();

};

