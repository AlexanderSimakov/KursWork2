#include "Searching.h"

Searching::Searching(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, QWidget* page, SQLWork* db, Page& _page, vector<int>& id)
	: QMainWindow(parent), _page(_page), id(id) {
	this->page = page;
	this->db = db;
}

void Searching::delete_widgets() {
	qDeleteAll(page->findChildren<QPushButton*>(QString::fromStdString("Search_button")));
	qDeleteAll(page->findChildren<QLineEdit*>(QString::fromStdString("Search_field")));
	qDeleteAll(page->findChildren<QComboBox*>(QString::fromStdString("Search_method")));
}

void Searching::init(vector<Search> search_commands, int* current_page) {
	this->search_commands = search_commands;
	this->current_page = current_page;
	create_search_button();
	create_search_field();
	crete_search_choise_method_button();
}

void Searching::clear_field() {
	lineEdit->setText("");
}

void Searching::show() {
	combo_box->show();
	button->show();
	lineEdit->show();
}

void Searching::set_default_search_method() {
	combo_box->setCurrentIndex(0);
}

void Searching::create_search_button() {
	const int X = 760, Y = 650, WIDTH = 80, HEIGHT = 40;
	button = new QPushButton("Search", page);
	button->setObjectName("Search_button");
	button->setFont(FONTS::UBUNTU_10);
	button->setStyleSheet("QPushButton#Search_button{ " +
		STYLE::BACKGROUNG::BLUE + 
		STYLE::BORDER::SIZE_10 +
		STYLE::BORDER::RADIUS_10 +
		STYLE::ALIGN::RIGHT +
		STYLE::PADDING::RIGHT_10 +
		STYLE::COLOR::WHITE + " } " + 
		" \n " +
		"QPushButton#Search_button:hover{ " + STYLE::BACKGROUNG::LIGHT_BLUE + " }");
	button->setGeometry(X, Y, WIDTH, HEIGHT);
	connect(button, &QPushButton::clicked, this,
		[=]() {
			*current_page = 0;
			string current_command = search_commands[combo_box->currentIndex()].command;
			id = db->get_ints(0, current_command + " '" + lineEdit->text().toStdString() + "' ");
			_page.update_window();
		});
}

void Searching::create_search_field() {
	const int X = 470, Y = 650, WIDTH = 300, HEIGHT = 40;
	lineEdit = new QLineEdit(page);
	lineEdit->setObjectName("Search_field");
	lineEdit->setFont(FONTS::UBUNTU_10);
	lineEdit->setStyleSheet(STYLE::BORDER::SIZE_2 +
		STYLE::BACKGROUNG::CREAM +
		STYLE::PADDING::LEFT_10);
	lineEdit->setGeometry(X, Y, WIDTH, HEIGHT);
}

void Searching::crete_search_choise_method_button() {
	const int X = 370, Y = 650, WIDTH = 100, HEIGHT = 40;
	combo_box = new QComboBox(page);
	combo_box->setObjectName("Search_method");
	combo_box->setFont(QFont(FONTS::UBUNTU_10));
	combo_box->setStyleSheet(STYLE::BORDER::SIZE_2 +
		STYLE::BACKGROUNG::CREAM +
		STYLE::BORDER::RADIUS_10 +
		STYLE::PADDING::LEFT_10);
	for (int i = 0; i < search_commands.size(); i++) {
		combo_box->addItem(search_commands[i].name.c_str());
	}
	combo_box->setGeometry(X, Y, WIDTH, HEIGHT);
}



