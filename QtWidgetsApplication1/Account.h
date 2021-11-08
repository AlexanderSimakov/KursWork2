#pragma once
#include <string>
#include <QString>
#include "SQLWORK.h"
#include "sha256.h"
#include "constants.h"
#include <time.h>

using namespace std;

class Account
{
public:
    void set_id(int id);
    void set_login(QString login);
    void set_name(QString name);
    void set_salted_hash_password(QString salted_hash_password);
    void set_salt(QString salt);
    void set_role(int role);
    void set_access(bool access);

    int get_id();
    QString get_login();
    QString get_name();
    QString get_salted_hash_password();
    QString get_salt();
    int get_role();
    bool get_access();

    void update(SQLWork* account_db);
    void add_in_db(SQLWork* account_db);

    QString get_password(QString true_hash, QString true_salt, QString password);
    bool is_right_password(QString true_hash, QString true_salt, QString password);
    static QString get_generated_hash(QString line, QString salt);
    static QString get_symbols_for_salt();
    static QString get_generated_salt();

private:
    static const int SALT_SIZE = 16;
    static const int SYMBOLS_SIZE = 62;

    int id = 0;
    QString login = "";
    QString name = "";
    QString salted_hash_password = "";
    QString salt = "";
    int role = -1;
    bool access = false;

};

