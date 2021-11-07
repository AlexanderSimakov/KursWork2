#pragma once
#include <string>
#include "SQLWORK.h"
#include "constants.h"

using namespace std;


class Book
{
public:

	void set_id(int id);
	void set_name(string name);
	void set_author_name(string author_name);
	void set_genre(string genre);
	void set_year(int year);
	void set_amount_of_page(int amount_of_page);
	void set_content(string content);
	void set_path_to_img(string path_to_img);
	
	void set_date_of_giving(string date_of_giving);
	void set_date_of_return(string date_of_return);
	void set_enabled(bool is_enable);

	int get_id();
	string get_name();
	string get_author_name();
	string get_genre();
	int get_year();
	int get_amount_of_page();
	string get_content();
	string get_path_to_img();

	string get_date_of_giving();
	string get_date_of_return();
	bool get_enabled();


	void update(SQLWork* db);
	void add_in_db(SQLWork* db);
	static Book get_book_by_id(SQLWork* db, int id);
	


private:
	

	int id = 0;
	string name = "";
	string author_name = "";
	string genre = "";
	int year = 0;
	int amount_of_page = 0;
	string content = "";
	string path_to_img = "";

	string date_of_giving = "-";
	string date_of_return = "-";
	bool is_enabled = true;


};

