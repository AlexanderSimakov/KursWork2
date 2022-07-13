#pragma once
#include <string>
#include "SQLWORK.h"
#include "constants.h"
#include <QString>

class People
{
public:
	void set_id(int id); // установка id
	void set_book_id(int book_id); // установка id взятой книги
	void set_name(QString name); // установка имени
	void set_phone(QString phone); // установка номера телефона
	void set_address(QString address); // установка адреса
	void set_age(int age); // установка возраста
	void set_sex(int sex); // установка пола

	int get_id(); // возвращает id
	int get_book_id(); // возвращает id книги
	QString get_name(); // возвращает имя
	QString get_phone(); // возвращает номер телефона
	QString get_address(); // возвращаеь адрес
	int get_age(); // возвращает возраст
	int get_sex(); // возвращает пол

	void add_in_db(SQLWork* people_db); // добавление обьекта в таблицу
	static People get_people_by_book_id(SQLWork* people_db, int book_id); // возвращение обьекта из таблицы по его id

private:
	int id = 0;
	int book_id = 0;
	QString name = "";
	QString phone = "";
	QString address = "";
	int age = 0;
	int sex = 0;
};

