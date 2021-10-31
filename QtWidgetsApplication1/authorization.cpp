#pragma once
#include "authorization.h"


Authorization::Authorization(SQLWork* sql_db) {
	this->sql_db = sql_db;
}

// ������ �����������
// ���������� ���� ����������������� ��������, ��� -1, ���� ������������ ����� �� �����������
int Authorization::start(string login, string pass) {
	string db_account_hash, db_account_salt, input_password;

	db_account_hash = sql_db->get_text("LOGIN", login, 2);
	db_account_salt = sql_db->get_text("LOGIN", login, 3);
	input_password = console::get_password(db_account_hash, db_account_salt, pass);

	if (input_password == "-1") {
		return -1;
		//console::show_error("�� ����� ������������ ����� ��� ������");
	}
	else if (sql_db->get_int("LOGIN", login, 5) == 0) {
		return -2;
		//console::show_error("� ������ ������ ��� ������� ������� �������������");
	}
	else {
		this->login = login;
		return sql_db->get_int("LOGIN", login, 4);
	}

}

string Authorization::get_login() {
	return this->login;
}
