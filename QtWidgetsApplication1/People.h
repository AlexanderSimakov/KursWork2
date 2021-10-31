#pragma once
#include <string>
#include "SQLWORK.h"



class People
{
public:
	void set_id(int id);
	void set_book_id(int book_id);
	void set_name(string name);
	void set_phone(string phone);
	void set_address(string address);
	void set_age(int age);
	void set_sex(int sex);

	int get_id();
	int get_book_id();
	string get_name();
	string get_phone();
	string get_address();
	int get_age();
	int get_sex();

	void update(SQLWork* people_db);
	void add_in_db(SQLWork* people_db);
	static People get_people_by_book_id(SQLWork* people_db, int book_id);


private:
	int id = 0;
	int book_id = 0;
	string name = "";
	string phone = "";
	string address = "";
	int age = 0;
	int sex = 0;



};

