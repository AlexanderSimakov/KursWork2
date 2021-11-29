#pragma once
#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include "ui_QtWidgetsApplication1.h"
#include "SQLWORK.h"
#include "Book.h"
#include "People.h"
#include "Page.h"
#include "ChoisePageButtons.h"
#include "Searching.h"
#include "constants.h"
#include <regex>
#include <ctime>
#include "Check.h"

namespace BOOK_ERROR 
{
	const int ALL_GOOD = 1;
	const int IS_EMPTY = 0;
	const int WRONG_YEAR = -1;
	const int WRONG_PAGES = -2;
}

namespace PEOPLE_ERROR 
{
	const int ALL_GOOD = 1;
	const int IS_EMPTY = 0;
	const int WRONG_NAME = -1;
	const int WRONG_PHONE = -2;
	const int WRONG_ADDRESS = -3;
	const int WRONG_AGE = -4;
	const int WRONG_GIVE_DATE = -5;
	const int WRONG_RETURN_DATE = -6;
	const int GIVE_DATE_MORE_THAN_RETURN_DATE = -7;
}


class BookPage : public QMainWindow, public Page
{
	Q_OBJECT
public:
	BookPage(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, SQLWork* books_db, SQLWork* people_db);

	virtual void update_window();
	void start();

private:
	Ui::QtWidgetsApplication1Class* ui;
	QWidget* parent;
	QWidget* page;
	SQLWork* books_db;
	SQLWork* people_db;

	const int NUMBER_OF_BOOKS_ON_PAGE = 7;
	int current_page = 0;

	vector<int> books_id;

	ChoisePageButtons* choise_page_buttons;
	Searching* searching;
	QCheck* _check_creation;
	QCheck* _check_giving;

	void show_book(Book book, int row, int column);
	void show_list();

	void clear_page();
	void clear_book_list();

	QLabel* get_name_label(QString name);
	QPixmap* get_image_pixmap(QString path, const int WIDTH, const int HEIGHT);

	void create_choise_page_buttons();
	void create_search();
	void create_add_button();
	
	void open_edit_book_page(Book book);
	void open_show_book_page(Book book);
	void open_give_book_page(Book book);
	void open_book_creation_page();

	void edit_book();
	void give_book(Book book);
	void return_book(Book book);
	void create_book();

	bool check_creation();
	void clear_creation_fields();
	void clear_give_fields();
	int check_giving();

	void update_books_id();
	void adjust_fonts();
	void init_cheks_messages();
	void open_main_widjet();	
};

