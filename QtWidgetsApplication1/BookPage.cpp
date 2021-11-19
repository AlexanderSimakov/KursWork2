#include "BookPage.h"

BookPage::BookPage(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, SQLWork* books_db, SQLWork* people_db)
	: QMainWindow(parent)
{
	this->parent = parent;
	this->ui = ui;
	this->page = ui->page_3;
	this->books_db = books_db;
	this->people_db = people_db;

	choise_page_buttons = new ChoisePageButtons(parent, ui, page, NUMBER_OF_BOOKS_ON_PAGE, &current_page, *this);
	searching = new Searching(parent, ui, page, books_db, *this, books_id);
	ui->id_create_book_line_edit->setVisible(false);

	adjust_fonts();
	init_cheks_messages();

	connect(ui->pushButton_4, &QPushButton::clicked, this, 
		[=]() {
			ui->pushButton_4->disconnect();
			QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), "/home", ("Images (*.png *.jpg)"));
			ui->img_create_book_line_edit->setText(fileName);
		});
}

void BookPage::update_window() 
{
	show_list();
}

void BookPage::start() 
{
	open_main_widjet();
	update_books_id();
	clear_page();
	create_add_button();
	create_search();
	show_list();
}

void BookPage::update_books_id() 
{
	books_id = books_db->get_ints();
}

void BookPage::clear_page() 
{
	clear_book_list();
	searching->delete_widgets();
	qDeleteAll(page->findChildren<QPushButton*>("BookPage_add_button"));
}

void BookPage::clear_book_list() 
{
	qDeleteAll(page->findChildren<QLabel*>());
	qDeleteAll(page->findChildren<QPushButton*>("choise_page_button"));
	qDeleteAll(page->findChildren<QPushButton*>("BookPage_btn"));
}

void BookPage::show_list()
{
	clear_book_list();
	create_choise_page_buttons();

	int books_start_at = NUMBER_OF_BOOKS_ON_PAGE * current_page;
	int books_end_at;

	if (books_id.size() - books_start_at >= NUMBER_OF_BOOKS_ON_PAGE)
		books_end_at = books_start_at + NUMBER_OF_BOOKS_ON_PAGE;
	else
		books_end_at = books_id.size();

	int j = 0, k = 0, n = 1;
	for (int i = 0; i < books_end_at - books_start_at; i++) 
	{
		show_book(Book::get_book_by_id(books_db, books_id[i + books_start_at]), j, k);
		if (j == 3) 
		{
			j = -1;
			k++;
		}
		j++;
	}
}

void BookPage::show_book(Book book, int row, int column) 
{
	const int WIDTH = 340, HEIGHT = 300, START_X = 10, START_Y = 13;
	const int ADD_X = 360, ADD_Y = 320;

	QLabel* name = get_name_label(book.get_name());
	QLabel* image = new QLabel(page);
	image->setPixmap(*get_image_pixmap(book.get_path_to_img(), 320, 240));
	image->setStyleSheet(STYLE::BACKGROUNG::TRANSPARENT);

	QPushButton* button = new QPushButton(page);
	button->setGeometry(START_X + ADD_X * row, START_Y + ADD_Y * column, WIDTH, HEIGHT);
	button->setLayout(new QGridLayout);
	button->setObjectName("BookPage_btn");
	if (book.get_enabled()) 
	{
		button->setStyleSheet("QPushButton#BookPage_btn{ " +
			STYLE::BACKGROUNG::CREAM + STYLE::BORDER::SOLID + STYLE::BORDER::WIDTH::_2 +
			STYLE::BORDER::RADIUS_10 + STYLE::BORDER::DARK_GREEN + " }\n "
			"QPushButton#BookPage_btn:hover{ " + STYLE::BACKGROUNG::LIGHT_CREAM + " }");
	}
	else 
	{
		button->setStyleSheet("QPushButton#BookPage_btn{ " +
			STYLE::BACKGROUNG::CREAM + STYLE::BORDER::SOLID + STYLE::BORDER::WIDTH::_2 +
			STYLE::BORDER::RADIUS_10 + STYLE::BORDER::RED + " } \n " +
			"QPushButton#BookPage_btn:hover{ " + STYLE::BACKGROUNG::LIGHT_CREAM + " }");
	}
	

	button->layout()->addWidget(image);
	button->layout()->addWidget(name);
	button->show();
	connect(button, &QPushButton::clicked, this,
		[=]() {
			ui->stackedWidget_2->setCurrentWidget(ui->showBookPage);
			open_show_book_page(book);
		});
}

QLabel* BookPage::get_name_label(QString book_name) 
{
	QLabel* name = new QLabel(book_name, page);
	name->setObjectName("BookPage_name");
	name->setStyleSheet(STYLE::BACKGROUNG::LIGHT_CREAM + STYLE::BORDER::RADIUS_10);
	name->setAlignment(Qt::AlignCenter);
	name->setFont(FONTS::UBUNTU_10);
	return name;
}

QPixmap* BookPage::get_image_pixmap(QString path_to_img, const int WIDTH, const int HEIGHT) 
{
	QPixmap *target = new QPixmap(QSize(WIDTH, HEIGHT));
    target->fill(Qt::transparent);

    QPixmap p = QPixmap(path_to_img);
    p = p.scaled(QSize(WIDTH, HEIGHT), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPainter painter (target);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    QPainterPath path = QPainterPath();
	int start_x = (WIDTH - p.size().width()) / 2;
	int start_y = (HEIGHT - p.size().height()) / 2;
    path.addRoundedRect(start_x, start_y, p.size().width(), p.size().height(), 10, 10);
    painter.setClipPath(path);
    painter.drawPixmap(start_x, start_y, p);

	return target;
}

void BookPage::create_choise_page_buttons() 
{
	choise_page_buttons->set_number_of_elements(books_id.size());
	choise_page_buttons->show();
}

void BookPage::create_search() 
{
	vector<Search> comm;
	comm.push_back({ "Name", " WHERE " + DB::BOOKS::FIELD::NAME + " GLOB " });
	comm.push_back({ "Author", " WHERE " + DB::BOOKS::FIELD::AUTHOR + " GLOB " });
	comm.push_back({ "Year", " WHERE " + DB::BOOKS::FIELD::YEAR + " GLOB " });
	comm.push_back({ "Genre", " WHERE " + DB::BOOKS::FIELD::GENRE + " GLOB " });
	comm.push_back({ "Pages", " WHERE " + DB::BOOKS::FIELD::PAGES + " GLOB " });
	comm.push_back({ "Content", " WHERE " + DB::BOOKS::FIELD::CONTENT + " GLOB " });
	searching->init(comm, &current_page);
	searching->show();
}

void BookPage::create_add_button() 
{
	const int X = 920, Y = 650, WIDTH = 145, HEIGHT = 40;
	const QString BUTTON_TEXT = "Add new";

	QPushButton* add_button = new QPushButton(BUTTON_TEXT, page);
	add_button->setGeometry(X, Y, WIDTH, HEIGHT);
	add_button->setFont(FONTS::UBUNTU_10);
	add_button->setObjectName("BookPage_add_button");

	add_button->setStyleSheet("QPushButton#BookPage_add_button { " +
		STYLE::BACKGROUNG::GREEN + STYLE::BORDER::RADIUS_10 + " } " +
		"QPushButton#BookPage_add_button::hover { " + STYLE::BACKGROUNG::LIGHT_GREEN + " }");
	
	connect(add_button, &QPushButton::clicked, this, [=]() { open_book_creation_page(); });
	add_button->show();
}

void BookPage::open_show_book_page(Book book) 
{
	ui->stackedWidget_2->setCurrentWidget(ui->showBookPage);
	ui->show_book_name->setText(book.get_name());
	ui->show_author->setText(book.get_author_name());
	ui->show_year->setText(QString::number(book.get_year()));
	ui->show_pages->setText(QString::number(book.get_amount_of_page()));
	ui->show_content->setText(book.get_content());

	ui->show_image->setPixmap(*get_image_pixmap(book.get_path_to_img(), 326, 326));
	ui->show_image->setStyleSheet(STYLE::BACKGROUNG::TRANSPARENT);

	if (book.get_enabled()) 
	{
		ui->show_remove_book_button->setEnabled(true);
		ui->show_remove_book_button->setVisible(true);
		disconnect(ui->show_remove_book_button, 0, 0, 0);
		connect(ui->show_remove_book_button, &QPushButton::clicked, this, 
			[=]() {
			if (QMessageBox::Yes == QMessageBox::question(this, "Apply Remove", "Apply?", QMessageBox::Yes | QMessageBox::No)) 
			{
				Book _book = book;
				books_db->delete_field( DB::BOOKS::FIELD::ID + " = " + QString::fromStdString(to_string(_book.get_id())));
				start();
			} });

		ui->show_edit_book_button->setGeometry(154, 370, 200, 50);
		ui->show_remove_book_button->setGeometry(24, 370, 100, 50);
	}
	else 
	{
		ui->show_remove_book_button->setEnabled(false);
		ui->show_remove_book_button->setVisible(false);
		ui->show_edit_book_button->setGeometry(24, 370, 330, 50);
	}

	ui->show_edit_book_button->setEnabled(true);
	ui->show_edit_book_button->setVisible(true);
	disconnect(ui->show_edit_book_button, 0, 0, 0);
	connect(ui->show_edit_book_button, &QPushButton::clicked, this, [=]() {	open_edit_book_page(book); });

	ui->show_return_book_button->setEnabled(true);
	ui->show_return_book_button->setVisible(true);
	disconnect(ui->show_return_book_button, 0, 0, 0);
	if (book.get_enabled()) 
	{
		ui->show_return_book_button->setText("Give");
		connect(ui->show_return_book_button, &QPushButton::clicked, this, [=]() { open_give_book_page(book); });
	}
	else 
	{
		ui->show_return_book_button->setText("Return");
		connect(ui->show_return_book_button, &QPushButton::clicked, this, [=]() { return_book(book); });
	}

	ui->show_back_to_book_button->setEnabled(true);
	ui->show_back_to_book_button->setVisible(true);

	People people = People::get_people_by_book_id(people_db, book.get_id());
	if (!book.get_enabled()) 
	{
		ui->show_back_user->setVisible(true);
		ui->show_user_name->setVisible(true);
		ui->show_date_of_getting->setVisible(true);
		ui->show_date_of_return->setVisible(true);
		ui->show_user_name->setText(people.get_name());
		ui->show_date_of_getting->setText(book.get_date_of_giving());
		ui->show_date_of_return->setText(book.get_date_of_return());
	}
	else 
	{
		ui->show_back_user->setVisible(false);
		ui->show_user_name->setVisible(false);
		ui->show_date_of_getting->setVisible(false);
		ui->show_date_of_return->setVisible(false);
	}
}

void BookPage::open_give_book_page(Book book) 
{
	ui->stackedWidget_2->setCurrentWidget(ui->giveBookPage);
	ui->giveBook_book_name_label->setText(book.get_name());

	QString date = get_current_format_date();

	ui->giveBook_give_date_input->setText(date);

	disconnect(ui->giveBook_give_button, 0, 0, 0);
	connect(ui->giveBook_give_button, &QPushButton::clicked, this, [=]() { give_book(book); });

	disconnect(ui->giveBook_back_button, 0, 0, 0);
	connect(ui->giveBook_back_button, &QPushButton::clicked, this, [=]() { open_show_book_page(book); });
}

void BookPage::give_book(Book book) 
{
	if (!check_giving())
		return;

	if (QMessageBox::Yes == QMessageBox::question(this, "Give", "Are you shure?", QMessageBox::Yes | QMessageBox::No)) 
	{
		People people;

		vector<int> IDs = people_db->get_ints();
		int min_nonexistent = Page::get_min_nonexist(IDs);

		people.set_id(min_nonexistent);
		people.set_book_id(book.get_id());
		people.set_name(ui->giveBook_name_input->text());
		people.set_phone(ui->giveBook_phone_input->text());
		people.set_address(ui->giveBook_address_input->text());
		people.set_age(ui->giveBook_age_input->text().toInt());
		people.set_sex(ui->giveBook_sex_input->currentIndex());

		book.set_date_of_giving(ui->giveBook_give_date_input->text());
		book.set_date_of_return(ui->giveBook_return_date_input->text());
		book.set_enabled(false);

		people.add_in_db(people_db);
		book.update(books_db);
		open_show_book_page(book);
	}
}

void BookPage::return_book(Book book) 
{
	if (QMessageBox::Yes == QMessageBox::question(this, "Return book", "Apply?", QMessageBox::Yes | QMessageBox::No)) 
	{
		book.set_date_of_giving("");
		book.set_date_of_return("");
		book.set_enabled(true);
		book.update(books_db);

		People people = People::get_people_by_book_id(people_db, book.get_id());

		people_db->delete_field(DB::BOOKS::FIELD::ID + " = " + QString::number(people.get_id()));
		start();
		open_show_book_page(book);
	}
}

void BookPage::open_edit_book_page(Book book) 
{
	ui->stackedWidget->setCurrentWidget(ui->addBookPage);
	clear_creation_fields();
	_check_creation->clear_error_message();

	ui->pushButton_3->setText("Edit book");
	ui->name_create_book_line_edit->setText(book.get_name());
	ui->author_create_book_line_edit->setText(book.get_author_name());
	ui->genre_create_book_line_edit->setCurrentText(book.get_genre());
	ui->year_create_book_line_edit->setText(QString::number(book.get_year()));
	ui->pages_create_book_line_edit->setText(QString::number(book.get_amount_of_page()));
	ui->img_create_book_line_edit->setText(book.get_path_to_img());
	ui->content_create_book_line_edit->setText(book.get_content());
	ui->id_create_book_line_edit->setText(QString::number(book.get_id()));

	disconnect(ui->pushButton_3, 0, 0, 0);
	connect(ui->pushButton_3, &QPushButton::clicked, this, [=]() { edit_book(); });

	disconnect(ui->commandLinkButton_3, 0, 0, 0);
	connect(ui->commandLinkButton_3, &QPushButton::clicked, this, [=]() { start(); open_show_book_page(book); });
}

void BookPage::edit_book() 
{
	if (!check_creation()) 
		return;

	if (QMessageBox::Yes == QMessageBox::question(this, "Apply Confirmation", "Apply?", QMessageBox::Yes | QMessageBox::No)) 
	{
		Book book = Book();

		book.set_id(ui->id_create_book_line_edit->text().toInt());
		book.set_name(ui->name_create_book_line_edit->text());
		book.set_author_name(ui->author_create_book_line_edit->text());
		book.set_genre(ui->genre_create_book_line_edit->currentText());
		book.set_year(ui->year_create_book_line_edit->text().toInt());
		book.set_amount_of_page(ui->pages_create_book_line_edit->text().toInt());
		book.set_content(ui->content_create_book_line_edit->toPlainText());
		book.set_path_to_img(ui->img_create_book_line_edit->text());
		book.set_date_of_giving("");
		book.set_date_of_return("");
		book.set_enabled(true);

		book.update(books_db);
		start();
		open_show_book_page(book);
	}
}

void BookPage::open_book_creation_page() 
{
	ui->stackedWidget->setCurrentWidget(ui->addBookPage);
	ui->pushButton_3->setText("Add book");

	clear_creation_fields();
	_check_creation->clear_error_message();

	int min_nonexistent = Page::get_min_nonexist(books_db->get_ints());

	ui->id_create_book_line_edit->setText(QString::number(min_nonexistent));
	ui->id_create_book_line_edit->setEnabled(false);

	disconnect(ui->commandLinkButton_3, 0, 0, 0);
	connect(ui->commandLinkButton_3, &QPushButton::clicked, this, [=]() { start(); });

	disconnect(ui->pushButton_3, 0, 0, 0);
	connect(ui->pushButton_3, &QPushButton::clicked, this, [=]() { create_book(); });
}

void BookPage::create_book() 
{
	if (!check_creation()) 
		return;
	
	if (QMessageBox::Yes == QMessageBox::question(this, "Add", "Are you shure?", QMessageBox::Yes | QMessageBox::No)) 
	{
		Book book;

		book.set_id(ui->id_create_book_line_edit->text().toInt());
		book.set_name(ui->name_create_book_line_edit->text());
		book.set_author_name(ui->author_create_book_line_edit->text());
		book.set_genre(ui->genre_create_book_line_edit->currentText());
		book.set_year(ui->year_create_book_line_edit->text().toInt());
		book.set_amount_of_page(ui->pages_create_book_line_edit->text().toInt());
		book.set_content(ui->content_create_book_line_edit->toPlainText());
		book.set_path_to_img(ui->img_create_book_line_edit->text());
		book.set_date_of_giving("");
		book.set_date_of_return("");
		book.set_enabled(true);

		book.add_in_db(books_db);
		start();
	}
}

bool BookPage::check_creation() 
{
	QString year = ui->year_create_book_line_edit->text();
	QString pages = ui->pages_create_book_line_edit->text();

	_check_creation->clear_error_message();
	_check_creation->clear_check_list();
	_check_creation->add_error_check({ BOOK_ERROR::WRONG_YEAR, year, regex("([1-9])([0-9]{0,3})") });
	_check_creation->add_error_check({ BOOK_ERROR::WRONG_PAGES, pages, regex("([1-9])([0-9]{0,3})") });

	if (QCheck::is_empty({
		ui->name_create_book_line_edit->text(), 
		ui->author_create_book_line_edit->text(),  
		pages, year,
		ui->content_create_book_line_edit->toPlainText() })) 
	{
		_check_creation->show_error_message(BOOK_ERROR::IS_EMPTY);
		return false;
	}

	int error_code = _check_creation->check_all();
	if (error_code != BOOK_ERROR::ALL_GOOD)
	{
		_check_creation->show_error_message(error_code);
		return false;
	}

	return true;
}

void BookPage::clear_creation_fields() 
{
	ui->name_create_book_line_edit->setText("");
	ui->author_create_book_line_edit->setText("");
	ui->genre_create_book_line_edit->setCurrentIndex(0);
	ui->year_create_book_line_edit->setText("");
	ui->pages_create_book_line_edit->setText("");
	ui->img_create_book_line_edit->setText("");
	ui->content_create_book_line_edit->setText("");
}

void BookPage::init_cheks_messages() 
{
	_check_creation = new QCheck(ui, ui->addBookPage);
	_check_creation->clear_check_list();
	_check_creation->add_error_message({BOOK_ERROR::IS_EMPTY, "All fields should be used", 950, 590, 400, 50});
	_check_creation->add_error_message({ BOOK_ERROR::WRONG_YEAR, "Wrong year", 950, 230, 400, 50 });
	_check_creation->add_error_message({ BOOK_ERROR::WRONG_PAGES, "Wrong pages", 950, 295, 400, 50 });

	_check_giving = new QCheck(ui, ui->giveBookPage);
	_check_giving->clear_check_list();
	_check_giving->add_error_message({PEOPLE_ERROR::IS_EMPTY, "All fields should be used", 490, 600, 400, 50});
	_check_giving->add_error_message({PEOPLE_ERROR::WRONG_NAME, "Wrong name", 490, 110, 400, 50});
	_check_giving->add_error_message({PEOPLE_ERROR::WRONG_PHONE, "Wrong phone", 490, 180, 400, 50});
	_check_giving->add_error_message({PEOPLE_ERROR::WRONG_ADDRESS, "Wrong address", 490, 250, 400, 50});
	_check_giving->add_error_message({PEOPLE_ERROR::WRONG_AGE, "Wrong age", 490, 320, 400, 50});
	_check_giving->add_error_message({PEOPLE_ERROR::WRONG_GIVE_DATE, "Wrong give date", 490, 460, 400, 50});
	_check_giving->add_error_message({PEOPLE_ERROR::WRONG_RETURN_DATE, "Wrong return date", 490, 530, 400, 50});
	_check_giving->add_error_message({PEOPLE_ERROR::GIVE_DATE_MORE_THAN_RETURN_DATE, "Give date more than return date", 490, 530, 400, 50});
}

void BookPage::adjust_fonts() 
{
	ui->name_create_book_line_edit->setFont(FONTS::UBUNTU_12);
	ui->author_create_book_line_edit->setFont(FONTS::UBUNTU_12);
	ui->genre_create_book_line_edit->setFont(FONTS::UBUNTU_12);
	ui->year_create_book_line_edit->setFont(FONTS::UBUNTU_12);
	ui->pages_create_book_line_edit->setFont(FONTS::UBUNTU_12);
	ui->img_create_book_line_edit->setFont(FONTS::UBUNTU_12);
	ui->pushButton_4->setFont(FONTS::UBUNTU_12);
	ui->content_create_book_line_edit->setFont(FONTS::UBUNTU_12);
	ui->pushButton_3->setFont(FONTS::UBUNTU_12);
	ui->commandLinkButton_3->setFont(FONTS::UBUNTU_12);

	ui->show_book_name->setFont(FONTS::UBUNTU_14);
	ui->show_author->setFont(FONTS::UBUNTU_14);
	ui->show_year->setFont(FONTS::UBUNTU_12);
	ui->show_pages->setFont(FONTS::UBUNTU_12);
	ui->show_content->setFont(FONTS::UBUNTU_12);
	ui->show_user_name->setFont(FONTS::UBUNTU_10);
	ui->show_date_of_getting->setFont(FONTS::UBUNTU_10);
	ui->show_date_of_return->setFont(FONTS::UBUNTU_10);
	ui->show_remove_book_button->setFont(FONTS::UBUNTU_12);
	ui->show_edit_book_button->setFont(FONTS::UBUNTU_12);
	ui->show_return_book_button->setFont(FONTS::UBUNTU_12);
	ui->show_back_to_book_button->setFont(FONTS::UBUNTU_10);

	ui->giveBook_book_name_label->setFont(FONTS::UBUNTU_14);
	ui->giveBook_name_input->setFont(FONTS::UBUNTU_12);
	ui->giveBook_phone_input->setFont(FONTS::UBUNTU_12);
	ui->giveBook_address_input->setFont(FONTS::UBUNTU_12);
	ui->giveBook_age_input->setFont(FONTS::UBUNTU_12);
	ui->giveBook_sex_input->setFont(FONTS::UBUNTU_12);
	ui->giveBook_give_date_input->setFont(FONTS::UBUNTU_12);
	ui->giveBook_return_date_input->setFont(FONTS::UBUNTU_12);
	ui->giveBook_give_button->setFont(FONTS::UBUNTU_14);
	ui->giveBook_back_button->setFont(FONTS::UBUNTU_10);

}

int BookPage::check_giving() 
{
	QString name = ui->giveBook_name_input->text();
	QString phone = ui->giveBook_phone_input->text();
	QString address = ui->giveBook_address_input->text();
	QString age = ui->giveBook_age_input->text();
	QString date_of_giving = ui->giveBook_give_date_input->text();
	QString date_of_return = ui->giveBook_return_date_input->text();

	_check_giving->clear_error_message();
	_check_giving->clear_check_list();
	_check_giving->add_error_check({PEOPLE_ERROR::WRONG_NAME, name, regex("^([A-Za-z ]{3,30})")});
	_check_giving->add_error_check({PEOPLE_ERROR::WRONG_PHONE, phone, regex("^(\\+375)(\\([0-9]{2}\\))([0-9]{3})(\\-)([0-9]{2})(\\-)([0-9]{2})")});
	_check_giving->add_error_check({PEOPLE_ERROR::WRONG_ADDRESS, address, regex("^([A-Za-z., ]{5,30})")});
	_check_giving->add_error_check({PEOPLE_ERROR::WRONG_AGE, age, regex("^([1-9])([0-9]{0,1})")});
	_check_giving->add_error_check({PEOPLE_ERROR::WRONG_GIVE_DATE, date_of_giving, regex("^(0[1-9]|[12][0-9]|3[01])\\.(0[1-9]|1[012])\\.([1-9]([0-9]){2,3})")});
	_check_giving->add_error_check({PEOPLE_ERROR::WRONG_RETURN_DATE, date_of_return, regex("^(0[1-9]|[12][0-9]|3[01])\\.(0[1-9]|1[012])\\.([1-9]([0-9]){2,3})")});

	
	if (QCheck::is_empty({name, phone, address, age, date_of_giving, date_of_return}))
	{
		_check_giving->show_error_message(PEOPLE_ERROR::IS_EMPTY);
		return false;
	}
	
	int error_code = _check_giving->check_all();
	if (error_code != PEOPLE_ERROR::ALL_GOOD) 
	{
		_check_giving->show_error_message(error_code);
		return false;
	}
	
	for (int i = date_of_giving.size() - 1; i >= 0; i--) 
	{
		if (date_of_giving[i] > date_of_return[i]) 
		{
			_check_giving->show_error_message(PEOPLE_ERROR::GIVE_DATE_MORE_THAN_RETURN_DATE);
			return false;
		}
	}
	
	return true;
}

void BookPage::open_main_widjet() 
{
	ui->stackedWidget->setCurrentWidget(ui->adminMainPage);
	ui->stackedWidget_2->setCurrentWidget(page);
}


