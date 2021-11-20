#pragma once
#include <string>
#include "SQLWORK.h"
#include "constants.h"
#include <QString>

using namespace std;

class Book
{
public:
	void set_id(int id);
	void set_name(QString name);
	void set_author_name(QString author_name);
	void set_genre(QString genre);
	void set_year(int year);
	void set_amount_of_page(int amount_of_page);
	void set_content(QString content);
	void set_path_to_img(QString path_to_img);
	
	void set_date_of_giving(QString date_of_giving);
	void set_date_of_return(QString date_of_return);
	void set_enabled(bool is_enable);

	int get_id();
	QString get_name();
	QString get_author_name();
	QString get_genre();
	int get_year();
	int get_amount_of_page();
	QString get_content();
	QString get_path_to_img();

	QString get_date_of_giving();
	QString get_date_of_return();
	bool get_enabled();

	void update(SQLWork* db);
	void add_in_db(SQLWork* db);
	static Book get_book_by_id(SQLWork* db, int id);

private:
	int id = 0;
	QString name = "";
	QString author_name = "";
	QString genre = "";
	int year = 0;
	int amount_of_page = 0;
	QString content = "";
	QString path_to_img = "";
	QString date_of_giving = "-";
	QString date_of_return = "-";
	bool is_enabled = true;
};

