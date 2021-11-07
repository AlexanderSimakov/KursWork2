#include "Book.h"

void Book::set_id(int id) {
	this->id = id;
}

void Book::set_name(string name) {
	this->name = name;
}

void Book::set_author_name(string author_name) {
	this->author_name = author_name;
}

void Book::set_genre(string genre) {
	this->genre = genre;
}

void Book::set_year(int year) {
	this->year = year;
}

void Book::set_amount_of_page(int amount_of_page) {
	this->amount_of_page = amount_of_page;
}

void Book::set_content(string content) {
	this->content = content;
}

void Book::set_path_to_img(string path_to_img) {
	this->path_to_img = path_to_img;
}

void Book::set_date_of_giving(string date_of_giving) {
	this->date_of_giving = date_of_giving;
}

void Book::set_date_of_return(string date_of_return) {
	this->date_of_return = date_of_return;
}

void Book::set_enabled(bool is_enabled) {
	this->is_enabled = is_enabled;
}

int Book::get_id() {
	return id;
}

string Book::get_name() {
	return name;
}

string Book::get_author_name() {
	return author_name;
}

string Book::get_genre() {
	return genre;
}

int Book::get_year() {
	return year;
}

int Book::get_amount_of_page() {
	return amount_of_page;
}

string Book::get_content() {
	return content;
}

string Book::get_path_to_img() {
	return path_to_img;
}

string Book::get_date_of_giving() {
	return date_of_giving;
}

string Book::get_date_of_return() {
	return date_of_return;
}

bool Book::get_enabled() {
	return is_enabled;
}

void Book::update(SQLWork* db) {
	string rule = " " + DB::BOOKS::FIELD::ID + " = " + to_string(id);
	db->update(DB::BOOKS::FIELD::NAME, "'" + name + "'", rule);
	db->update(DB::BOOKS::FIELD::AUTHOR, "'" + author_name + "'", rule);
	db->update(DB::BOOKS::FIELD::GENRE, "'" + genre + "'", rule);
	db->update(DB::BOOKS::FIELD::YEAR, to_string(year), rule);
	db->update(DB::BOOKS::FIELD::PAGES, to_string(amount_of_page), rule);
	db->update(DB::BOOKS::FIELD::CONTENT, "'" + content + "'", rule);
	db->update(DB::BOOKS::FIELD::IMG_PATH, "'" + path_to_img + "'", rule);
	db->update(DB::BOOKS::FIELD::GIVE_DATE, "'" + date_of_giving + "'", rule);
	db->update(DB::BOOKS::FIELD::RETURN_DATE, "'" + date_of_return + "'", rule);
	db->update(DB::BOOKS::FIELD::ENABLED, is_enabled ? "1" : "0", rule);

}

void Book::add_in_db(SQLWork* db) {
	db->push_back({
			to_string(id),
			"'" + name + "'",
			"'" + author_name + "'",
			"'" + genre + "'",
			to_string(year),
			to_string(amount_of_page),
			"'" + content + "'",
			"'" + path_to_img + "'",
			"'" + date_of_giving + "'",
			"'" + date_of_return + "'",
			is_enabled ? "1" : "0"
		});
}

Book Book::get_book_by_id(SQLWork* db, int id) {
	Book book;

	book.set_id(id);
	book.set_name(db->get_text(DB::BOOKS::FIELD::ID, to_string(id), 1));
	book.set_author_name(db->get_text(DB::BOOKS::FIELD::ID, to_string(id), 2));
	book.set_genre(db->get_text(DB::BOOKS::FIELD::ID, to_string(id), 3));
	book.set_year(db->get_int(DB::BOOKS::FIELD::ID, to_string(id), 4));
	book.set_amount_of_page(db->get_int(DB::BOOKS::FIELD::ID, to_string(id), 5));
	book.set_content(db->get_text(DB::BOOKS::FIELD::ID, to_string(id), 6));
	book.set_path_to_img(db->get_text(DB::BOOKS::FIELD::ID, to_string(id), 7));
	book.set_date_of_giving(db->get_text(DB::BOOKS::FIELD::ID, to_string(id), 8));
	book.set_date_of_return(db->get_text(DB::BOOKS::FIELD::ID, to_string(id), 9));
	book.set_enabled(db->get_int(DB::BOOKS::FIELD::ID, to_string(id), 10));


	return book;
}


