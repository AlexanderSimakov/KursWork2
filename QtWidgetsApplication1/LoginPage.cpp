#include "LoginPage.h"

LoginPage::LoginPage(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, SQLWork* account_db)
	: QMainWindow(parent), PAGE_WIDTH(ui->page_3->width()), PAGE_HEIGHT(ui->page_3->height()) {
	this->ui = ui;
	this->page = ui->logInPage;
	this->account_db = account_db;

}

void LoginPage::open() {
	ui->stackedWidget->setCurrentWidget(page);
}

Account LoginPage::get_authorized_account() {
	Account account;
	string login = get_login();
	string pass = get_password();

	if (login.size() == 0 || pass.size() == 0) {
		clear_error_message();
		show_error_message("Oops. Fields should not be empty");
		return account;
	}else if (!is_account_have_access(login)) {
		clear_error_message();
		clear_password_input();
		show_error_message("Oops. Account have no access");
		return account;
	}

	string db_account_hash = account_db->get_text("LOGIN", login, 2);
	string db_account_salt = account_db->get_text("LOGIN", login, 3);

	if (!account.is_right_password(db_account_hash, db_account_salt, pass)) {
		clear_error_message();
		clear_password_input();
		show_error_message("Oops. Wrong login or password");
		return account;
	}
	else { 
		account.set_login(login);
		account.set_name(account_db->get_text("LOGIN", login, 1));
		account.set_salted_hash_password(db_account_hash);
		account.set_salt(db_account_salt);
		account.set_role(account_db->get_int("LOGIN", login, 4));
		account.set_access(account_db->get_int("LOGIN", login, 5));
		account.set_id(account_db->get_int("LOGIN", login, 6));
		return account;
	}
}

bool LoginPage::is_account_have_access(string login) {
	return account_db->get_int("LOGIN", login, 5) == 1;
}

string LoginPage::get_login() {
	return ui->authorization_login_input->text().toStdString();
}

string LoginPage::get_password() {
	return ui->authorization_pass_input->text().toStdString();
}

void LoginPage::show_error_message(string text) {
	init_error_message();
	error_message->setText(QString::fromStdString(text));
	error_message->show();
}

void LoginPage::clear_error_message() {
	qDeleteAll(page->findChildren<QLabel*>("LoginPage_error_message"));
}

void LoginPage::clear_login_input() {
	ui->authorization_login_input->setText("");
}

void LoginPage::clear_password_input() {
	ui->authorization_pass_input->setText("");
}

void LoginPage::init_error_message() {
	error_message = new QLabel(QString::fromStdString(""), page);
	error_message->setObjectName("LoginPage_error_message");
	error_message->setAlignment(Qt::AlignHCenter);
	error_message->setStyleSheet("color: #f5685d");
	error_message->setFont(QFont("Arial", 12));
	error_message->setGeometry(391, 468, 500, 30);
}





