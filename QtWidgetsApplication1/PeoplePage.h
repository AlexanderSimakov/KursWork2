#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include <QMessageBox>
#include "SQLWORK.h"
#include "People.h"
#include "Book.h"
#include "ChoisePageButtons.h"
#include "Page.h"
#include <ctime>
#include "Searching.h"
#include "constants.h"

class PeoplePage : public QMainWindow, public Page
{
	Q_OBJECT
public:
	PeoplePage(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, SQLWork* people_db, SQLWork* book_db);

	virtual void update_window();
	void start();

private:
	Ui::QtWidgetsApplication1Class* ui;
	QWidget* _parent;
	QWidget* page;
	SQLWork* people_db;
	SQLWork* book_db;

	const int NUMBER_OF_PEOPLE_ON_PAGE = 7;
	const int ADD = 130;
	const int ADD_X = 360;
	const int ADD_Y = 320;
	const int MARGIN = 5;
	const int PAGE_WIDTH;
	const int PAGE_HEIGHT;
	int current_page = 0;
	vector<int> people_id;

	ChoisePageButtons* choise_page_buttons;
	Searching* searching;

	void update_people_id();

	void clear_page();
	void clear_people_list();

	void show_list();
	void show_people(People* people, int row, int column);
	void create_choise_page_buttons();
	void create_search();

	void create_back_label(int row, int column);
	void create_back_people_info_label(int row, int column);
	void create_back_book_info_label(int row, int column);
	void create_name_label(People* people, int row, int column);
	void create_phone_label(People* people, int row, int column);
	void create_address_label(People* people, int row, int column);
	void create_age_label(People* people, int row, int column);
	void create_sex_label(People* people, int row, int column);

	void create_book_name_label(Book* book, int row, int column);
	void create_book_give_date_label(Book* book, int row, int column, bool is_overdue = false);
	void create_book_return_date_label(Book* book, int row, int column, bool is_overdue = false);

	void create_book_button(People people, int row, int column);
	void create_return_button(People people, int row, int column);

	void return_book(People people);
	void open_book_info_page(People people);

	People get_people_by_id(int id);
};

