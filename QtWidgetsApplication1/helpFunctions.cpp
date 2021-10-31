#pragma once
#include "helpFunctions.h"



// возвращает 1, если логина нет в базе данных
int console::check_free_login(SQLWork* db, string login) {
	return 1;
	if (login.size() < 4) {
		return -1;
		//show_error("Слишком маленький логин");
	}
	else if (!console::is_all_symbols_and_nums(login)) {
		return -2;
		//show_error("Логин содержит недопустимые символы");
	}
	else if (db->get_text("LOGIN", login, 2) != "") {
		return -3;
		//show_error("Логин занят");
	}
	else {
		return 1;
	}
}

// возвращает пароль, подходящий к введенному хешу и соли
// возвращает '-1', если неправильный логин или пароль
string console::get_password(string true_hash, string true_salt, string password) {
	if (true_hash != help_functions::get_generated_hash(password, true_salt)) { // неправильный логин или пароль
		return "-1";
	}
	else { // все хорошо
		return password;
	}
}




// возвращает true, если строка состоит только из букв и цифр
bool console::is_all_symbols_and_nums(string line) {
	for (int i = 0; i < line.size(); i++) {
		if (!help_functions::is_symbol_letter_of_num(line[i])) return false;
	}

	return true;
}

// возвращает true, если символ является буквой, цифрой или пробелом
bool help_functions::is_symbol_letter_of_num(char symbol) {
	const string right_symbols = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890 ";
	for (int i = 0; i < right_symbols.size(); i++) {
		if (symbol == right_symbols[i]) return true;
	}
	return false;
}


// возвращает хешированную солью строку
string help_functions::get_generated_hash(string line, string salt) {
	return sha1(sha1(line + salt) + sha1(line));
}
