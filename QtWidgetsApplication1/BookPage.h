#pragma once
#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include "ui_QtWidgetsApplication1.h"
#include "SQLWORK.h"
#include "Book.h"
#include "People.h"
#include "Page.h"
#include "ChoisePageButtons.h"
#include "Searching.h"

class BookPage : public QMainWindow, public Page
{
	Q_OBJECT
public:
	BookPage(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, SQLWork* books_db, SQLWork* people_db);

	virtual void update_window() {
		show_list();
	}

	void start();

private:
	QWidget* _parent;
	Ui::QtWidgetsApplication1Class* ui;
	QWidget* page;
	SQLWork* books_db;
	SQLWork* people_db;

	const int NUMBER_OF_BOOKS_ON_PAGE = 7;
	const int ADD = 130;
	const int ADD_X = 360;
	const int ADD_Y = 320;
	const int MARGIN = 5;
	const int PAGE_WIDTH;
	const int PAGE_HEIGHT;
	int current_page = 0;

	vector<int> books_id;

	ChoisePageButtons* choise_page_buttons;
	Searching* searching;
	
	void update_books_id();

	void show_list();

	void clear_page();
	void clear_book_list();

	void show_book(Book* book, int row, int column);
	void create_choise_page_buttons();
	void create_search();
	void create_add_button();
	
	void create_edit_button(Book book, int num_in_list);

	void edit_book();
	void open_edit_book_page(Book book);

	void open_show_book_page(Book book);
	
	void open_give_book_page(Book book);
	void give_book(Book book);
	void return_book(Book book);

	void open_book_creation_page();
	void create_book();

};



