#pragma once
#include <iostream>
#include "SQLWORK.h"
#include "helpFunctions.h"
#include "constants.h"
#include <string>



using namespace std;


class Authorization
{
public:
	Authorization(SQLWork* sql_db);
	int start(string login, string pass);
	string get_login();

private:
	SQLWork *sql_db = nullptr;
	string login = "";
};
