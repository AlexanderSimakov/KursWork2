#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include "Account.h"
#include "SQLWORK.h"


void init_accounts_db(SQLWork* db);
void init_books_db(SQLWork* db);
void init_people_db(SQLWork* db);
void add_admin_account_if_not_exists(SQLWork* db);

enum role { user, admin };

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    SQLWork accounts_db(ACCOUNTS_DATABASE_FILENAME, ACCOUNTS_DATABASE_NAME);
    SQLWork books_db(BOOKS_DATABASE_FILENAME, BOOKS_DATABASE_NAME);
    SQLWork people_db(PEOPLE_DATABASE_FILENAME, PEOPLE_DATABASE_NAME);


    init_accounts_db(&accounts_db);
    init_books_db(&books_db);
    init_people_db(&people_db);

    QtWidgetsApplication1 w;
    
    w.set_accounts_db(&accounts_db);
    w.set_books_db(&books_db);
    w.set_people_db(&people_db);
    w.setWindowTitle("Library");
    w.init();
    w.show();
    
    return a.exec();
}


void init_accounts_db(SQLWork* db) {
    db->open();
    db->create_table_if_not_exists({ 
                 SQL_cell{ "LOGIN", "TEXT PRIMARY KEY NOT NULL"},
                 SQL_cell{ "NAME",   "TEXT NOT NULL"},
                 SQL_cell{ "HASH",   "TEXT NOT NULL"},
                 SQL_cell{ "SALT",   "TEXT NOT NULL"},
                 SQL_cell{ "ROLE",   "INT NOT NULL"},
                 SQL_cell{ "ACCESS", "INT NOT NULL"},
                 SQL_cell{ "ID", "INT NOT NULL"} });

    add_admin_account_if_not_exists(db);
}

void init_books_db(SQLWork* db) {
    db->open();
    db->create_table_if_not_exists({ 
                 SQL_cell{ "ID",             "INT PRIMARY KEY NOT NULL"},
                 SQL_cell{ "NAME",           "TEXT NOT NULL"},
                 SQL_cell{ "AUTHOR_NAME",    "TEXT NOT NULL"},
                 SQL_cell{ "GENRE",          "TEXT NOT NULL"},
                 SQL_cell{ "YEAR",           "INT NOT NULL"},
                 SQL_cell{ "AMOUNT_OF_PAGE", "INT NOT NULL"},
                 SQL_cell{ "CONTENT",        "TEXT NOT NULL"},
                 SQL_cell{ "PATH_TO_IMG",    "TEXT NOT NULL"},
                 SQL_cell{ "DATE_OF_GIVING", "TEXT NOT NULL"},
                 SQL_cell{ "DATE_OF_REPEAT", "TEXT NOT NULL"},
                 SQL_cell{ "ENABLED",        "INT NOT NULL"}
        });
}

void init_people_db(SQLWork* db) {
    db->open();
    db->create_table_if_not_exists({
                 SQL_cell{ "ID",             "INT PRIMARY KEY NOT NULL"},
                 SQL_cell{ "BOOK_ID",        "TEXT NOT NULL"},
                 SQL_cell{ "NAME",           "TEXT NOT NULL"},
                 SQL_cell{ "PHONE",          "TEXT NOT NULL"},
                 SQL_cell{ "ADDRESS",        "TEXT NOT NULL"},
                 SQL_cell{ "AGE",            "INT NOT NULL"},
                 SQL_cell{ "SEX",            "INT NOT NULL"}
        });
}


void add_admin_account_if_not_exists(SQLWork* db) {
    if (db->get_text("LOGIN", "admin", 2) == "") {

        const string salt = Account::get_generated_salt();
        const string salted_hash_password = Account::get_generated_hash("admin", salt);

        db->push_back({ "'admin'", "'Admin'", "'" + salted_hash_password + "'", "'" + salt + "'", "1", "1", "1" });
    }
}


