#pragma once
#include "sqlite3.h"
#include <string>
#include <vector>
#include <iostream>
#include <QString>

using namespace std;

struct SQL_cell
{
	QString NAME = "";
	QString TYPE = "";
};


class SQLWork
{
public:
	SQLWork(const QString file_name, const QString data_base_name);
	void create_table_if_not_exists(vector<SQL_cell> table_fields);
	void open();
	void close();
	void push_back(vector<QString> field);
	void update(QString fild_for_update, QString new_value, QString rule);
	void delete_field(QString rule);
	
	vector<QString> get_strings(int column = 0);
	vector<int> get_ints(int column = 0);
	vector<int> get_ints(int column, QString rule);

	int get_int(QString db_field, QString field_for_search, int num_of_value);
	QString get_text(QString db_field, QString field_for_search, int num_of_value);
	int get_count();
	int get_count(QString rule);
	int get_count_unique_fieds(QString column_name);
	int get_sum(QString column_name, QString rule);
	vector<QString> get_unique_fields(QString column_name);
	bool is_table_exists();

private:
	vector<SQL_cell> table_fields;
	const QString FILE_NAME;
	const QString DATA_BASE_NAME;
	sqlite3* dataBase = nullptr;
	sqlite3_stmt* stmt = nullptr;

	bool do_sql(QString sql);
	QString get_created_table_sql_command();
	QString get_push_back_sql(vector<QString> field);
	
};





