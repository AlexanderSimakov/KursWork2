#include "PeoplePage.h"

PeoplePage::PeoplePage(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, SQLWork* people_db, SQLWork* book_db) 
	: QMainWindow(parent) 
{
	this->ui = ui;
	this->page = ui->page;
	this->people_db = people_db;
	this->book_db = book_db;
	this->_parent = parent;

	searching = new Searching(_parent, ui, page, people_db, *this, people_id);
}

void PeoplePage::start() 
{
	update_people_id();
	clear_page();
	create_search();
	show_list();
}

void PeoplePage::update_window() {
	show_list();
}

void PeoplePage::update_people_id() 
{
	people_id = people_db->get_ints(0);
}

void PeoplePage::clear_page() 
{
	clear_people_list();
	searching->delete_widgets();
}

void PeoplePage::clear_people_list() 
{
	qDeleteAll(page->findChildren<QLabel*>());
	qDeleteAll(page->findChildren<QPushButton*>("book_return_button"));
	qDeleteAll(page->findChildren<QPushButton*>("book_show_button"));
}

void PeoplePage::show_list() 
{
	clear_people_list();
	create_choise_page_buttons();

	int people_start_at = NUMBER_OF_PEOPLE_ON_PAGE * current_page;
	int people_end_at;

	if (people_id.size() - people_start_at >= NUMBER_OF_PEOPLE_ON_PAGE)
		people_end_at = people_start_at + NUMBER_OF_PEOPLE_ON_PAGE;
	else
		people_end_at = people_id.size();

	int j = 0, k = 0, n = 1;
	for (int i = 0; i < people_end_at - people_start_at; i++) 
	{
		show_people(&get_people_by_id(people_id[i + people_start_at]), j, k);
		if (j == 3) 
		{
			j = -1;
			k++;
		}
		j++;
	}
}

void PeoplePage::show_people(People* people, int row, int column) 
{
	create_back_label(row, column);
	create_back_people_info_label(row, column);
	create_back_book_info_label(row, column);
	create_name_label(people, row, column);
	create_phone_label(people, row, column);
	create_address_label(people, row, column);
	create_age_label(people, row, column);
	create_sex_label(people, row, column);
	create_return_button(*people, row, column);

	Book book = Book::get_book_by_id(book_db, people->get_book_id());
	bool is_overdue = false;
	QString current_data = Page::get_current_format_date();
	QString date_of_return = book.get_date_of_return();
	for (int i = current_data.size() - 1; i >= 0; i--) 
	{
		if (current_data[i] > date_of_return[i]) 
		{
			is_overdue = true;
			break;
		}
	}

	create_book_name_label(&book, row, column);
	create_book_give_date_label(&book, row, column, is_overdue);
	create_book_return_date_label(&book, row, column, is_overdue);
}

void PeoplePage::create_choise_page_buttons() 
{
	choise_page_buttons = new ChoisePageButtons(_parent, ui, page, NUMBER_OF_PEOPLE_ON_PAGE, &current_page, *this);
	choise_page_buttons->set_number_of_elements(people_db->get_count());
	choise_page_buttons->show();
}

void PeoplePage::create_search() 
{
	vector<Search> comm;
	comm.push_back({"Name", " WHERE " + DB::PEOPLE::FIELD::NAME + " GLOB "});
	comm.push_back({"Phone", " WHERE " + DB::PEOPLE::FIELD::PHONE + " GLOB " });
	comm.push_back({"Address", " WHERE " + DB::PEOPLE::FIELD::ADDRESS + " GLOB " });
	comm.push_back({"Age", " WHERE " + DB::PEOPLE::FIELD::AGE + " GLOB " });
	searching->init(comm, &current_page);
	searching->show();
}

void PeoplePage::create_back_label(int row, int column) 
{
	const int WIDTH = 340, HEIGHT = 300, START_X = 10, START_Y = 13;

	QLabel* back = new QLabel("", page);
	back->setStyleSheet(STYLE::BACKGROUNG::CREAM + STYLE::BORDER::SIZE_10 + STYLE::BORDER::RADIUS_10);
	back->setObjectName("peoplePage_back");
	back->setGeometry(START_X + ADD_X * row, START_Y + ADD_Y * column, WIDTH, HEIGHT);
	back->show();
}

void PeoplePage::create_back_people_info_label(int row, int column) 
{
	const int WIDTH = 320, HEIGHT = 130, START_X = 20, START_Y = 25;

	QLabel* back_people = new QLabel("", page);
	back_people->setStyleSheet(STYLE::BACKGROUNG::CREAM + STYLE::BORDER::SIZE_2 + 
		STYLE::BORDER::SOLID + STYLE::BORDER::LITE_CREAM + STYLE::BORDER::RADIUS_10);
	
	back_people->setObjectName("peoplePage_back");
	back_people->setGeometry(START_X + ADD_X * row, START_Y + ADD_Y * column, WIDTH, HEIGHT);
	back_people->show();
}

void PeoplePage::create_back_book_info_label(int row, int column) 
{
	const int WIDTH = 320, HEIGHT = 130, START_X = 20, START_Y = 166;

	QLabel* back_book = new QLabel("", page);
	back_book->setStyleSheet(STYLE::BACKGROUNG::CREAM + STYLE::BORDER::SIZE_2 +
		STYLE::BORDER::SOLID + STYLE::BORDER::LITE_CREAM + STYLE::BORDER::RADIUS_10);

	back_book->setObjectName("peoplePage_back");
	back_book->setGeometry(START_X + ADD_X * row, START_Y + ADD_Y * column, WIDTH, HEIGHT);
	back_book->show();
}

void PeoplePage::create_name_label(People* people, int row, int column) 
{
	const int WIDTH = 180, HEIGHT = 30, START_X = 35, START_Y = 35;
	QLabel* name = new QLabel(people->get_name(), page);
	name->setStyleSheet(STYLE::BACKGROUNG::TRANSPARENT);
	name->setFont(FONTS::UBUNTU_10);
	name->setGeometry(START_X + ADD_X * row, START_Y + ADD_Y * column, WIDTH, HEIGHT);
	name->show();
}

void PeoplePage::create_phone_label(People* people, int row, int column) 
{
	const int WIDTH = 180, HEIGHT = 30, START_X = 35, START_Y = 75;
	QLabel* phone = new QLabel(people->get_phone(), page);
	phone->setStyleSheet(STYLE::BACKGROUNG::TRANSPARENT);
	phone->setFont(FONTS::UBUNTU_10);
	phone->setGeometry(START_X + ADD_X * row, START_Y + ADD_Y * column, WIDTH, HEIGHT);
	phone->show();
}

void PeoplePage::create_address_label(People* people, int row, int column) 
{
	const int WIDTH = 180, HEIGHT = 30, START_X = 35, START_Y = 115;
	QLabel* address = new QLabel(people->get_address(), page);
	address->setStyleSheet(STYLE::BACKGROUNG::TRANSPARENT);
	address->setFont(FONTS::UBUNTU_10);
	address->setGeometry(START_X + ADD_X * row, START_Y + ADD_Y * column, WIDTH, HEIGHT);
	address->show();
}

void PeoplePage::create_age_label(People* people, int row, int column) 
{
	const int WIDTH = 60, HEIGHT = 30, START_X = 275, START_Y = 35;
	QLabel* age = new QLabel("Age: " + QString::number(people->get_age()), page);
	age->setStyleSheet(STYLE::BACKGROUNG::TRANSPARENT);
	age->setFont(FONTS::UBUNTU_10);
	age->setGeometry(START_X + ADD_X * row, START_Y + ADD_Y * column, WIDTH, HEIGHT);
	age->show();
}

void PeoplePage::create_sex_label(People* people, int row, int column) 
{
	const int WIDTH = 55, HEIGHT = 30, START_X = 275, START_Y = 115;

	QString qsex;
	int isex = people->get_sex();
	if (isex == 1)
		qsex = "Male";
	else if (isex == 2)
		qsex = "Female";
	else
		qsex == "Other";

	QLabel* sex = new QLabel(qsex, page);
	sex->setStyleSheet(STYLE::BACKGROUNG::TRANSPARENT);
	sex->setFont(FONTS::UBUNTU_10);
	sex->setGeometry(START_X + ADD_X * row, START_Y + ADD_Y * column, WIDTH, HEIGHT);
	sex->show();
}

void PeoplePage::create_book_name_label(Book* book, int row, int column) 
{
	const int WIDTH = 180, HEIGHT = 30, START_X = 35, START_Y = 175;
	QLabel* book_name = new QLabel(book->get_name(), page);
	book_name->setStyleSheet(STYLE::BACKGROUNG::TRANSPARENT);
	book_name->setFont(FONTS::UBUNTU_10);
	book_name->setGeometry(START_X + ADD_X * row, START_Y + ADD_Y * column, WIDTH, HEIGHT);
	book_name->show();
}

void PeoplePage::create_book_give_date_label(Book* book, int row, int column, bool is_overdue) 
{
	const int WIDTH = 180, HEIGHT = 30, START_X = 35, START_Y = 215;
	QLabel* book_give_date = new QLabel(book->get_date_of_giving(), page);
	
	if (is_overdue)
		book_give_date->setStyleSheet(STYLE::BACKGROUNG::TRANSPARENT + STYLE::COLOR::RED);
	else
		book_give_date->setStyleSheet(STYLE::BACKGROUNG::TRANSPARENT + STYLE::COLOR::DARK_GREEN);
	
	book_give_date->setFont(FONTS::UBUNTU_10);
	book_give_date->setGeometry(START_X + ADD_X * row, START_Y + ADD_Y * column, WIDTH, HEIGHT);
	book_give_date->show();
}

void PeoplePage::create_book_return_date_label(Book* book, int row, int column, bool is_overdue) 
{
	const int WIDTH = 180, HEIGHT = 30, START_X = 35, START_Y = 255;
	QLabel* book_return_date = new QLabel(book->get_date_of_return(), page);

	if (is_overdue)
		book_return_date->setStyleSheet(STYLE::BACKGROUNG::TRANSPARENT + STYLE::COLOR::RED);
	else
		book_return_date->setStyleSheet(STYLE::BACKGROUNG::TRANSPARENT + STYLE::COLOR::DARK_GREEN);

	book_return_date->setFont(FONTS::UBUNTU_10);
	book_return_date->setGeometry(START_X + ADD_X * row, START_Y + ADD_Y * column, WIDTH, HEIGHT);
	book_return_date->show();
}

void PeoplePage::create_return_button(People people, int row, int column) 
{
	const int WIDTH = 62, HEIGHT = 124, START_X = 275, START_Y = 169;
	QPushButton* return_btn = new QPushButton("Return", page);
	return_btn->setObjectName("book_return_button");
	return_btn->setFont(FONTS::UBUNTU_10);
	
	return_btn->setStyleSheet("QPushButton#book_return_button{ " + STYLE::BACKGROUNG::PURPLE + 
		STYLE::BORDER::SIZE_10 + STYLE::BORDER::RADIUS_5 + STYLE::COLOR::WHITE + " } " +
		"QPushButton#book_return_button:hover{ " + STYLE::BACKGROUNG::LIGHT_PURPLR + " }");

	return_btn->setGeometry(START_X + ADD_X * row, START_Y + ADD_Y * column, WIDTH, HEIGHT);
	connect(return_btn, &QPushButton::clicked, this, [=]() { return_book(people); });
	return_btn->show();
}

void PeoplePage::return_book(People people) 
{
	if (QMessageBox::Yes == QMessageBox::question(this, "Apply Return", "Apply?", QMessageBox::Yes | QMessageBox::No)) 
	{
		Book book = Book::get_book_by_id(book_db, people.get_book_id());
		book.set_date_of_giving("");
		book.set_date_of_return("");
		book.set_enabled(true);
		book.update(book_db);

		people_db->delete_field(DB::PEOPLE::FIELD::ID + " = " + QString::fromStdString(to_string(people.get_id())));
		start();
	}
}

People PeoplePage::get_people_by_id(int id) 
{
	People people;
	QString q_id = QString::number(id);

	people.set_id(id);
	people.set_book_id(people_db->get_int(DB::PEOPLE::FIELD::ID, q_id, 1));
	people.set_name(people_db->get_text(DB::PEOPLE::FIELD::ID, q_id, 2));
	people.set_phone(people_db->get_text(DB::PEOPLE::FIELD::ID, q_id, 3));
	people.set_address(people_db->get_text(DB::PEOPLE::FIELD::ID, q_id, 4));
	people.set_age(people_db->get_int(DB::PEOPLE::FIELD::ID, q_id, 5));
	people.set_sex(people_db->get_int(DB::PEOPLE::FIELD::ID, q_id, 6));

	return people;
}

