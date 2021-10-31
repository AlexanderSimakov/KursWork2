#pragma once
#include "helpFunctions.h"



// ���������� 1, ���� ������ ��� � ���� ������
int console::check_free_login(SQLWork* db, string login) {
	return 1;
	if (login.size() < 4) {
		return -1;
		//show_error("������� ��������� �����");
	}
	else if (!console::is_all_symbols_and_nums(login)) {
		return -2;
		//show_error("����� �������� ������������ �������");
	}
	else if (db->get_text("LOGIN", login, 2) != "") {
		return -3;
		//show_error("����� �����");
	}
	else {
		return 1;
	}
}

// ���������� ������, ���������� � ���������� ���� � ����
// ���������� '-1', ���� ������������ ����� ��� ������
string console::get_password(string true_hash, string true_salt, string password) {
	if (true_hash != help_functions::get_generated_hash(password, true_salt)) { // ������������ ����� ��� ������
		return "-1";
	}
	else { // ��� ������
		return password;
	}
}




// ���������� true, ���� ������ ������� ������ �� ���� � ����
bool console::is_all_symbols_and_nums(string line) {
	for (int i = 0; i < line.size(); i++) {
		if (!help_functions::is_symbol_letter_of_num(line[i])) return false;
	}

	return true;
}

// ���������� true, ���� ������ �������� ������, ������ ��� ��������
bool help_functions::is_symbol_letter_of_num(char symbol) {
	const string right_symbols = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890 ";
	for (int i = 0; i < right_symbols.size(); i++) {
		if (symbol == right_symbols[i]) return true;
	}
	return false;
}


// ���������� ������������ ����� ������
string help_functions::get_generated_hash(string line, string salt) {
	return sha1(sha1(line + salt) + sha1(line));
}
