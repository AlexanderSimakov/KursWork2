#pragma once
#include "sqlite3.h"
#include <string>
#include <vector>
#include <iostream>
#include <QString>

using namespace std;

struct SQL_cell // структура дл€ хранени€ названи€ и типа €чейки
{
	QString NAME = "";
	QString TYPE = "";
};


class SQLWork
{
public:
	SQLWork(const QString file_name, const QString data_base_name); 
	void create_table_if_not_exists(vector<SQL_cell> table_fields); // создание таблицы по вектору €чеек
	void open(); // открытие таблицы данных
	void close(); // закрытие таблицы данных
	void push_back(vector<QString> field); // запись в таблицу одного элемента
	void update(QString fild_for_update, QString new_value, QString rule); // изменени€ пол€ €чейки в таблице
	void delete_field(QString rule); // удаление €чейки из таблицы
	
	vector<QString> get_strings(int column = 0); // функци€ возвращает вектор типа QString по номеру столбца из таблицы
	vector<int> get_ints(int column = 0); // функци€ возвращает вектор типа int по номеру столбца из таблицы
	vector<int> get_ints(int column, QString rule);// функци€ возвращает вектор типа int по номеру столбца и правилу из таблицы

	int get_int(QString db_field, QString field_for_search, int num_of_value);// функци€ возвращает значение типа int из таблицы
	QString get_text(QString db_field, QString field_for_search, int num_of_value);// функци€ возвращает значение типа QString из таблицы
	int get_count();// функци€ возвращает количество элементов в таблице
	int get_count(QString rule);// функци€ возвращает количество €чеек таблице по введенному правилу
	int get_count_unique_fieds(QString column_name);// функци€ возвращает количество уникальных значений по переданному названию столбца
	int get_sum(QString column_name, QString rule);// функци€ возвращает сумму элементов в стобце по его названию и правилу
	vector<QString> get_unique_fields(QString column_name);// функци€ возвращает вектор элементов типа QString из стобца по его названию
	bool is_table_exists();// возвращает true, если в таблица существует

private:
	vector<SQL_cell> table_fields;
	const QString FILE_NAME;
	const QString DATA_BASE_NAME;
	sqlite3* dataBase = nullptr;
	sqlite3_stmt* stmt = nullptr;

	bool do_sql(QString sql); // функци€, выполн€юща€ sql-команду
	QString get_created_table_sql_command(); // функци€, возвращающа€ сгенерированную команду создани€ таблицы
	QString get_push_back_sql(vector<QString> field); // функци€, возвращающа€ сгенерированную команду вставки €чейки в таблицу
};





