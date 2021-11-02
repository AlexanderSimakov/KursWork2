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

	connect(ui->edit_book_push_button, &QPushButton::clicked, this, 
		[=]() { 
			ui->edit_book_push_button->disconnect();
			edit_book(); 
		});

	connect(ui->pushButton_4, &QPushButton::clicked, this, 
		[=]() {
			ui->pushButton_4->disconnect();
			QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), "/home", ("Images (*.png *.jpg)"));
			ui->img_create_book_line_edit->setText(fileName);
		});

	connect(ui->open_image_edit_push_button, &QPushButton::clicked, this,
		[=]() {
			ui->open_image_edit_push_button->disconnect();
			QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), "/home", ("Images (*.png *.jpg)"));
			ui->img_edit_book_line_edit_2->setText(fileName);
		});
}

void BookPage::start() {
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
	//qDeleteAll(page->findChildren<QWidget*>());
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
	name->setStyleSheet(" background: #FFE2B9; margin: 2px; border-radius: 10px;");
	name->setFont(QFont("Arial", 10));


	//  --------------- create image label ---------------
	QLabel* image = new QLabel("", page);
	image->setStyleSheet("border-radius: 10px;");
	QPixmap pixmap = QPixmap(QString::fromStdString(book.get_path_to_img()));
	pixmap = pixmap.scaled(QSize(320, 240), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	image->setPixmap(pixmap);


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
	comm.push_back({ "Name", " WHERE NAME GLOB " });
	comm.push_back({ "Author", " WHERE AUTHOR_NAME GLOB " });
	comm.push_back({ "Year", " WHERE YEAR GLOB " });
	comm.push_back({ "Genre", " WHERE GENRE GLOB " });
	comm.push_back({ "Pages", " WHERE AMOUNT_OF_PAGE GLOB " });
	comm.push_back({ "Content", " WHERE CONTENT GLOB " });
	searching->init(comm, &current_page);
	searching->show();
}

void BookPage::create_add_button() {
	const int X = 920, Y = 650, WIDTH = 145, HEIGHT = 40;
	const string BUTTON_TEXT = "Add new";

	QPushButton* add_button = new QPushButton(QString::fromStdString(BUTTON_TEXT), page);
	add_button->setGeometry(X, Y, WIDTH, HEIGHT);
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

	QPixmap pixmap = QPixmap(QString::fromStdString(book.get_path_to_img()));
	pixmap = pixmap.scaled(QSize(326, 326), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	ui->show_image->setAlignment(Qt::AlignCenter);
	ui->show_image->setPixmap(pixmap);
	

	ui->show_remove_book_button->setEnabled(true);
	ui->show_remove_book_button->setVisible(true);
	disconnect(ui->show_remove_book_button, 0, 0, 0);
	connect(ui->show_remove_book_button, &QPushButton::clicked, this, [=]() { 
		Book _book = book;
		QMessageBox::question(this, "Apply Remove", "Apply?", QMessageBox::Yes | QMessageBox::No);
		books_db->delete_field("ID = " + to_string(_book.get_id()));
	});

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

	disconnect(ui->giveBook_give_button, 0, 0, 0);
	connect(ui->giveBook_give_button, &QPushButton::clicked, this, [=]() {
		give_book(book);
		});
}

void BookPage::give_book(Book book) {
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
}

void BookPage::return_book(Book book) {
	book.set_date_of_giving("");
	book.set_date_of_return("");
	book.set_enabled(true);
	book.update(books_db);

	People people = People::get_people_by_book_id(people_db, book.get_id());

	people_db->delete_field("ID = " + to_string(people.get_id()));
	start();
	open_show_book_page(book);
}

void BookPage::open_edit_book_page(Book book) {
	ui->stackedWidget->setCurrentWidget(ui->addBookPage);
	
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
}

void BookPage::edit_book() {
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
	}
}

void BookPage::open_book_creation_page() {
	ui->stackedWidget->setCurrentWidget(ui->addBookPage);
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

	disconnect(ui->pushButton_3, 0, 0, 0);
	connect(ui->pushButton_3, &QPushButton::clicked, this,
		[=]() {
			ui->pushButton_3->disconnect();
			create_book();
		});

}

void BookPage::create_book() {
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
	open_book_creation_page();
}




