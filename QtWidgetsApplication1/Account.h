#pragma once
#include <string>
#include "SQLWORK.h"
#include "sha256.h"
#include <time.h>

using namespace std;

class Account
{
public:
    void set_id(int id);
    void set_login(string login);
    void set_name(string name);
    void set_salted_hash_password(string salted_hash_password);
    void set_salt(string salt);
    void set_role(int role);
    void set_access(bool access);

    int get_id();
    string get_login();
    string get_name();
    string get_salted_hash_password();
    string get_salt();
    int get_role();
    bool get_access();

    void update(SQLWork* account_db);
    void add_in_db(SQLWork* account_db);

    string get_password(string true_hash, string true_salt, string password);
    bool is_right_password(string true_hash, string true_salt, string password);
    static string get_generated_hash(string line, string salt);
    static string get_symbols_for_salt();
    static string get_generated_salt();

private:
    static const int SALT_SIZE = 16;
    static const int SYMBOLS_SIZE = 62;

    int id = 0;
    string login = "";
    string name = "";
    string salted_hash_password = "";
    string salt = "";
    int role = -1;
    bool access = false;

};

