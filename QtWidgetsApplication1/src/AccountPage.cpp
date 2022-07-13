#include "AccountPage.h"

AccountPage::AccountPage(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, SQLWork* account_db)
	: QMainWindow(parent)
{
	this->ui = ui;
	this->page = ui->page_2;
	this->account_db = account_db;
	this->parent = parent;

	adjust_fonts();
	init_pixmaps();
	init_checks_messages();
}

void AccountPage::update_window() 
{
	show_list();
}

void AccountPage::start()
{
	open_main_page();
	update_accounts_id();
	clear_page();
	create_add_button();
	show_list();
}

void AccountPage::update_accounts_id()
{
	accounts_id = account_db->get_ints(DB::ACCOUNTS::INT::ID);
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

void AccountPage::show_account(Account* account, const int ROW, const int COLUMN)
{
	const int START_X = 265, START_Y = 100;
	QLabel* name = get_name_label(account->get_name());
	QLabel* login = get_login_label(account->get_login());
	QLabel* image = get_image_label(account->get_role(), account->get_access());
	
	QPushButton* button = new QPushButton(page);
	QGridLayout* grid_layout = new QGridLayout();
	button->setGeometry(15 + START_X * ROW, 10 + START_Y * COLUMN, 255, 90);
	button->setObjectName("accountPage_button");
	button->setLayout(grid_layout);
	button->setStyleSheet("QPushButton#accountPage_button{ " + 
		STYLE::BACKGROUNG::CREAM + STYLE::BORDER::SOLID + 
		STYLE::BORDER::WIDTH::_2 + STYLE::BORDER::RADIUS_10 + " } "
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

QLabel* AccountPage::get_name_label(const QString NAME)
{
	QLabel* name = new QLabel(NAME);
	name->setStyleSheet(STYLE::BACKGROUNG::TRANSPARENT);
	name->setFont(FONTS::UBUNTU_10);
	return name;
}

QLabel* AccountPage::get_login_label(const QString LOGIN)
{
	QLabel* login = new QLabel(LOGIN);
	login->setStyleSheet(STYLE::BACKGROUNG::TRANSPARENT);
	login->setFont(FONTS::UBUNTU_10);
	return login;
}

void AccountPage::create_choise_page_buttons()
{
	ChoisePageButtons* choise_page_buttons = new ChoisePageButtons(parent, ui, page, NUMBER_OF_ACCOUNTS_ON_PAGE, &current_page, *this);
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
		"QPushButton#AccountPage_add_button::hover { " + STYLE::BACKGROUNG::LIGHT_GREEN +" }");

	connect(add_button, &QPushButton::clicked, this,
		[=]() {
			open_account_creation_page();
		});

	add_button->show();
}

Account AccountPage::get_account_by_id(const int ID)
{
	Account account;
	const QString QID = QString::number(ID);

	account.set_id(ID);
	account.set_login(account_db->get_text(DB::ACCOUNTS::FIELD::ID, QID, DB::ACCOUNTS::INT::LOGIN));
	account.set_name(account_db->get_text(DB::ACCOUNTS::FIELD::ID, QID, DB::ACCOUNTS::INT::NAME));
	account.set_salted_hash_password(account_db->get_text(DB::ACCOUNTS::FIELD::ID, QID, DB::ACCOUNTS::INT::HASH));
	account.set_salt(account_db->get_text(DB::ACCOUNTS::FIELD::ID, QID, DB::ACCOUNTS::INT::SALT));
	account.set_role(account_db->get_int(DB::ACCOUNTS::FIELD::ID, QID, DB::ACCOUNTS::INT::ROLE));
	account.set_access(account_db->get_int(DB::ACCOUNTS::FIELD::ID, QID, DB::ACCOUNTS::INT::ACCESS));

	return account;
}

void AccountPage::edit_account()
{
	if (!check_edition())
		return;

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

void AccountPage::open_edit_account_page(Account account, const bool IS_REMOVABLE, const bool IS_STATUS_EDITABLE, const bool IS_BACK_TO_ACCOUNTS) 
{
	open_account_edit_widget();
	clear_account_edit_page();

	if (IS_REMOVABLE)
		ui->remove_account_button->setVisible(true);
	else
		ui->remove_account_button->setVisible(false);

	if (account.get_id() == current_account->get_id())
		ui->remove_account_button->setVisible(false);

	if (IS_STATUS_EDITABLE)
	{
		ui->checkBox->setVisible(true);
		ui->checkBox_2->setVisible(true);
	}
	else
	{
		ui->checkBox->setVisible(false);
		ui->checkBox_2->setVisible(false);
	}

	if (IS_BACK_TO_ACCOUNTS)
		connect(ui->commandLinkButton, SIGNAL(clicked()), parent, SLOT(back_to_accounts()));
	else
		connect(ui->commandLinkButton, SIGNAL(clicked()), parent, SLOT(open_books_page()));


	disconnect(ui->pushButton, 0, 0, 0);
	connect(ui->pushButton, &QPushButton::clicked, this, [=]() { edit_account(); });

	disconnect(ui->remove_account_button, 0, 0, 0);
	connect(ui->remove_account_button, &QPushButton::clicked, this, 
		[=]() { 
			if (QMessageBox::Yes == QMessageBox::question(this, "Apply Confirmation", "Apply?", QMessageBox::Yes | QMessageBox::No)) {
				account_db->delete_field(DB::ACCOUNTS::FIELD::ID + " = " + ui->lineEdit_9->text());
				start();
			}
		});

	ui->lineEdit_9->setText(QString::fromStdString(to_string(account.get_id())));
	ui->lineEdit_2->setText(account.get_name());
	ui->lineEdit_6->setText(account.get_login());
	ui->checkBox->setChecked(account.get_access());
	ui->checkBox_2->setChecked(account.get_role());
}

void AccountPage::create_account()
{
	if (!check_creation())
		return;
	
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
	open_account_creation_widget();
	clear_account_edit_page();

	disconnect(ui->pushButton, 0, 0, 0);
	connect(ui->pushButton, &QPushButton::clicked, this, [=]() { create_account(); });

	int min_nonexistent = Page::get_min_nonexist(accounts_id);
	ui->lineEdit_9->setText(QString::number(min_nonexistent));
}

bool AccountPage::check_creation() 
{
	QString name = ui->lineEdit_2->text();
	QString login = ui->lineEdit_6->text();
	QString password = ui->lineEdit_7->text();
	QString repeat_password = ui->lineEdit_8->text();

	_check->clear_error_message();
	_check->clear_check_list();
	_check->add_error_check({ ACCOUNT_ERROR::WRONG_NAME, name, regex("^([a-zA-Z ]{3,30})") });
	_check->add_error_check({ ACCOUNT_ERROR::WRONG_LOGIN, login, regex("^([\\w]{5,30})") });
	_check->add_error_check({ ACCOUNT_ERROR::WRONG_PASSWORD, password, regex("^([\\w]{5,30})") });

	if (QCheck::is_empty({ name, login, password, repeat_password }))
	{
		_check->show_error_message(ACCOUNT_ERROR::IS_EMPTY);
		return false;
	}
	else if (password != repeat_password)
	{
		_check->show_error_message(ACCOUNT_ERROR::PASSWORDS_NOT_SAME);
		return false;
	}
	else if (account_db->get_text(DB::ACCOUNTS::FIELD::LOGIN, login, 0) != "")
	{
		_check->show_error_message(ACCOUNT_ERROR::LOGIN_EXIST);
		return false;
	}

	int error_code = _check->check_all();
	if (error_code != ACCOUNT_ERROR::ALL_GOOD)
	{
		_check->show_error_message(error_code);
		return false;
	}

	return true;
}

bool AccountPage::check_edition() 
{
	QString name = ui->lineEdit_2->text();
	QString login = ui->lineEdit_6->text();
	QString password = ui->lineEdit_7->text();
	QString repeat_password = ui->lineEdit_8->text();

	_check->clear_error_message();
	_check->clear_check_list();
	_check->add_error_check({ ACCOUNT_ERROR::WRONG_NAME, name, regex("^([a-zA-Z ]{3,30})") });
	_check->add_error_check({ ACCOUNT_ERROR::WRONG_LOGIN, login, regex("^([\\w]{5,30})") });
	_check->add_error_check({ ACCOUNT_ERROR::WRONG_PASSWORD, password, regex("^([\\w]{5,30})") });


	int error_code;
	if (ui->lineEdit_7->text() != "") 
	{
		if (QCheck::is_empty({ name, login, password, repeat_password }))
		{
			_check->show_error_message(ACCOUNT_ERROR::IS_EMPTY);
			return false;
		}
		else if (password != repeat_password)
		{
			_check->show_error_message(ACCOUNT_ERROR::PASSWORDS_NOT_SAME);
			return false;
		}
		
		int error_code = _check->check_all();
		if (error_code != ACCOUNT_ERROR::ALL_GOOD)
		{
			_check->show_error_message(error_code);
			return false;
		}
	}
	else
	{
		if (_check->check_by_error_codes({ ACCOUNT_ERROR::WRONG_NAME }) != ACCOUNT_ERROR::ALL_GOOD)
		{
			_check->show_error_message(ACCOUNT_ERROR::WRONG_NAME);
			return false;
		}
	}

	return true;
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

void AccountPage::init_checks_messages() 
{
	_check = new QCheck(ui, ui->editAccountPage);
	_check->clear_message_list();
	_check->add_error_message({ ACCOUNT_ERROR::IS_EMPTY, "All fields should be used", 950, 400, 400, 50 });
	_check->add_error_message({ ACCOUNT_ERROR::WRONG_NAME, "Wrong name", 950, 135, 400, 50});
	_check->add_error_message({ ACCOUNT_ERROR::WRONG_LOGIN, "Wrong login", 950, 200, 400, 50});
	_check->add_error_message({ ACCOUNT_ERROR::LOGIN_EXIST, "Login already exist", 950, 200, 400, 50 });
	_check->add_error_message({ ACCOUNT_ERROR::WRONG_PASSWORD, "Wrong password", 950, 265, 400, 50});
	_check->add_error_message({ ACCOUNT_ERROR::PASSWORDS_NOT_SAME, "Passwords should be same", 950, 330, 400, 50 });
}

void AccountPage::set_current_account(Account* current_account)
{
	this->current_account = current_account;
}

void AccountPage::open_main_page() 
{
	ui->stackedWidget->setCurrentWidget(ui->adminMainPage);
	ui->stackedWidget_2->setCurrentWidget(page);
}

void AccountPage::open_account_edit_widget() 
{
	ui->stackedWidget->setCurrentWidget(ui->editAccountPage);
	ui->editAccountPage_title->setText("Accout editing");
	ui->lineEdit_6->setEnabled(false);
	ui->pushButton->setText("Apply");
}

void AccountPage::open_account_creation_widget() 
{
	ui->stackedWidget->setCurrentWidget(ui->editAccountPage);
	ui->editAccountPage_title->setText("Accout creation");
	ui->remove_account_button->setVisible(false);
	ui->lineEdit_6->setEnabled(true);
	ui->pushButton->setText("Add");
}

