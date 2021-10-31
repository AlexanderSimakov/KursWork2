#pragma once
#include <string>
#include <iostream>
#include "SQLWORK.h"
#include "constants.h"
#include <time.h>
#include "sha256.h"

using namespace std;


namespace console {
	

	int check_free_login(SQLWork* db, string login);
	string get_password(string true_hash, string true_salt, string password);
	bool is_all_symbols_and_nums(string line);
}

namespace help_functions {
	string get_generated_hash(string line, string salt);
	bool is_symbol_letter_of_num(char symbol);
}




