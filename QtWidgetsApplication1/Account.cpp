#include "Account.h"

void Account::set_id(int id) {
	this->id = id;
}

void Account::set_name(string name) {
	this->name = name;
}

void Account::set_login(string login) {
	this->login = login;
}

void Account::set_salted_hash_password(string salted_hash_password) {
	this->salted_hash_password = salted_hash_password;
}

void Account::set_salt(string salt) {
	this->salt = salt;
}

void Account::set_role(int role) {
	this->role = role;
}

void Account::set_access(bool access) {
	this->access = access;
}

int Account::get_id() {
	return id;
}

string Account::get_name() {
	return name;
}

string Account::get_login() {
	return login;
}

string Account::get_salted_hash_password() {
	return salted_hash_password;
}

string Account::get_salt() {
	return salt;
}

int Account::get_role() {
	return role;
}

bool Account::get_access() {
	return access;
}

string Account::get_password(string true_hash, string true_salt, string password) {
	if (true_hash != get_generated_hash(password, true_salt)) // неправильный логин или пароль
		return "-1";
	else  // все хорошо
		return password;
}

bool Account::is_right_password(string true_hash, string true_salt, string password) {
	if (true_hash != get_generated_hash(password, true_salt)) // неправильный логин или пароль
		return false;
	else
		return true;
}

string Account::get_generated_hash(string line, string salt) {
	return sha1(sha1(line + salt) + sha1(line));
}

string Account::get_symbols_for_salt() {
	string symbols;
	symbols.reserve(SYMBOLS_SIZE);

	char little_letter = 'a';
	char big_letter = 'A';
	char number = '0';
	for (int k = 0; k < 26; k++) {
		symbols.push_back(little_letter++);
		symbols.push_back(big_letter++);
		if (k < 10) symbols.push_back(number++);
	}

	return symbols;
}

string Account::get_generated_salt() {
	string symbols = get_symbols_for_salt();

	srand(time(NULL));

	string salt;
	salt.reserve(SALT_SIZE);

	for (int i = 0; i < SALT_SIZE; i++) {
		salt.push_back(symbols[rand() % SYMBOLS_SIZE]);
	}

	return salt;
}

void Account::update(SQLWork* accounts_db) {
	string rule = " " + DB::ACCOUNTS::FIELD::ID + " = " + to_string(id);
	accounts_db->update(DB::ACCOUNTS::FIELD::LOGIN, "'" + login + "'", rule);
	accounts_db->update(DB::ACCOUNTS::FIELD::NAME, "'" + name + "'", rule);
	accounts_db->update(DB::ACCOUNTS::FIELD::HASH, "'" + salted_hash_password + "'", rule);
	accounts_db->update(DB::ACCOUNTS::FIELD::SALT, "'" + salt + "'", rule);
	accounts_db->update(DB::ACCOUNTS::FIELD::ROLE, to_string(role), rule);
	accounts_db->update(DB::ACCOUNTS::FIELD::ACCESS, to_string(access), rule);
}

void Account::add_in_db(SQLWork* accounts_db) {
	accounts_db->push_back({
			"'" + login + "'",
			"'" + name + "'",
			"'" + salted_hash_password + "'",
			"'" + salt + "'",
			to_string(role),
			to_string(access),
			to_string(id)
		});
}



