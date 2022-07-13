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

	virtual void update_window(); // обновление экрана
	void start(); // запуск страницы книг

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

	void show_book(Book book, int row, int column); // вывод книги на экран
	void show_list(); // вывод списка книг

	void clear_page(); // очистка страницы
	void clear_book_list(); // очистка выведенных книг

	QLabel* get_name_label(QString name); // инициализирует и возвращает виджет с названием книги
	QPixmap* get_image_pixmap(QString path, const int WIDTH, const int HEIGHT); // инициализирует и возвращает картинку книги

	void create_choise_page_buttons(); // инициализация кнопок выбора страницы
	void create_search(); // инициализация поиска
	void create_add_button(); // инициализация кнопки добавления книги
	
	void open_edit_book_page(Book book); // открывает страницу редактирования книги
	void open_show_book_page(Book book); // открывает страницу вывода информации о книге
	void open_give_book_page(Book book); // открывает страницу выдачи книги
	void open_book_creation_page(); // открывает страницу добавления новой книги

	void edit_book(); // изменяет информацию о книге
	void give_book(Book book); // выдача книги
	void return_book(Book book); // возвращение книги
	void create_book(); // создание книги

	bool check_creation(); // проверка при создании книги
	void clear_creation_fields(); // очистка полей ввода при создании книги
	void clear_give_fields(); // очистка полей ввода при выдаче книги
	int check_giving(); // проверка при выдаче книги

	void update_books_id(); // обновление вектора, содержащего id книг
	void adjust_fonts(); // настройки стилей шрифтов
	void init_cheks_messages(); // инициализация сообщений проверки
	void open_main_widjet(); // открытие главного окна 
};

