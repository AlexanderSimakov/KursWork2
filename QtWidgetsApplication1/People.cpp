#include "People.h"

void People::set_id(int id) {
	this->id = id;
}

void People::set_book_id(int book_id) {
	this->book_id = book_id;
}

void People::set_name(QString name) {
	this->name = name;
}

void People::set_phone(QString phone) {
	this->phone = phone;
}

void People::set_address(QString address) {
	this->address = address;
}

void People::set_age(int age) {
	this->age = age;
}

void People::set_sex(int sex) {
	this->sex = sex;
}

int People::get_id() {
	return id;
}

int People::get_book_id() {
	return book_id;
}

QString People::get_name() {
	return name;
}

QString People::get_phone() {
	return phone;
}

QString People::get_address() {
	return address;
}

int People::get_age() {
	return age;
}

int People::get_sex() {
	return sex;
}

void People::add_in_db(SQLWork* people_db) {
	people_db->push_back({
			QString::fromStdString(to_string(id)),
			QString::fromStdString(to_string(book_id)),
			"'" + name + "'",
			"'" + phone + "'",
			"'" + address + "'",
			QString::fromStdString(to_string(age)),
			QString::fromStdString(to_string(sex))
		});
}

People People::get_people_by_book_id(SQLWork* people_db, int book_id) {
	People people;

	QString q_book_id = QString::fromStdString(to_string(book_id));

	people.set_id(people_db->get_int(DB::PEOPLE::FIELD::BOOK_ID, q_book_id, 0));
	people.set_book_id(people_db->get_int(DB::PEOPLE::FIELD::BOOK_ID, q_book_id, 1));
	people.set_name(people_db->get_text(DB::PEOPLE::FIELD::BOOK_ID, q_book_id, 2));
	people.set_phone(people_db->get_text(DB::PEOPLE::FIELD::BOOK_ID, q_book_id, 3));
	people.set_address(people_db->get_text(DB::PEOPLE::FIELD::BOOK_ID, q_book_id, 4));
	people.set_age(people_db->get_int(DB::PEOPLE::FIELD::BOOK_ID, q_book_id, 5));
	people.set_sex(people_db->get_int(DB::PEOPLE::FIELD::BOOK_ID, q_book_id, 6));


	return people;
}



