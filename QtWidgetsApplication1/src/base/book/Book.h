#pragma once
#include <string>
#include "SQLWORK.h"
#include "constants.h"
#include <QString>

using namespace std;

class Book
{
public:
	void set_id(int id); // установка id
	void set_name(QString name); // установка названия
	void set_author_name(QString author_name); // установка имени автора
	void set_genre(QString genre); // установка жанра
	void set_year(int year); // установка года
	void set_amount_of_page(int amount_of_page); // установка количества страниц
	void set_content(QString content); // установка краткого описания
	void set_path_to_img(QString path_to_img); // установка пути к изображению
	
	void set_date_of_giving(QString date_of_giving); // установка даты выдачи
	void set_date_of_return(QString date_of_return); // установка даты возвращения
	void set_enabled(bool is_enable); // установка доступности

	int get_id(); // возвращение id
	QString get_name(); // возвращение названия
	QString get_author_name(); // возвращение имени автора
	QString get_genre(); // возвращение жанра
	int get_year(); // возвращение года
	int get_amount_of_page(); // возвращение количества страниц
	QString get_content(); // возвращение краткого описания
	QString get_path_to_img(); // возвращение пути к изображению

	QString get_date_of_giving(); // возвращение даты выдачи
	QString get_date_of_return(); // возвращение даты возвращения книги
	bool get_enabled(); // возвращение доступности

	void update(SQLWork* db); // обновление книги в таблице
	void add_in_db(SQLWork* db); // добавление книги в таблицу
	static Book get_book_by_id(SQLWork* db, int id); // возвращение книги из таблицы по id

private:
	int id = 0;
	QString name = "";
	QString author_name = "";
	QString genre = "";
	int year = 0;
	int amount_of_page = 0;
	QString content = "";
	QString path_to_img = "";
	QString date_of_giving = "-";
	QString date_of_return = "-";
	bool is_enabled = true;
};

