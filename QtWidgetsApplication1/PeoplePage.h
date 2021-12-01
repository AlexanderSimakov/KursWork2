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

	virtual void update_window(); // обновляет информацию окна
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

	void update_people_id(); // обновление вектора id людей

	void clear_page(); // полная очистка страницы
	void clear_people_list(); // очистка вывода информации о людях

	void show_list(); // вывод информации о людях
	void show_people(People* people, int row, int column); // вывод информации о конкретном человеке
	void create_choise_page_buttons(); // инициализация кнопок выбора страниц
	void create_search(); // инициализация поиска

	void create_back_label(int row, int column); // инициализация фона при выводе информации о человеке
	void create_back_people_info_label(int row, int column); // инициализация рамки вывода информации о человеке
	void create_back_book_info_label(int row, int column); // инициализация рамки вывода информации о взятой книге
	void create_name_label(People* people, int row, int column); // создание поля для отображения имени человека
	void create_phone_label(People* people, int row, int column); // создание поля для отображения номера телефона человека  
	void create_address_label(People* people, int row, int column); // создание поля для отображения адреса человека
	void create_age_label(People* people, int row, int column); // создание поля для отображения возраста человека
	void create_sex_label(People* people, int row, int column); // создание поля для отображения пола человека

	void create_book_name_label(Book* book, int row, int column); // создание поля для отображения названия взятой книги
	void create_book_give_date_label(Book* book, int row, int column, bool is_overdue = false); // создание поля для отображения даты выдачи взятой книги
	void create_book_return_date_label(Book* book, int row, int column, bool is_overdue = false); // создание поля для отображения даты возвращения взятой книги

	void create_book_button(People people, int row, int column); // инициализация кнопки просмотра взятой человеком книги
	void create_return_button(People people, int row, int column); // инициализация кнопки возвращения взятой книги

	void return_book(People people); // функция возвращаюшя книгу
	void open_book_info_page(People people); // функция открытия всей информации о книге

	People get_people_by_id(int id); // возвращения обекта People по его id
};

