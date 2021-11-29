#include "LoginPage.h"

LoginPage::LoginPage(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, SQLWork* account_db)
	: QMainWindow(parent) 
{
	this->ui = ui;
	this->page = ui->logInPage;
	this->account_db = account_db;
	adjust_fonts();
	init_check_message();
}

void LoginPage::open() 
{
	ui->stackedWidget->setCurrentWidget(page);
}

Account LoginPage::get_authorized_account() 
{
	Account account;
	QString login = get_login();
	QString pass = get_password();
	QString db_account_hash = account_db->get_text(DB::ACCOUNTS::FIELD::LOGIN, login, 2);
	QString db_account_salt = account_db->get_text(DB::ACCOUNTS::FIELD::LOGIN, login, 3);

	check->clear_error_message();
	if (login.size() == 0 || pass.size() == 0)
		check->show_error_message(LOGIN_ERROR::IS_EMPTY);
	
	else if (!account.is_right_password(db_account_hash, db_account_salt, pass)) 
		check->show_error_message(LOGIN_ERROR::WRONG_INPUT);
		
	else if (!is_account_have_access(login)) 
		check->show_error_message(LOGIN_ERROR::NO_ACCESS);
	
	else 
	{
		account.set_login(login);
		account.set_name(account_db->get_text(DB::ACCOUNTS::FIELD::LOGIN, login, 1));
		account.set_salted_hash_password(db_account_hash);
		account.set_salt(db_account_salt);
		account.set_role(account_db->get_int(DB::ACCOUNTS::FIELD::LOGIN, login, 4));
		account.set_access(account_db->get_int(DB::ACCOUNTS::FIELD::LOGIN, login, 5));
		account.set_id(account_db->get_int(DB::ACCOUNTS::FIELD::LOGIN, login, 6));
	}
	clear_password_input();
	return account;
}

bool LoginPage::is_account_have_access(QString login) 
{
	return account_db->get_int(DB::ACCOUNTS::FIELD::LOGIN, login, 5) == 1;
}

QString LoginPage::get_login() 
{
	return ui->authorization_login_input->text();
}

QString LoginPage::get_password() 
{
	return ui->authorization_pass_input->text();
}

void LoginPage::clear_login_input() 
{
	ui->authorization_login_input->setText("");
}

void LoginPage::clear_password_input() 
{
	ui->authorization_pass_input->setText("");
}

void LoginPage::adjust_fonts() 
{
	ui->log_in_button->setFont(FONTS::UBUNTU_14);
	ui->authorization_login_input->setFont(FONTS::UBUNTU_14);
	ui->authorization_pass_input->setFont(FONTS::UBUNTU_14);
	ui->login_page_name->setFont(FONTS::UBUNTU_16);
}

void LoginPage::init_check_message() 
{
	check = new QCheck(ui, ui->logInPage);
	check->clear_check_list();
	check->add_error_message({ LOGIN_ERROR::IS_EMPTY, "All fields should be used", 540, 470, 500, 30});
	check->add_error_message({ LOGIN_ERROR::NO_ACCESS, "Account have no access", 540, 470, 500, 30 });
	check->add_error_message({ LOGIN_ERROR::WRONG_INPUT, "Wrong login or password", 540, 470, 500, 30 });
}

void LoginPage::clear_error_message() 
{
	check->clear_error_message();
}

