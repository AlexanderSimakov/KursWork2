#include "AccountPage.h"

AccountPage::AccountPage(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, SQLWork* account_db)
	: QMainWindow(parent), PAGE_WIDTH(ui->page_3->width()), PAGE_HEIGHT(ui->page_3->height()) {
	this->ui = ui;
	this->page = ui->page_2;
	this->account_db = account_db;
	this->_parent = parent;

	adjust_fonts();

	connect(ui->pushButton_2, &QPushButton::clicked, this,
		[=]() {
			ui->pushButton_2->disconnect();
			create_account();
		});

	admin_pixmap = QPixmap(QString::fromStdString("admin.png"));
	admin_pixmap = admin_pixmap.scaled(QSize(62, 62), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	user_pixmap = QPixmap(QString::fromStdString("user.png"));
	user_pixmap = user_pixmap.scaled(QSize(62, 52), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

void AccountPage::start() {
	ui->stackedWidget->setCurrentWidget(ui->adminMainPage);
	ui->stackedWidget_2->setCurrentWidget(ui->page_2);
	update_accounts_id();
	clear_page();
	create_add_button();
	show_list();
}

void AccountPage::update_accounts_id() {
	accounts_id = account_db->get_ints(6);
}

void AccountPage::clear_page() {
	clear_account_list();
	qDeleteAll(page->findChildren<QPushButton*>(QString::fromStdString("AccountPage_add_button")));
}

void AccountPage::clear_account_list() {
	qDeleteAll(page->findChildren<QPushButton*>(QString::fromStdString("choise_page_button")));
	qDeleteAll(page->findChildren<QPushButton*>(QString::fromStdString("accountPage_button")));
}

void AccountPage::clear_account_edit_page() {
	ui->lineEdit_9->setText("");
	ui->lineEdit_2->setText("");
	ui->lineEdit_6->setText("");
	ui->lineEdit_7->setText("");
	ui->lineEdit_8->setText("");
	ui->checkBox->setChecked(false);
	ui->checkBox_2->setChecked(false);
}

void AccountPage::show_list() {
	clear_account_list();
	create_choise_page_buttons();

	int accounts_start_at = NUMBER_OF_ACCOUNTS_ON_PAGE * current_page;
	int accounts_end_at;

	if (accounts_id.size() - accounts_start_at >= NUMBER_OF_ACCOUNTS_ON_PAGE)
		accounts_end_at = accounts_start_at + NUMBER_OF_ACCOUNTS_ON_PAGE;
	else
		accounts_end_at = accounts_id.size();

	int j = 0, k = 0, n = 1;
	for (int i = 0; i < accounts_end_at - accounts_start_at; i++) {
		show_account(&get_account_by_id(accounts_id[i + accounts_start_at]), j, k);
		if (j == 3) {
			j = -1;
			k++;
		}
		j++;
	}
}

void AccountPage::show_account(Account* account, int row, int column){
	QLabel* name = new QLabel(QString::fromStdString(account->get_name()));
	name->setStyleSheet("background: transparent;");
	name->setFont(QFont("Ubuntu", 10));

	QLabel* login = new QLabel(QString::fromStdString(account->get_login()));
	login->setStyleSheet("background: transparent;");
	login->setFont(QFont("Ubuntu", 10));

	QLabel* image = new QLabel("");
	QPixmap pixmap;
	image->setFixedSize(62, 60);
	image->setAlignment(Qt::AlignHCenter);

	if (account->get_role() == 1) {
		pixmap = admin_pixmap;
		if (account->get_access()) 
			image->setStyleSheet("background: #AEFF75; border-radius: 20px;");
		else
			image->setStyleSheet("background: #FF7373; border-radius: 20px;");
	}
	else {
		pixmap = user_pixmap;
		if (account->get_access())
			image->setStyleSheet("background: #AEFF75; border-radius: 30px;");
		else
			image->setStyleSheet("background: #FF7373; border-radius: 30px;");
	}

	image->setPixmap(pixmap);

	QPushButton* button = new QPushButton(page);
	QGridLayout* grid_layout = new QGridLayout();
	button->setGeometry(15 + ADD_X * row, 10 + ADD_Y * column, 255, 90);
	button->setObjectName("accountPage_button");
	button->setLayout(grid_layout);
	button->setStyleSheet("QPushButton#accountPage_button{ background-color: #FFD69C; border-style: solid; border-width: 2px; border-radius: 10px; }"
		" \n "
		"QPushButton#accountPage_button:hover{ background: #FFE2B9; }");
	
	grid_layout->addWidget(name, 0, 0);
	grid_layout->addWidget(login, 1, 0);
	grid_layout->addWidget(image, 0, 1, 0, 2, Qt::AlignRight);
	
	Account _account = *account;
	connect(button, &QPushButton::clicked, this,
		[=]() {
			open_edit_account_page(_account);
		});

	button->show();
}

void AccountPage::create_choise_page_buttons() {
	ChoisePageButtons* choise_page_buttons = new ChoisePageButtons(_parent, ui, page, NUMBER_OF_ACCOUNTS_ON_PAGE, &current_page, *this);
	choise_page_buttons->set_number_of_elements(account_db->get_count());
	choise_page_buttons->show();
}

void AccountPage::create_add_button() {
	const int X = 920, Y = 650, WIDTH = 145, HEIGHT = 40;
	const string BUTTON_TEXT = "Add new";

	QPushButton* add_button = new QPushButton(QString::fromStdString(BUTTON_TEXT), page);
	add_button->setObjectName("AccountPage_add_button");
	add_button->setFont(QFont("Ubuntu", 10));
	add_button->setGeometry(X, Y, WIDTH, HEIGHT);
	add_button->setStyleSheet("QPushButton#AccountPage_add_button { background: #AEFF75; border-radius: 10px; } QPushButton#AccountPage_add_button::hover { background: #c1ff96; }");
	connect(add_button, &QPushButton::clicked, this,
		[=]() {
			open_account_creation_page();
		});
	add_button->show();
}

Account AccountPage::get_account_by_id(int id) {
	Account account;

	account.set_id(id);
	account.set_login(account_db->get_text("ID", to_string(id), 0));
	account.set_name(account_db->get_text("ID", to_string(id), 1));
	account.set_salted_hash_password(account_db->get_text("ID", to_string(id), 2));
	account.set_salt(account_db->get_text("ID", to_string(id), 3));
	account.set_role(account_db->get_int("ID", to_string(id), 4));
	account.set_access(account_db->get_int("ID", to_string(id), 5));

	return account;
}

void AccountPage::edit_account() {
	if (QMessageBox::Yes == QMessageBox::question(this, "Apply Confirmation", "Apply?", QMessageBox::Yes | QMessageBox::No)) {
		
		Account account = Account();
		string salt, hash;

		if (ui->lineEdit_7->text().size() == 0) {
			salt = account_db->get_text("ID", ui->lineEdit_9->text().toStdString(), 3);
			hash = account_db->get_text("ID", ui->lineEdit_9->text().toStdString(), 2);
		}
		else {
			salt = account.get_generated_salt();
			hash = account.get_generated_hash(ui->lineEdit_7->text().toStdString(), salt);
		}

		account.set_id(ui->lineEdit_9->text().toInt());
		account.set_login(ui->lineEdit_6->text().toStdString());
		account.set_name(ui->lineEdit_2->text().toStdString());
		account.set_salted_hash_password(hash);
		account.set_salt(salt);
		account.set_role(ui->checkBox_2->isChecked());
		account.set_access(ui->checkBox->isChecked());

		account.update(account_db);
	}
}

void AccountPage::open_edit_account_page(Account account, bool is_removable, bool is_status_editable, bool is_back_to_accounts) {
	ui->stackedWidget->setCurrentWidget(ui->editAccountPage);
	ui->editAccountPage_title->setText("Accout editing");
	clear_account_edit_page();

	if (is_removable) {
		ui->remove_account_button->setEnabled(true);
		ui->remove_account_button->setVisible(true);
	}
	else {
		ui->remove_account_button->setEnabled(false);
		ui->remove_account_button->setVisible(false);
	}
	
	if (is_status_editable) {
		ui->checkBox->setEnabled(true);
		ui->checkBox->setVisible(true);
		ui->checkBox_2->setEnabled(true);
		ui->checkBox_2->setVisible(true);
	}
	else {
		ui->checkBox->setEnabled(false);
		ui->checkBox->setVisible(false);
		ui->checkBox_2->setEnabled(false);
		ui->checkBox_2->setVisible(false);
	}

	if (is_back_to_accounts) {
		connect(ui->commandLinkButton, SIGNAL(clicked()), _parent, SLOT(back_to_accounts()));
	}
	else {
		connect(ui->commandLinkButton, SIGNAL(clicked()), _parent, SLOT(open_books_page()));
	}


	ui->pushButton->setText("Apply");

	disconnect(ui->pushButton, 0, 0, 0);
	connect(ui->pushButton, &QPushButton::clicked, this, [=]() { edit_account(); });


	ui->lineEdit_9->setText(QString::fromStdString(to_string(account.get_id())));
	ui->lineEdit_2->setText(QString::fromStdString(account.get_name()));
	ui->lineEdit_6->setText(QString::fromStdString(account.get_login()));
	ui->checkBox->setChecked(account.get_access());
	ui->checkBox_2->setChecked(account.get_role());

	disconnect(ui->remove_account_button, 0, 0, 0);
	connect(ui->remove_account_button, &QPushButton::clicked, this, [=]() { 
		QMessageBox::question(this, "Apply Confirmation", "Apply?", QMessageBox::Yes | QMessageBox::No);
		account_db->delete_field("ID = " + ui->lineEdit_9->text().toStdString()); 
	});
}

void AccountPage::create_account() {
	clear_creation_error();
	int error_code = check_creation();
	if (error_code == 0) {
		show_creation_error("All fields should be used", 4.8);
		return;
	}
	else if (error_code == -1) {
		show_creation_error("Wrong name", 0);
		return;
	}
	else if (error_code == -2) {
		show_creation_error("Wrong login", 1);
		return;
	}
	else if (error_code == -3) {
		show_creation_error("login already used", 1);
		return;
	}
	else if (error_code == -4) {
		show_creation_error("Wrong password", 2);
		return;
	}
	else if (error_code == -5) {
		show_creation_error("Password not same", 3);
		return;
	}

	if (QMessageBox::Yes == QMessageBox::question(this, "Apply Confirmation", "Apply?", QMessageBox::Yes | QMessageBox::No)) {
		Account account = Account();

		string salt = account.get_generated_salt();
		string hash = account.get_generated_hash(ui->lineEdit_7->text().toStdString(), salt);

		account.set_id(ui->lineEdit_9->text().toInt());
		account.set_login(ui->lineEdit_6->text().toStdString());
		account.set_name(ui->lineEdit_2->text().toStdString());
		account.set_salted_hash_password(hash);
		account.set_salt(salt);
		account.set_role(ui->checkBox_2->isChecked());
		account.set_access(ui->checkBox->isChecked());

		account.add_in_db(account_db);
		start();
	}
}

void AccountPage::open_account_creation_page(){
	ui->stackedWidget->setCurrentWidget(ui->editAccountPage);
	ui->editAccountPage_title->setText("Accout creation");
	clear_account_edit_page();
	clear_creation_error();
	ui->remove_account_button->setEnabled(false);
	ui->remove_account_button->setVisible(false);
	ui->pushButton->setText("Add");

	disconnect(ui->pushButton, 0, 0, 0);
	connect(ui->pushButton, &QPushButton::clicked, this, [=]() { create_account(); });

	int min_nonexistent = 1;

	if (accounts_id.size() != 0) {
		for (int i = 0; i < *max_element(accounts_id.begin(), accounts_id.end()) + 2; i++) {
			if (accounts_id.end() == std::find(accounts_id.begin(), accounts_id.end(), min_nonexistent)) {
				break;
			}
			min_nonexistent++;
		}
	}
	ui->lineEdit_9->setText(QString::fromStdString(to_string(min_nonexistent)));
}



/*
 1 - ��� ������
 0 - ���� ������������� ����
-1 - ������������ ���
-2 - ������������ �����
-3 - ����� �����
-4 - ������������ ������
-5 - ������ �� ���������
*/
int AccountPage::check_creation() {
	cmatch result;
	regex regular_name("^([A-Za-z ]{3,30})");
	regex regular_login("^([\\w]{5,30})");
	regex regular_password("^([\\w]{5,30})");


	string name = ui->lineEdit_2->text().toStdString();
	string login = ui->lineEdit_6->text().toStdString();
	string password = ui->lineEdit_7->text().toStdString();
	string repeat_password = ui->lineEdit_8->text().toStdString();

	if (name == "" || login == "" || password == "" || repeat_password == "") {
		return 0;
	}
	else if (!regex_match(name.c_str(), result, regular_name)) {
		return -1;
	}
	else  if (!regex_match(login.c_str(), result, regular_login)) {
		return -2;
	}
	else  if (false) { // ��������� ������
		return -3;
	}
	else  if (!regex_match(password.c_str(), result, regular_password)) {
		return -4;
	}
	else  if (password != repeat_password) {
		return -5;
	}
	

	return 1;
}

void AccountPage::show_creation_error(string message, double num_of_line) {
	const int START_X = 900, START_Y = 135, ADD = 65, WIDTH = 400, HEIGHT = 50;
	QLabel* error_message = new QLabel(QString::fromStdString(message), ui->editAccountPage);
	error_message->setObjectName("accountPage_creation_error");
	error_message->setStyleSheet("color: #f5685d");
	error_message->setFont(QFont("Ubuntu", 12));
	error_message->setGeometry(START_X, START_Y + (ADD * num_of_line), WIDTH, HEIGHT);
	error_message->show();
}

void AccountPage::clear_creation_error() {
	qDeleteAll(ui->editAccountPage->findChildren<QLabel*>(QString::fromStdString("accountPage_creation_error")));
}

void AccountPage::adjust_fonts() {
	ui->lineEdit_2->setFont(QFont("Ubuntu", 14));
	ui->lineEdit_6->setFont(QFont("Ubuntu", 14));
	ui->lineEdit_7->setFont(QFont("Ubuntu", 14));
	ui->lineEdit_8->setFont(QFont("Ubuntu", 14));
	ui->checkBox->setFont(QFont("Ubuntu", 14));
	ui->checkBox_2->setFont(QFont("Ubuntu", 14));
	ui->remove_account_button->setFont(QFont("Ubuntu", 14));
	ui->pushButton->setFont(QFont("Ubuntu", 14));
	ui->commandLinkButton->setFont(QFont("Ubuntu", 10));
	ui->editAccountPage_title->setFont(QFont("Ubuntu", 14));

}




