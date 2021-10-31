#pragma once
#include "sqlite3.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct SQL_cell
{
	string NAME = "";
	string TYPE = "";
};


class SQLWork
{
public:
	SQLWork(const string file_name, const string data_base_name);
	void create_table_if_not_exists(vector<SQL_cell> table_fields);
	void open();
	void close();
	void push_back(vector<string> field);
	void update(string fild_for_update, string new_value, string rule);
	void delete_field(string rule);
	
	void show_table(string sql_before_db_name, string sql_after_db_name, vector<string> out_strings, vector<int> num_of_columns, vector<int> lenght_of_columns);
	vector<string> get_strings(int column = 0);
	vector<int> get_ints(int column = 0);
	vector<int> get_ints(int column, string rule);

	int get_int(string db_field, string field_for_search, int num_of_value);
	string get_text(string db_field, string field_for_search, int num_of_value);
	int get_count();
	int get_count(string rule);
	int get_count_unique_fieds(string column_name);
	int get_sum(string column_name, string rule);
	vector<string> get_unique_fields(string column_name);
	bool is_table_exists();
	void print_spaces(int amount);

private:
	vector<SQL_cell> table_fields;
	const string FILE_NAME;
	const string DATA_BASE_NAME;
	sqlite3* dataBase = nullptr;
	sqlite3_stmt* stmt = nullptr;

	bool do_sql(string sql);
	string get_created_table_sql_command();
	string get_push_back_sql(vector<string> field);
	
};





