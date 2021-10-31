#include "LoginPage.h"

LoginPage::LoginPage(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, SQLWork* account_db)
	: QMainWindow(parent), PAGE_WIDTH(ui->page_3->width()), PAGE_HEIGHT(ui->page_3->height()) {
	this->ui = ui;
	this->page = ui->logInPage;
	this->account_db = account_db;

	connect(ui->log_in_button, &QPushButton::clicked, this, 
		[]() {
		
		
		});
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
		show_error_message("Fields should not be empty");
		return account;
	}

	string db_account_hash = account_db->get_text("LOGIN", login, 2);
	string db_account_salt = account_db->get_text("LOGIN", login, 3);
	string input_password = account.get_password(db_account_hash, db_account_salt, pass);

	if (input_password == "-1") {
		clear_error_message();
		show_error_message("Error");
		return account;
	}
	else if (account_db->get_int("LOGIN", login, 5) == 0) {
		clear_error_message();
		show_error_message("Account have no access");
		return account;
	}
	else { // good
		account.set_role(account_db->get_int("LOGIN", login, 4));
		return account;
	}
}


string LoginPage::get_login() {
	return ui->authorization_login_input->text().toStdString();
}

string LoginPage::get_password() {
	return ui->authorization_pass_input->text().toStdString();
}

void LoginPage::show_error_message(string text) {
	QLabel* error_message = new QLabel(QString::fromStdString(text), page);
	error_message->setObjectName("LoginPage_error_message");
	error_message->setAlignment(Qt::AlignHCenter);
	error_message->setGeometry(391, 468, 500, 30);
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







