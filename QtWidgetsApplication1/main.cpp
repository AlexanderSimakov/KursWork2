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
    
    SQLWork accounts_db(DB::ACCOUNTS::FILENAME, DB::ACCOUNTS::NAME);
    SQLWork books_db(DB::BOOKS::FILENAME, DB::BOOKS::NAME);
    SQLWork people_db(DB::PEOPLE::FILENAME, DB::PEOPLE::NAME);


    init_accounts_db(&accounts_db);
    init_books_db(&books_db);
    init_people_db(&people_db);

    QtWidgetsApplication1 w;
    w.setFixedSize(QSize(1280, 720));
    
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
                 SQL_cell{ DB::ACCOUNTS::FIELD::LOGIN,  "TEXT PRIMARY KEY NOT NULL"},
                 SQL_cell{ DB::ACCOUNTS::FIELD::NAME,   "TEXT NOT NULL"},
                 SQL_cell{ DB::ACCOUNTS::FIELD::HASH,   "TEXT NOT NULL"},
                 SQL_cell{ DB::ACCOUNTS::FIELD::SALT,   "TEXT NOT NULL"},
                 SQL_cell{ DB::ACCOUNTS::FIELD::ROLE,   "INT NOT NULL"},
                 SQL_cell{ DB::ACCOUNTS::FIELD::ACCESS, "INT NOT NULL"},
                 SQL_cell{ DB::ACCOUNTS::FIELD::ID,     "INT NOT NULL"} });

    add_admin_account_if_not_exists(db);
}

void init_books_db(SQLWork* db) {
    db->open();
    db->create_table_if_not_exists({ 
                 SQL_cell{ DB::BOOKS::FIELD::ID,          "INT PRIMARY KEY NOT NULL"},
                 SQL_cell{ DB::BOOKS::FIELD::NAME,        "TEXT NOT NULL"},
                 SQL_cell{ DB::BOOKS::FIELD::AUTHOR,      "TEXT NOT NULL"},
                 SQL_cell{ DB::BOOKS::FIELD::GENRE,       "TEXT NOT NULL"},
                 SQL_cell{ DB::BOOKS::FIELD::YEAR,        "INT NOT NULL"},
                 SQL_cell{ DB::BOOKS::FIELD::PAGES,       "INT NOT NULL"},
                 SQL_cell{ DB::BOOKS::FIELD::CONTENT,     "TEXT NOT NULL"},
                 SQL_cell{ DB::BOOKS::FIELD::IMG_PATH,    "TEXT NOT NULL"},
                 SQL_cell{ DB::BOOKS::FIELD::GIVE_DATE,   "TEXT NOT NULL"},
                 SQL_cell{ DB::BOOKS::FIELD::RETURN_DATE, "TEXT NOT NULL"},
                 SQL_cell{ DB::BOOKS::FIELD::ENABLED,     "INT NOT NULL"}
        });
}

void init_people_db(SQLWork* db) {
    db->open();
    db->create_table_if_not_exists({
                 SQL_cell{ DB::PEOPLE::FIELD::ID,      "INT PRIMARY KEY NOT NULL"},
                 SQL_cell{ DB::PEOPLE::FIELD::BOOK_ID, "TEXT NOT NULL"},
                 SQL_cell{ DB::PEOPLE::FIELD::NAME,    "TEXT NOT NULL"},
                 SQL_cell{ DB::PEOPLE::FIELD::PHONE,   "TEXT NOT NULL"},
                 SQL_cell{ DB::PEOPLE::FIELD::ADDRESS, "TEXT NOT NULL"},
                 SQL_cell{ DB::PEOPLE::FIELD::AGE,     "INT NOT NULL"},
                 SQL_cell{ DB::PEOPLE::FIELD::SEX,     "INT NOT NULL"}
        });
}


void add_admin_account_if_not_exists(SQLWork* db) {
    if (db->get_text(DB::ACCOUNTS::FIELD::LOGIN, "admin", 2) == "") {

        const string salt = Account::get_generated_salt();
        const string salted_hash_password = Account::get_generated_hash("admin", salt);

        db->push_back({ "'admin'", "'Admin'", "'" + salted_hash_password + "'", "'" + salt + "'", "1", "1", "1" });
    }
}


