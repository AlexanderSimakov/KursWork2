#pragma once
#include "SQLWORK.h"

// конструктор, инициализируюший название базы данных и название файла базы данных
SQLWork::SQLWork(const string FILE_NAME, const string DATA_BASE_NAME) 
	: FILE_NAME(FILE_NAME),  DATA_BASE_NAME(DATA_BASE_NAME){ }

// создает таблицу в базе данных, если она не создана до этого
void SQLWork::create_table_if_not_exists(vector<SQL_cell> table_fields) {
	this->table_fields = table_fields;
	do_sql(get_created_table_sql_command());
}

// генерирует sql команду для создания базы данных и возвращает ее
string SQLWork::get_created_table_sql_command() {
	string sql = " CREATE TABLE IF NOT EXISTS " + DATA_BASE_NAME + " ( ";

	for (int i = 0; i < table_fields.size(); i++) {
		sql += table_fields[i].NAME + " " + table_fields[i].TYPE;
		if (i != table_fields.size() - 1) sql += ",";
		sql += " ";
	}

	sql += " ); ";
	return sql;
}

// открывает базу данных
void SQLWork::open() {
	if (sqlite3_open(FILE_NAME.c_str(), &dataBase)) {
		cout << "Ошибка открытия/создания БД:" << sqlite3_errmsg(dataBase);
	}
}

// закрывает базу данных
void SQLWork::close() {
	if (sqlite3_close(dataBase) == SQLITE_BUSY) {
		cout << "Ошибка закрытия БД." << endl;
	}
}

// вставляет поле в конец таблицы
void SQLWork::push_back(vector<string> field) {
	string sql = get_push_back_sql(field);
	do_sql(sql);
}

// генерирует команду вставки в конец таблицы
string SQLWork::get_push_back_sql(vector<string> field) {
	string sql = "INSERT INTO " + DATA_BASE_NAME + " ( ";
	for (int i = 0; i < table_fields.size(); i++) {
		sql += table_fields[i].NAME;
		if (i != table_fields.size() - 1) sql += ",";
		sql += " ";
	}

	sql += " ) VALUES ( ";

	for (int i = 0; i < field.size(); i++) {
		sql += field[i];
		if (i != field.size() - 1) sql += ",";
		sql += " ";
	}

	sql += " );";
	return sql;
}

// обновляет поле на новое значение по введенному правилу sql
void SQLWork::update(string fild_in_db, string new_value, string rule) {
	string sql = "UPDATE " + DATA_BASE_NAME + " set " + fild_in_db + " = " + new_value + " where " + rule + " ;";
	do_sql(sql);
}

// удаляет поле по введенному правилу sql
void SQLWork::delete_field(string rule) {
	string sql = "DELETE from " + DATA_BASE_NAME + " where " + rule + " ;";
	do_sql(sql);
}

// выводит таблицу с введенными столбцами и правиломи
void SQLWork::show_table(string sql_before_db_name, string sql_after_db_name, vector<string> out_strings, vector<int> columns_in_db, vector<int> lenght_of_columns) {
	string sql = sql_before_db_name + DATA_BASE_NAME + sql_after_db_name;

	if (!is_table_exists()) {
		cout << " В таблице отсутствуют записи..." << endl;
	}
	else {
		sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

		for (int i = 0; i < out_strings.size(); i++) {
			cout << " " << out_strings[i];
			print_spaces(lenght_of_columns[i] - out_strings[i].size() - 2);
			cout << "|";
		}
		cout << endl;

		int rc;
		string text;
		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
			for (int i = 0; i < out_strings.size(); i++) {
				text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, columns_in_db[i]));
				cout << " " << text;
				print_spaces(lenght_of_columns[i] - text.size() - 2);
				cout << "|";
			}
			cout << endl;
		}

		sqlite3_finalize(stmt);
	}
}

vector<string> SQLWork::get_strings(int column) {
	string sql = "SELECT * FROM " + DATA_BASE_NAME + " ;";
	vector<string> strings;
	
	if (!is_table_exists()) {
		cout << " В таблице отсутствуют записи..." << endl;
	}
	else {
		sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

		int rc;
		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
				strings.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, column)));
				
		}

		sqlite3_finalize(stmt);
	}
	return strings;
}

vector<int> SQLWork::get_ints(int column) {
	string sql = "SELECT * FROM " + DATA_BASE_NAME + " ;";
	vector<int> ints;

	if (!is_table_exists()) {
		cout << " В таблице отсутствуют записи..." << endl;
	}
	else {
		sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

		int rc;
		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
			ints.push_back(sqlite3_column_int(stmt, column));

		}

		sqlite3_finalize(stmt);
	}
	return ints;
}

vector<int> SQLWork::get_ints(int column, string rule) {
	string sql = "SELECT * FROM " + DATA_BASE_NAME + " " + rule + " ;";
	vector<int> ints;

	if (!is_table_exists()) {
		cout << " В таблице отсутствуют записи..." << endl;
	}
	else {
		sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

		int rc;
		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
			ints.push_back(sqlite3_column_int(stmt, column));

		}

		sqlite3_finalize(stmt);
	}
	return ints;
}

// возвращает уникальные значения введенного столбца
vector<string> SQLWork::get_unique_fields(string column_name) {
	string sql = "SELECT DISTINCT " + column_name + " FROM " + DATA_BASE_NAME + " ;";
	int amount = get_count_unique_fieds(column_name);
	vector<string> fields;

	if (!is_table_exists()) {
		return {};
	}
	else {
		sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

		int rc;
		string text;
		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
			text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
			fields.push_back(text);
		}

		sqlite3_finalize(stmt);
	}
	return fields;
}

// возвращает true, если в таблтце есть записи
bool SQLWork::is_table_exists() {
	if (get_count() == 0) return false;
	else return true;
}

// возвращает количество ячеек в базе данных
int SQLWork::get_count() {
	string sql = "SELECT Count(*) FROM " + DATA_BASE_NAME + ";";

	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

	int rc, value = 0;
	if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		value = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	return value;
}

// возвращает количество ячеек в базе данных по введенному правилу
int SQLWork::get_count(string rule) {
	string sql = "SELECT Count(*) FROM " + DATA_BASE_NAME + rule + ";";

	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

	int rc, value = 0;
	if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		value = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	return value;
}

// возвращает количество уникальных значений в введенном столбце
int SQLWork::get_count_unique_fieds(string column_name) {
	string sql = "SELECT Count(DISTINCT " + column_name + " ) FROM " + DATA_BASE_NAME + " ;";

	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

	int rc, value = 0;
	if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		value = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	return value;
}

// возвращает сумму значений в введенном столбце
int SQLWork::get_sum(string column_name, string rule) {
	string sql = "SELECT SUM( " + column_name + " ) FROM " + DATA_BASE_NAME + rule +  ";";

	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

	int rc, value = 0;
	if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		value = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	return value;
}

// возвращает значение int, с номером num_of_value, когда находит field_for_search в поле db_field
int SQLWork::get_int(string db_field, string field_for_search, int num_of_value) {
	string sql = "SELECT * FROM " + DATA_BASE_NAME + " WHERE " + db_field + " GLOB '" + field_for_search + "';";

	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

	int rc, value = 0;
	if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		value = sqlite3_column_int(stmt, num_of_value);
	}

	sqlite3_finalize(stmt);
	return value;
}

// возвращает значение string, с номером num_of_value, когда находит field_for_search в поле db_field
string SQLWork::get_text(string db_field, string field_for_search, int num_of_value) {
	string text, sql = "SELECT * FROM " + DATA_BASE_NAME + " WHERE " + db_field + " GLOB '" + field_for_search + "';";

	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

	int rc;
	if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, num_of_value));
	}

	sqlite3_finalize(stmt);
	return text;
}

// выполняет переданную sql команду
bool SQLWork::do_sql(string sql) {
	char* error = 0;
	if (sqlite3_exec(dataBase, sql.c_str(), 0, 0, &error))
	{
		cout << "Ошибка БД: " << error << endl;
		sqlite3_free(error);
		return false;
	}
	else {
		return true;
	}
}

// печатает введенное количесвто пробелов
void SQLWork::print_spaces(int amount) {
	for (int i = 0; i < amount; i++) {
		cout << " ";
	}
}


