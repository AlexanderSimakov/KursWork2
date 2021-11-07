#include "BookPage.h"

BookPage::BookPage(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, SQLWork* books_db, SQLWork* people_db)
	: QMainWindow(parent), PAGE_WIDTH(ui->page_3->width()), PAGE_HEIGHT(ui->page_3->height()) {
	this->_parent = parent;
	this->ui = ui;
	this->page = ui->page_3;
	this->books_db = books_db;
	this->people_db = people_db;

	choise_page_buttons = new ChoisePageButtons(_parent, ui, page, NUMBER_OF_BOOKS_ON_PAGE, &current_page, *this);
	searching = new Searching(_parent, ui, page, books_db, *this, books_id);
	ui->id_create_book_line_edit->setVisible(false);

	adjust_fonts();


	connect(ui->pushButton_4, &QPushButton::clicked, this, 
		[=]() {
			ui->pushButton_4->disconnect();
			QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), "/home", ("Images (*.png *.jpg)"));
			ui->img_create_book_line_edit->setText(fileName);
		});
}

void BookPage::start() {
	ui->stackedWidget->setCurrentWidget(ui->adminMainPage);
	ui->stackedWidget_2->setCurrentWidget(ui->page_3);
	update_books_id();
	clear_page();
	create_add_button();
	create_search();

	show_list();
}

void BookPage::update_books_id() {
	books_id = books_db->get_ints();
}

void BookPage::clear_page() {
	clear_book_list();
	searching->delete_widgets();
	qDeleteAll(page->findChildren<QPushButton*>(QString::fromStdString("BookPage_add_button")));
}

void BookPage::clear_book_list() {
	qDeleteAll(page->findChildren<QLabel*>());
	qDeleteAll(page->findChildren<QPushButton*>(QString::fromStdString("choise_page_button")));
	qDeleteAll(page->findChildren<QPushButton*>(QString::fromStdString("BookPage_btn")));
}

void BookPage::show_list(){
	clear_book_list();
	create_choise_page_buttons();

	int books_start_at = NUMBER_OF_BOOKS_ON_PAGE * current_page;
	int books_end_at;

	if (books_id.size() - books_start_at >= NUMBER_OF_BOOKS_ON_PAGE)
		books_end_at = books_start_at + NUMBER_OF_BOOKS_ON_PAGE;
	else
		books_end_at = books_id.size();

	int j = 0, k = 0, n = 1;
	for (int i = 0; i < books_end_at - books_start_at; i++) {
		show_book(Book::get_book_by_id(books_db, books_id[i + books_start_at]), j, k);
		if (j == 3) {
			j = -1;
			k++;
		}
		j++;
	}
}

void BookPage::show_book(Book book, int row, int column) {
	const int WIDTH = 340, HEIGHT = 300, START_X = 10, START_Y = 13;

	//  --------------- create name label ----------------
	QLabel* name = new QLabel(QString::fromStdString(book.get_name()), page);
	name->setObjectName("BookPage_name");
	name->setStyleSheet(" background: #FFE2B9; border-radius: 10px;");
	name->setAlignment(Qt::AlignCenter);
	name->setFont(FONTS::UBUNTU_10);


	//  --------------- create image label ---------------
	QLabel* image = new QLabel("", page);
	image->setStyleSheet("background: transparent;");

	QPixmap target = QPixmap(QSize(320, 240));
    target.fill(Qt::transparent);

    QPixmap p = QPixmap(QString::fromStdString(book.get_path_to_img()));
    p = p.scaled(QSize(320, 240), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPainter painter (&target);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);


    QPainterPath path = QPainterPath();
	int start_x = (320 - p.size().width()) / 2;
	int start_y = (240 - p.size().height()) / 2;
    path.addRoundedRect(start_x, start_y, p.size().width(), p.size().height(), 10, 10);
    painter.setClipPath(path);
    painter.drawPixmap(start_x, start_y, p);

	image->setPixmap(target);
	// ---------------------------------------------------

	//  --------------- create button --------------------
	QPushButton* button = new QPushButton(page);
	button->setGeometry(START_X + ADD_X * row, START_Y + ADD_Y * column, WIDTH, HEIGHT);
	button->setLayout(new QGridLayout);
	button->setObjectName("BookPage_btn");
	if (book.get_enabled()) {
		button->setStyleSheet("QPushButton#BookPage_btn{ background-color: #FFD69C; border-style: solid; border-width: 2px; border-radius: 10px; border-color: #7fbf52 }"
			" \n "
			"QPushButton#BookPage_btn:hover{ background: #FFE2B9; }");
	}
	else {
		button->setStyleSheet("QPushButton#BookPage_btn{ background-color: #FFD69C; border-style: solid; border-width: 2px; border-radius: 10px; border-color: #f5685d }"
			" \n "
			"QPushButton#BookPage_btn:hover{ background: #FFE2B9; }");
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

void BookPage::create_choise_page_buttons() {
	choise_page_buttons->set_number_of_elements(books_id.size());
	choise_page_buttons->show();
}

void BookPage::create_search() {
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

void BookPage::create_add_button() {
	const int X = 920, Y = 650, WIDTH = 145, HEIGHT = 40;
	const string BUTTON_TEXT = "Add new";

	QPushButton* add_button = new QPushButton(QString::fromStdString(BUTTON_TEXT), page);
	add_button->setGeometry(X, Y, WIDTH, HEIGHT);
	add_button->setFont(FONTS::UBUNTU_10);
	add_button->setObjectName("BookPage_add_button");
	add_button->setStyleSheet("QPushButton#BookPage_add_button { background: #AEFF75; border-radius: 10px; } QPushButton#BookPage_add_button::hover { background: #c1ff96; }");
	connect(add_button, &QPushButton::clicked, this, 
		[=]() {
			open_book_creation_page();
		});
	add_button->show();
}

void BookPage::create_edit_button(Book book, int num_in_list) {
	const int WIDTH = 100, HEIGHT = 33;
	QPushButton* edit_btn = new QPushButton("edit", page);
	edit_btn->setObjectName(QString("book_edit_button"));
	edit_btn->setFont(FONTS::UBUNTU_10);
	edit_btn->setGeometry(PAGE_WIDTH - WIDTH, HEIGHT + MARGIN + ADD * num_in_list, WIDTH, HEIGHT);
	connect(edit_btn, &QPushButton::clicked, this, [=]() { open_show_book_page(book); });
	edit_btn->show();
}

void BookPage::open_show_book_page(Book book) {
	ui->stackedWidget_2->setCurrentWidget(ui->showBookPage);

	ui->show_book_name->setText(QString::fromStdString(book.get_name()));
	ui->show_author->setText(QString::fromStdString(book.get_author_name()));
	ui->show_year->setText(QString::fromStdString(to_string(book.get_year())));
	ui->show_pages->setText(QString::fromStdString(to_string(book.get_amount_of_page())));
	ui->show_content->setText(QString::fromStdString(book.get_content()));


	//  --------------- create image label ---------------
	ui->show_image->setStyleSheet("background: transparent;");

	QPixmap target = QPixmap(QSize(326, 326));
	target.fill(Qt::transparent);

	QPixmap p = QPixmap(QString::fromStdString(book.get_path_to_img()));
	p = p.scaled(QSize(326, 326), Qt::KeepAspectRatio, Qt::SmoothTransformation);

	QPainter painter(&target);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);


	QPainterPath path = QPainterPath();
	int start_x = (326 - p.size().width()) / 2;
	int start_y = (326 - p.size().height()) / 2;
	path.addRoundedRect(start_x, start_y, p.size().width(), p.size().height(), 10, 10);
	painter.setClipPath(path);
	painter.drawPixmap(start_x, start_y, p);

	ui->show_image->setPixmap(target);
	// ---------------------------------------------------
	

	if (book.get_enabled()) {
		ui->show_remove_book_button->setEnabled(true);
		ui->show_remove_book_button->setVisible(true);
		disconnect(ui->show_remove_book_button, 0, 0, 0);
		connect(ui->show_remove_book_button, &QPushButton::clicked, this, [=]() {
			if (QMessageBox::Yes == QMessageBox::question(this, "Apply Remove", "Apply?", QMessageBox::Yes | QMessageBox::No)) {
				Book _book = book;
				books_db->delete_field( DB::BOOKS::FIELD::ID + " = " + to_string(_book.get_id()));
				start();
			}
			});

		ui->show_edit_book_button->setGeometry(154, 370, 200, 50);
		ui->show_remove_book_button->setGeometry(24, 370, 100, 50);
	}
	else {
		ui->show_remove_book_button->setEnabled(false);
		ui->show_remove_book_button->setVisible(false);

		ui->show_edit_book_button->setGeometry(24, 370, 330, 50);
		
	}

	ui->show_edit_book_button->setEnabled(true);
	ui->show_edit_book_button->setVisible(true);
	disconnect(ui->show_edit_book_button, 0, 0, 0);
	connect(ui->show_edit_book_button, &QPushButton::clicked, this, [=]() {
		open_edit_book_page(book);
	});

	ui->show_return_book_button->setEnabled(true);
	ui->show_return_book_button->setVisible(true);
	disconnect(ui->show_return_book_button, 0, 0, 0);
	if (book.get_enabled()) {
		ui->show_return_book_button->setText("Give");
		connect(ui->show_return_book_button, &QPushButton::clicked, this, [=]() {
			open_give_book_page(book);
		});
	}
	else {
		ui->show_return_book_button->setText("Return");
		connect(ui->show_return_book_button, &QPushButton::clicked, this, [=]() {
			return_book(book);
			});
	}

	ui->show_back_to_book_button->setEnabled(true);
	ui->show_back_to_book_button->setVisible(true);

	People people = People::get_people_by_book_id(people_db, book.get_id());

	if (!book.get_enabled()) {
		ui->show_back_user->setVisible(true);
		ui->show_user_name->setVisible(true);
		ui->show_date_of_getting->setVisible(true);
		ui->show_date_of_return->setVisible(true);
		ui->show_user_name->setText(QString::fromStdString(people.get_name()));
		ui->show_date_of_getting->setText(QString::fromStdString(book.get_date_of_giving()));
		ui->show_date_of_return->setText(QString::fromStdString(book.get_date_of_return()));
	}
	else {
		ui->show_back_user->setVisible(false);
		ui->show_user_name->setVisible(false);
		ui->show_date_of_getting->setVisible(false);
		ui->show_date_of_return->setVisible(false);
	}

	
}

void BookPage::open_give_book_page(Book book) {
	ui->stackedWidget_2->setCurrentWidget(ui->giveBookPage);
	ui->giveBook_book_name_label->setText(QString::fromStdString(book.get_name()));

	time_t now = time(0);
	tm* ltm = localtime(&now);

	QString day;
	QString month;

	int day_i = ltm->tm_mday;
	if (day_i < 10) 
		day = QString(QString::fromStdString("0" + to_string(day_i)));
	else 
		day = QString(QString::fromStdString(to_string(day_i)));

	int month_i = 1 + ltm->tm_mon;
	if (month_i < 10)
		month = QString(QString::fromStdString("0" + to_string(month_i)));
	else
		month = QString(QString::fromStdString(to_string(month_i)));

	QString year(QString::fromStdString(to_string(1900 + ltm->tm_year)));



	ui->giveBook_give_date_input->setText(day + "." + month + "." + year);

	disconnect(ui->giveBook_give_button, 0, 0, 0);
	connect(ui->giveBook_give_button, &QPushButton::clicked, this, [=]() {
		give_book(book);
		});

	disconnect(ui->giveBook_back_button, 0, 0, 0);
	connect(ui->giveBook_back_button, &QPushButton::clicked, this, [=]() {
		open_show_book_page(book);
		});
}

void BookPage::give_book(Book book) {
	clear_give_error();
	int error_code = check_giving();
	if (error_code == 0) {
		show_give_error("All fields should be used", 7);
		return;
	}
	else if (error_code == -1) {
		show_give_error("Wrong name", 0);
		return;
	}
	else if (error_code == -2) {
		show_give_error("Wrong phone", 1);
		return;
	}
	else if (error_code == -3) {
		show_give_error("Wrong address", 2);
		return;
	}
	else if (error_code == -4) {
		show_give_error("Wrong age", 3); 
		return;
	}
	else if (error_code == -5) {
		show_give_error("Wrong give date", 5); 
		return;
	}
	else if (error_code == -6) {
		show_give_error("Wrong return date", 6);
		return;
	}
	else if (error_code == -7) {
		show_give_error("Return date should be more than give date", 6);
		return;
	}
	

	if (QMessageBox::Yes == QMessageBox::question(this, "Give", "Are you shure?", QMessageBox::Yes | QMessageBox::No)) {
		People people;

		vector<int> IDs = people_db->get_ints();
		int min_nonexistent = 1;

		if (IDs.size() != 0) {
			for (int i = 0; i < *max_element(IDs.begin(), IDs.end()) + 2; i++) {
				if (IDs.end() == std::find(IDs.begin(), IDs.end(), min_nonexistent)) {
					break;
				}
				min_nonexistent++;
			}
		}

		people.set_id(min_nonexistent);
		people.set_book_id(book.get_id());
		people.set_name(ui->giveBook_name_input->text().toStdString());
		people.set_phone(ui->giveBook_phone_input->text().toStdString());
		people.set_address(ui->giveBook_address_input->text().toStdString());
		people.set_age(ui->giveBook_age_input->text().toInt());
		people.set_sex(ui->giveBook_sex_input->currentIndex());

		book.set_date_of_giving(ui->giveBook_give_date_input->text().toStdString());
		book.set_date_of_return(ui->giveBook_return_date_input->text().toStdString());
		book.set_enabled(false);

		people.add_in_db(people_db);
		book.update(books_db);
		open_show_book_page(book);
	}
}

void BookPage::return_book(Book book) {
	if (QMessageBox::Yes == QMessageBox::question(this, "Return book", "Apply?", QMessageBox::Yes | QMessageBox::No)) {
		book.set_date_of_giving("");
		book.set_date_of_return("");
		book.set_enabled(true);
		book.update(books_db);

		People people = People::get_people_by_book_id(people_db, book.get_id());

		people_db->delete_field(DB::BOOKS::FIELD::ID + " = " + to_string(people.get_id()));
		start();
		open_show_book_page(book);
	}
}

void BookPage::open_edit_book_page(Book book) {
	ui->stackedWidget->setCurrentWidget(ui->addBookPage);
	clear_creation_fields();
	clear_creation_error();

	ui->pushButton_3->setText("Edit book");
	
	ui->name_create_book_line_edit->setText(QString::fromStdString(book.get_name()));
	ui->author_create_book_line_edit->setText(QString::fromStdString(book.get_author_name()));
	ui->genre_create_book_line_edit->setCurrentText(QString::fromStdString(book.get_genre()));
	ui->year_create_book_line_edit->setText(QString::fromStdString(to_string(book.get_year())));
	ui->pages_create_book_line_edit->setText(QString::fromStdString(to_string(book.get_amount_of_page())));
	ui->img_create_book_line_edit->setText(QString::fromStdString(book.get_path_to_img()));
	ui->content_create_book_line_edit->setText(QString::fromStdString(book.get_content()));
	ui->id_create_book_line_edit->setText(QString::fromStdString(to_string(book.get_id())));

	disconnect(ui->pushButton_3, 0, 0, 0);
	connect(ui->pushButton_3, &QPushButton::clicked, this, [=]() {
		edit_book();
		});

	disconnect(ui->commandLinkButton_3, 0, 0, 0);
	connect(ui->commandLinkButton_3, &QPushButton::clicked, this, [=]() {
		start();
		open_show_book_page(book);
		});
}

void BookPage::edit_book() {
	clear_creation_error();
	int error_code = check_creation();
	if (error_code == 0) {
		show_creation_error("All fields should be used", 8.5);
		return reconnect_create_button();
	}
	else if (error_code == -1) {
		show_creation_error("Wrong year", 3);
		return reconnect_create_button();
	}
	else if (error_code == -2) {
		show_creation_error("Wrong pages", 4);
		return reconnect_create_button();
	}

	if (QMessageBox::Yes == QMessageBox::question(this, "Apply Confirmation", "Apply?", QMessageBox::Yes | QMessageBox::No)) {
		Book book = Book();

		book.set_id(ui->id_create_book_line_edit->text().toInt());
		book.set_name(ui->name_create_book_line_edit->text().toStdString());
		book.set_author_name(ui->author_create_book_line_edit->text().toStdString());
		book.set_genre(ui->genre_create_book_line_edit->currentText().toStdString());
		book.set_year(ui->year_create_book_line_edit->text().toInt());
		book.set_amount_of_page(ui->pages_create_book_line_edit->text().toInt());
		book.set_content(ui->content_create_book_line_edit->toPlainText().toStdString());
		book.set_path_to_img(ui->img_create_book_line_edit->text().toStdString());
		book.set_date_of_giving("");
		book.set_date_of_return("");
		book.set_enabled(true);

		book.update(books_db);
		start();
		open_show_book_page(book);
	}
}

void BookPage::open_book_creation_page() {
	ui->stackedWidget->setCurrentWidget(ui->addBookPage);
	ui->pushButton_3->setText("Add book");

	clear_creation_fields();
	clear_creation_error();

	vector<int> IDs = books_db->get_ints();
	int min_nonexistent = 1;

	if (IDs.size() != 0) {
		for (int i = 0; i < *max_element(IDs.begin(), IDs.end()) + 2; i++) {
			if (IDs.end() == std::find(IDs.begin(), IDs.end(), min_nonexistent)) {
				break;
			}
			min_nonexistent++;
		}
	}

	ui->id_create_book_line_edit->setText(QString::fromStdString(to_string(min_nonexistent)));
	ui->id_create_book_line_edit->setEnabled(false);

	disconnect(ui->commandLinkButton_3, 0, 0, 0);
	connect(ui->commandLinkButton_3, &QPushButton::clicked, this, [=]() {
		start();
		});

	reconnect_create_button();
}

void BookPage::create_book() {
	clear_creation_error();
	int error_code = check_creation();
	if (error_code == 0) {
		show_creation_error("All fields should be used", 8.5);
		return reconnect_create_button();
	} else if (error_code == -1) {
		show_creation_error("Wrong year", 3);
		return reconnect_create_button();
	} else if (error_code == -2) {
		show_creation_error("Wrong pages", 4);
		return reconnect_create_button();
	}

	if (QMessageBox::Yes == QMessageBox::question(this, "Add", "Are you shure?", QMessageBox::Yes | QMessageBox::No)) {
		Book book;

		book.set_id(ui->id_create_book_line_edit->text().toInt());
		book.set_name(ui->name_create_book_line_edit->text().toStdString());
		book.set_author_name(ui->author_create_book_line_edit->text().toStdString());
		book.set_genre(ui->genre_create_book_line_edit->currentText().toStdString());
		book.set_year(ui->year_create_book_line_edit->text().toInt());
		book.set_amount_of_page(ui->pages_create_book_line_edit->text().toInt());
		book.set_content(ui->content_create_book_line_edit->toPlainText().toStdString());
		book.set_path_to_img(ui->img_create_book_line_edit->text().toStdString());
		book.set_date_of_giving("");
		book.set_date_of_return("");
		book.set_enabled(true);

		book.add_in_db(books_db);
		start();
	}
}

/*
 1 - все хорошо
 0 - есть незаполненные поля
-1 - неправильный год
-2 - неправилные страницы
*/
int BookPage::check_creation() {
	cmatch result;
	regex regular_year("([1-9])([0-9]{0,3})"); 
	regex regular_pages("([1-9])([0-9]{0,3})");
	string year = ui->year_create_book_line_edit->text().toStdString();
	string pages = ui->pages_create_book_line_edit->text().toStdString();

	if (ui->name_create_book_line_edit->text() == "" ||
		ui->author_create_book_line_edit->text() == "" ||
		ui->year_create_book_line_edit->text() == "" ||
		ui->pages_create_book_line_edit->text() == "" ||
		ui->content_create_book_line_edit->toPlainText().toStdString() == "") {
		return 0;
	}
	else if (!regex_match(year.c_str(), result, regular_year)) {
		return -1;
	}
	else  if (!regex_match(pages.c_str(), result, regular_pages)) {
		return -2;
	}

	return 1;
}

void BookPage::show_creation_error(string message, double num_of_line) {
	const int START_X = 900, START_Y = 35, ADD = 65, WIDTH = 400, HEIGHT = 50;
	QLabel* error_message = new QLabel(QString::fromStdString(message), ui->addBookPage);
	error_message->setObjectName("BookPage_creation_error");
	error_message->setStyleSheet("color: #f5685d");
	error_message->setFont(FONTS::UBUNTU_12);
	error_message->setGeometry(START_X, START_Y + (ADD * num_of_line), WIDTH, HEIGHT);
	error_message->show();
}

void BookPage::show_give_error(string message, double num_of_line) {
	const int START_X = 490, START_Y = 110, ADD = 70, WIDTH = 400, HEIGHT = 50;
	QLabel* error_message = new QLabel(QString::fromStdString(message), ui->giveBookPage);
	error_message->setObjectName("BookPage_give_error");
	error_message->setStyleSheet("color: #f5685d");
	error_message->setFont(FONTS::UBUNTU_12);
	error_message->setGeometry(START_X, START_Y + (ADD * num_of_line), WIDTH, HEIGHT);
	error_message->show();
}

void BookPage::clear_creation_error() {
	qDeleteAll(ui->addBookPage->findChildren<QLabel*>(QString::fromStdString("BookPage_creation_error")));
}

void BookPage::clear_give_error() {
	qDeleteAll(ui->giveBookPage->findChildren<QLabel*>(QString::fromStdString("BookPage_give_error")));
}

void BookPage::clear_creation_fields() {
	ui->name_create_book_line_edit->setText("");
	ui->author_create_book_line_edit->setText("");
	ui->genre_create_book_line_edit->setCurrentIndex(0);
	ui->year_create_book_line_edit->setText("");
	ui->pages_create_book_line_edit->setText("");
	ui->img_create_book_line_edit->setText("");
	ui->content_create_book_line_edit->setText("");
}

void BookPage::reconnect_create_button() {
	disconnect(ui->pushButton_3, 0, 0, 0);
	connect(ui->pushButton_3, &QPushButton::clicked, this,
		[=]() {
			ui->pushButton_3->disconnect();
			create_book();
		});
}

void BookPage::adjust_fonts() {
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

	// show book page
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

	// add book page
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

/*
 1 - все хорошо
 0 - есть незаполненные поля
-1 - неправильное имя
-2 - неправильный телефон
-3 - неправильный адрес
-4 - неправильный возраст
-5 - неправильныя дата выдачи
-6 - неправильная дата возвращения
-7 - дата возвращения меньше или равна дате выдачи
*/
int BookPage::check_giving() {
	cmatch result;
	regex regular_name("^([A-Za-z ]{3,30})");
	regex regular_phone("^(\\+375)(\\([0-9]{2}\\))([0-9]{3})(\\-)([0-9]{2})(\\-)([0-9]{2})");
	regex regular_address("^([A-Za-z., ]{5,30})");
	regex regular_age("^([1-9])([0-9]{0,1})");
	regex regular_give_date("^(0[1-9]|[12][0-9]|3[01])\\.(0[1-9]|1[012])\\.([1-9]([0-9]){2,3})");
	regex regular_return_date("^(0[1-9]|[12][0-9]|3[01])\\.(0[1-9]|1[012])\\.([1-9]([0-9]){2,3})");


	string name = ui->giveBook_name_input->text().toStdString();
	string phone = ui->giveBook_phone_input->text().toStdString();
	string address = ui->giveBook_address_input->text().toStdString();
	string age = ui->giveBook_age_input->text().toStdString();
	string date_of_giving = ui->giveBook_give_date_input->text().toStdString();
	string date_of_return = ui->giveBook_return_date_input->text().toStdString();

	if (name == "" || phone == "" || address == "" || age == "" || date_of_giving == "" || date_of_return == "") {
		return 0;
	}
	else if (!regex_match(name.c_str(), result, regular_name)) {
		return -1;
	}
	else  if (!regex_match(phone.c_str(), result, regular_phone)) {
		return -2;
	}
	else  if (!regex_match(address.c_str(), result, regular_address)) {
		return -3;
	}
	else  if (!regex_match(age.c_str(), result, regular_age)) {
		return -4;
	}
	else  if (!regex_match(date_of_giving.c_str(), result, regular_give_date)) {
		return -5;
	}
	else  if (!regex_match(date_of_return.c_str(), result, regular_return_date)) {
		return -6;
	}
	else{
		for (int i = date_of_giving.size() - 1; i >= 0; i--) {
			if (date_of_giving[i] > date_of_return[i]) {
				return -7;
			}
		}
	}

	return 1;
}




