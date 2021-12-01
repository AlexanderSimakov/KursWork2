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
    void set_id(int id); // установка id
    void set_login(QString login); // установка логина
    void set_name(QString name); // установка имени
    void set_salted_hash_password(QString salted_hash_password); // установка хешированного пароля
    void set_salt(QString salt); // установка соли
    void set_role(int role); // установка роли
    void set_access(bool access); // установка доступа

    int get_id(); // возвращение id
    QString get_login(); // возвращение логина
    QString get_name(); // возвращение имени
    QString get_salted_hash_password(); // возвращение хешированного пароля
    QString get_salt(); // возвращение соли
    int get_role(); // возвращение роли
    bool get_access(); // возвращение доступа

    void update(SQLWork* account_db); //  обновление аккаунта в таблице
    void add_in_db(SQLWork* account_db); // добавление аккаунта в таблицу

    bool is_right_password(QString true_hash, QString true_salt, QString password); // возвращает true, если пароль верный
    static QString get_generated_hash(QString line, QString salt); // возвращает хеш переданной строки с солью
    static QString get_symbols_for_salt(); // возвращает символы для соли
    static QString get_generated_salt(); // возвращает сгенерированную соль

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

