#include "Account.h"

void Account::set_id(int id) {
	this->id = id;
}

void Account::set_name(QString name) {
	this->name = name;
}

void Account::set_login(QString login) {
	this->login = login;
}

void Account::set_salted_hash_password(QString salted_hash_password) {
	this->salted_hash_password = salted_hash_password;
}

void Account::set_salt(QString salt) {
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

QString Account::get_name() {
	return name;
}

QString Account::get_login() {
	return login;
}

QString Account::get_salted_hash_password() {
	return salted_hash_password;
}

QString Account::get_salt() {
	return salt;
}

int Account::get_role() {
	return role;
}

bool Account::get_access() {
	return access;
}

QString Account::get_password(QString true_hash, QString true_salt, QString password) {
	if (true_hash != get_generated_hash(password, true_salt)) // неправильный логин или пароль
		return "-1";
	else  // все хорошо
		return password;
}

bool Account::is_right_password(QString true_hash, QString true_salt, QString password) {
	if (true_hash != get_generated_hash(password, true_salt)) // неправильный логин или пароль
		return false;
	else
		return true;
}

QString Account::get_generated_hash(QString line, QString salt) {
	return QString::fromStdString(sha1(sha1(line.toStdString() + salt.toStdString()) + sha1(line.toStdString())));
}

QString Account::get_symbols_for_salt() {
	QString symbols;
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

QString Account::get_generated_salt() {
	QString symbols = get_symbols_for_salt();

	srand(time(NULL));

	QString salt;
	salt.reserve(SALT_SIZE);

	for (int i = 0; i < SALT_SIZE; i++) {
		salt.push_back(symbols[rand() % SYMBOLS_SIZE]);
	}

	return salt;
}

void Account::update(SQLWork* accounts_db) {
	QString rule = " " + DB::ACCOUNTS::FIELD::ID + " = " + QString::fromStdString(to_string(id));
	accounts_db->update(DB::ACCOUNTS::FIELD::LOGIN, "'" + login + "'", rule);
	accounts_db->update(DB::ACCOUNTS::FIELD::NAME, "'" + name + "'", rule);
	accounts_db->update(DB::ACCOUNTS::FIELD::HASH, "'" + salted_hash_password + "'", rule);
	accounts_db->update(DB::ACCOUNTS::FIELD::SALT, "'" + salt + "'", rule);
	accounts_db->update(DB::ACCOUNTS::FIELD::ROLE, QString::fromStdString(to_string(role)), rule);
	accounts_db->update(DB::ACCOUNTS::FIELD::ACCESS, QString::fromStdString(to_string(access)), rule);
}

void Account::add_in_db(SQLWork* accounts_db) {
	accounts_db->push_back({
			"'" + login + "'",
			"'" + name + "'",
			"'" + salted_hash_password + "'",
			"'" + salt + "'",
			QString::fromStdString(to_string(role)),
			QString::fromStdString(to_string(access)),
			QString::fromStdString(to_string(id))
		});
}



