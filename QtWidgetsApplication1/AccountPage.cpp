#include "AccountPage.h"

AccountPage::AccountPage(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, SQLWork* account_db)
	: QMainWindow(parent)
{
	this->ui = ui;
	this->page = ui->page_2;
	this->account_db = account_db;
	this->_parent = parent;

	adjust_fonts();
	init_pixmaps();
}

void AccountPage::start()
{
	ui->stackedWidget->setCurrentWidget(ui->adminMainPage);
	ui->stackedWidget_2->setCurrentWidget(page);

	update_accounts_id();
	clear_page();
	create_add_button();
	show_list();
}

void AccountPage::update_accounts_id()
{
	accounts_id = account_db->get_ints(6);
}

void AccountPage::clear_page()
{
	clear_account_list();
	qDeleteAll(page->findChildren<QPushButton*>("AccountPage_add_button"));
}

void AccountPage::clear_account_list()
{
	qDeleteAll(page->findChildren<QPushButton*>("choise_page_button"));
	qDeleteAll(page->findChildren<QPushButton*>("accountPage_button"));
}

void AccountPage::clear_account_edit_page()
{
	ui->lineEdit_9->setText("");
	ui->lineEdit_2->setText("");
	ui->lineEdit_6->setText("");
	ui->lineEdit_7->setText("");
	ui->lineEdit_8->setText("");
	ui->checkBox->setChecked(false);
	ui->checkBox_2->setChecked(false);
}

void AccountPage::show_list()
{
	clear_account_list();
	create_choise_page_buttons();

	int accounts_start_at = NUMBER_OF_ACCOUNTS_ON_PAGE * current_page;
	int accounts_end_at;

	if (accounts_id.size() - accounts_start_at >= NUMBER_OF_ACCOUNTS_ON_PAGE)
		accounts_end_at = accounts_start_at + NUMBER_OF_ACCOUNTS_ON_PAGE;
	else
		accounts_end_at = accounts_id.size();

	int j = 0, k = 0, n = 1;
	for (int i = 0; i < accounts_end_at - accounts_start_at; i++)
	{
		show_account(&get_account_by_id(accounts_id[i + accounts_start_at]), j, k);
		if (j == 3)
		{
			j = -1;
			k++;
		}
		j++;
	}
}

void AccountPage::show_account(Account* account, int row, int column)
{
	QLabel* name = get_name_label(account->get_name());
	QLabel* login = get_login_label(account->get_login());
	QLabel* image = get_image_label(account->get_role(), account->get_access());
	
	QPushButton* button = new QPushButton(page);
	QGridLayout* grid_layout = new QGridLayout();
	button->setGeometry(15 + ADD_X * row, 10 + ADD_Y * column, 255, 90);
	button->setObjectName("accountPage_button");
	button->setLayout(grid_layout);
	button->setStyleSheet("QPushButton#accountPage_button{ " + 
		STYLE::BACKGROUNG::CREAM + STYLE::BORDER::SOLID + 
		STYLE::BORDER::WIDTH::_2 + STYLE::BORDER::RADIUS_10 + " }"
		" \n "
		"QPushButton#accountPage_button:hover{ " + STYLE::BACKGROUNG::LIGHT_CREAM + "}");
	

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

QLabel* AccountPage::get_name_label(QString name)
{
	QLabel* name_label = new QLabel(name);
	name_label->setStyleSheet(STYLE::BACKGROUNG::TRANSPARENT);
	name_label->setFont(FONTS::UBUNTU_10);
	return name_label;
}

QLabel* AccountPage::get_login_label(QString name)
{
	QLabel* login_label = new QLabel(name);
	login_label->setStyleSheet(STYLE::BACKGROUNG::TRANSPARENT);
	login_label->setFont(FONTS::UBUNTU_10);
	return login_label;
}

void AccountPage::create_choise_page_buttons()
{
	ChoisePageButtons* choise_page_buttons = new ChoisePageButtons(_parent, ui, page, NUMBER_OF_ACCOUNTS_ON_PAGE, &current_page, *this);
	choise_page_buttons->set_number_of_elements(account_db->get_count());
	choise_page_buttons->show();
}

QLabel* AccountPage::get_image_label(const int ROLE, const int ACCESS) 
{
	QLabel* image = new QLabel();
	QPixmap pixmap;
	image->setFixedSize(62, 60);
	image->setAlignment(Qt::AlignHCenter);

	if (ROLE == 1)
	{
		pixmap = admin_pixmap;
		if (ACCESS) 
			image->setStyleSheet(STYLE::BACKGROUNG::GREEN + STYLE::BORDER::RADIUS_20);
		else
			image->setStyleSheet(STYLE::BACKGROUNG::LIGHT_RED + STYLE::BORDER::RADIUS_20);
	}
	else 
	{
		pixmap = user_pixmap;
		if (ACCESS)
			image->setStyleSheet(STYLE::BACKGROUNG::GREEN + STYLE::BORDER::RADIUS_30);
		else
			image->setStyleSheet(STYLE::BACKGROUNG::LIGHT_RED + STYLE::BORDER::RADIUS_30);
	}

	image->setPixmap(pixmap);
	return image;
}

void AccountPage::create_add_button()
{
	const int X = 920, Y = 650, WIDTH = 145, HEIGHT = 40;
	const QString BUTTON_TEXT = "Add new";

	QPushButton* add_button = new QPushButton(BUTTON_TEXT, page);
	add_button->setObjectName("AccountPage_add_button");
	add_button->setFont(FONTS::UBUNTU_10);
	add_button->setGeometry(X, Y, WIDTH, HEIGHT);
	add_button->setStyleSheet("QPushButton#AccountPage_add_button { " +
		STYLE::BACKGROUNG::GREEN + STYLE::BORDER::RADIUS_10 + " } " +
		" \n " +
		"QPushButton#AccountPage_add_button::hover { " + STYLE::BACKGROUNG::LIGHT_GREEN +" }");
	connect(add_button, &QPushButton::clicked, this,
		[=]() {
			open_account_creation_page();
		});
	add_button->show();
}

Account AccountPage::get_account_by_id(int id)
{
	Account account;
	QString q_id = QString::number(id);

	account.set_id(id);
	account.set_login(account_db->get_text(DB::ACCOUNTS::FIELD::ID, q_id, 0));
	account.set_name(account_db->get_text(DB::ACCOUNTS::FIELD::ID, q_id, 1));
	account.set_salted_hash_password(account_db->get_text(DB::ACCOUNTS::FIELD::ID, q_id, 2));
	account.set_salt(account_db->get_text(DB::ACCOUNTS::FIELD::ID, q_id, 3));
	account.set_role(account_db->get_int(DB::ACCOUNTS::FIELD::ID, q_id, 4));
	account.set_access(account_db->get_int(DB::ACCOUNTS::FIELD::ID, q_id, 5));

	return account;
}

void AccountPage::edit_account()
{
	clear_creation_error();
	int error_code = check_creation();
	
	if (error_code == -1)
		return show_creation_error("Wrong name", 0);
	else if (error_code == -2)
		return show_creation_error("Wrong login", 1);
	
	if (ui->lineEdit_7->text() != "")
	{
		if (error_code == 0)
			return show_creation_error("All fields should be used", 4.8);
		else if (error_code == -4)
			return show_creation_error("Wrong password", 2);
		else if (error_code == -5)
			return show_creation_error("Password not same", 3);
	}
	

	if (QMessageBox::Yes == QMessageBox::question(this, "Apply Confirmation", "Apply?", QMessageBox::Yes | QMessageBox::No))
	{
		
		Account account = Account();
		QString salt, hash;

		if (ui->lineEdit_7->text().size() == 0)
		{
			salt = account_db->get_text(DB::ACCOUNTS::FIELD::ID, ui->lineEdit_9->text(), 3);
			hash = account_db->get_text(DB::ACCOUNTS::FIELD::ID, ui->lineEdit_9->text(), 2);
		}
		else
		{
			salt = account.get_generated_salt();
			hash = account.get_generated_hash(ui->lineEdit_7->text(), salt);
		}

		account.set_id(ui->lineEdit_9->text().toInt());
		account.set_login(ui->lineEdit_6->text());
		account.set_name(ui->lineEdit_2->text());
		account.set_salted_hash_password(hash);
		account.set_salt(salt);
		account.set_role(ui->checkBox_2->isChecked());
		account.set_access(ui->checkBox->isChecked());

		account.update(account_db);
		start();
	}
}

void AccountPage::open_edit_account_page(Account account, bool is_removable, bool is_status_editable, bool is_back_to_accounts) {
	ui->stackedWidget->setCurrentWidget(ui->editAccountPage);
	ui->editAccountPage_title->setText("Accout editing");
	ui->lineEdit_6->setEnabled(false);
	clear_account_edit_page();
	clear_creation_error();

	if (is_removable)
	{
		ui->remove_account_button->setEnabled(true);
		ui->remove_account_button->setVisible(true);
	}
	else
	{
		ui->remove_account_button->setEnabled(false);
		ui->remove_account_button->setVisible(false);
	}

	if (account.get_id() == current_account->get_id())
	{
		ui->remove_account_button->setEnabled(false);
		ui->remove_account_button->setVisible(false);
	}
	
	if (is_status_editable)
	{
		ui->checkBox->setEnabled(true);
		ui->checkBox->setVisible(true);
		ui->checkBox_2->setEnabled(true);
		ui->checkBox_2->setVisible(true);
	}
	else
	{
		ui->checkBox->setEnabled(false);
		ui->checkBox->setVisible(false);
		ui->checkBox_2->setEnabled(false);
		ui->checkBox_2->setVisible(false);
	}

	if (is_back_to_accounts)
		connect(ui->commandLinkButton, SIGNAL(clicked()), _parent, SLOT(back_to_accounts()));
	else
		connect(ui->commandLinkButton, SIGNAL(clicked()), _parent, SLOT(open_books_page()));


	ui->pushButton->setText("Apply");

	disconnect(ui->pushButton, 0, 0, 0);
	connect(ui->pushButton, &QPushButton::clicked, this, [=]() { edit_account(); });

	ui->lineEdit_9->setText(QString::fromStdString(to_string(account.get_id())));
	ui->lineEdit_2->setText(account.get_name());
	ui->lineEdit_6->setText(account.get_login());
	ui->checkBox->setChecked(account.get_access());
	ui->checkBox_2->setChecked(account.get_role());

	disconnect(ui->remove_account_button, 0, 0, 0);
	connect(ui->remove_account_button, &QPushButton::clicked, this, 
		[=]() { 
		if (QMessageBox::Yes == QMessageBox::question(this, "Apply Confirmation", "Apply?", QMessageBox::Yes | QMessageBox::No)) {
			account_db->delete_field(DB::ACCOUNTS::FIELD::ID + " = " + ui->lineEdit_9->text());
			start();
		}
	});
}

void AccountPage::create_account()
{
	clear_creation_error();
	int error_code = check_creation();
	
	if (error_code == 0)
		return show_creation_error("All fields should be used", 4.8);
	
	else if (error_code == -1)
		return show_creation_error("Wrong name", 0);
	
	else if (error_code == -2)
		return show_creation_error("Wrong login", 1);
	
	else if (error_code == -3)
		return show_creation_error("login already used", 1);
	
	else if (error_code == -4)
		return show_creation_error("Wrong password", 2);

	else if (error_code == -5)
		return show_creation_error("Password not same", 3);


	if (QMessageBox::Yes == QMessageBox::question(this, "Apply Confirmation", "Apply?", QMessageBox::Yes | QMessageBox::No))
	{
		Account account = Account();

		QString salt = account.get_generated_salt();
		QString hash = account.get_generated_hash(ui->lineEdit_7->text(), salt);

		account.set_id(ui->lineEdit_9->text().toInt());
		account.set_login(ui->lineEdit_6->text());
		account.set_name(ui->lineEdit_2->text());
		account.set_salted_hash_password(hash);
		account.set_salt(salt);
		account.set_role(ui->checkBox_2->isChecked());
		account.set_access(ui->checkBox->isChecked());

		account.add_in_db(account_db);
		start();
	}
}

void AccountPage::open_account_creation_page()
{
	ui->stackedWidget->setCurrentWidget(ui->editAccountPage);
	ui->editAccountPage_title->setText("Accout creation");
	clear_account_edit_page();
	clear_creation_error();
	ui->remove_account_button->setEnabled(false);
	ui->remove_account_button->setVisible(false);
	ui->lineEdit_6->setEnabled(true);
	ui->pushButton->setText("Add");

	disconnect(ui->pushButton, 0, 0, 0);
	connect(ui->pushButton, &QPushButton::clicked, this, [=]() { create_account(); });

	int min_nonexistent = 1;

	if (accounts_id.size() != 0)
	{
		for (int i = 0; i < *max_element(accounts_id.begin(), accounts_id.end()) + 2; i++)
		{
			if (accounts_id.end() == std::find(accounts_id.begin(), accounts_id.end(), min_nonexistent))
			{
				break;
			}
			min_nonexistent++;
		}
	}
	ui->lineEdit_9->setText(QString::number(min_nonexistent));
}

/*
 1 - все хорошо
 0 - есть незаполненные поля
-1 - неправильное имя
-2 - неправильный логин
-3 - логин занят
-4 - неправильный пароль
-5 - пароли не совпадают
*/
int AccountPage::check_creation() {
	QString name = ui->lineEdit_2->text();
	QString login = ui->lineEdit_6->text();
	QString password = ui->lineEdit_7->text();
	QString repeat_password = ui->lineEdit_8->text();

	Check check({ {name, -1, "^([a-za-z ]{3,30})"}, 
		{login, -2, "^([\\w]{5,30})"}, 
		{password, -4, "^([\\w]{5,30})"} });

	
	if (Check::is_empty({ name, login, password, repeat_password })) 
		return 0;

	int err = check.check_all();

	if (err != 1) 
		return err;
	
	else if (password != repeat_password) 
		return -5;
	
	else if (account_db->get_text(DB::ACCOUNTS::FIELD::LOGIN, login, 0) != "")
		return -3;

	return 1;
}

void AccountPage::show_creation_error(QString message, double num_of_line)
{
	const int START_X = 900, START_Y = 135, ADD = 65, WIDTH = 400, HEIGHT = 50;
	QLabel* error_message = new QLabel(message, ui->editAccountPage);
	error_message->setObjectName("accountPage_creation_error");
	error_message->setStyleSheet(STYLE::COLOR::RED);
	error_message->setFont(FONTS::UBUNTU_12);
	error_message->setGeometry(START_X, START_Y + (ADD * num_of_line), WIDTH, HEIGHT);
	error_message->show();
}

void AccountPage::clear_creation_error() 
{
	qDeleteAll(ui->editAccountPage->findChildren<QLabel*>("accountPage_creation_error"));
}

void AccountPage::adjust_fonts() 
{
	ui->lineEdit_2->setFont(FONTS::UBUNTU_14);
	ui->lineEdit_6->setFont(FONTS::UBUNTU_14);
	ui->lineEdit_7->setFont(FONTS::UBUNTU_14);
	ui->lineEdit_8->setFont(FONTS::UBUNTU_14);
	ui->checkBox->setFont(FONTS::UBUNTU_14);
	ui->checkBox_2->setFont(FONTS::UBUNTU_14);
	ui->remove_account_button->setFont(FONTS::UBUNTU_14);
	ui->pushButton->setFont(FONTS::UBUNTU_14);
	ui->commandLinkButton->setFont(FONTS::UBUNTU_10);
	ui->editAccountPage_title->setFont(FONTS::UBUNTU_14);
}


void AccountPage::init_pixmaps() 
{
	admin_pixmap = QPixmap("admin.png");
	user_pixmap = QPixmap("user.png");

	admin_pixmap = admin_pixmap.scaled(QSize(62, 62), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	user_pixmap = user_pixmap.scaled(QSize(62, 52), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);	
}


void AccountPage::set_current_account(Account* current_account)
{
	this->current_account = current_account;
}




