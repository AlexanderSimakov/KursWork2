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
                 SQL_cell{ DB::ACCOUNTS::FIELD::LOGIN,  DB::FIELD_SETTING::TEXT_PRIMARY},
                 SQL_cell{ DB::ACCOUNTS::FIELD::NAME,   DB::FIELD_SETTING::TEXT},
                 SQL_cell{ DB::ACCOUNTS::FIELD::HASH,   DB::FIELD_SETTING::TEXT},
                 SQL_cell{ DB::ACCOUNTS::FIELD::SALT,   DB::FIELD_SETTING::TEXT},
                 SQL_cell{ DB::ACCOUNTS::FIELD::ROLE,   DB::FIELD_SETTING::INT},
                 SQL_cell{ DB::ACCOUNTS::FIELD::ACCESS, DB::FIELD_SETTING::INT},
                 SQL_cell{ DB::ACCOUNTS::FIELD::ID,     DB::FIELD_SETTING::INT} 
        });

    add_admin_account_if_not_exists(db);
}

void init_books_db(SQLWork* db) {
    db->open();
    db->create_table_if_not_exists({ 
                 SQL_cell{ DB::BOOKS::FIELD::ID,          DB::FIELD_SETTING::INT_PRIMARY},
                 SQL_cell{ DB::BOOKS::FIELD::NAME,        DB::FIELD_SETTING::TEXT},
                 SQL_cell{ DB::BOOKS::FIELD::AUTHOR,      DB::FIELD_SETTING::TEXT},
                 SQL_cell{ DB::BOOKS::FIELD::GENRE,       DB::FIELD_SETTING::TEXT},
                 SQL_cell{ DB::BOOKS::FIELD::YEAR,        DB::FIELD_SETTING::INT},
                 SQL_cell{ DB::BOOKS::FIELD::PAGES,       DB::FIELD_SETTING::INT},
                 SQL_cell{ DB::BOOKS::FIELD::CONTENT,     DB::FIELD_SETTING::TEXT},
                 SQL_cell{ DB::BOOKS::FIELD::IMG_PATH,    DB::FIELD_SETTING::TEXT},
                 SQL_cell{ DB::BOOKS::FIELD::GIVE_DATE,   DB::FIELD_SETTING::TEXT},
                 SQL_cell{ DB::BOOKS::FIELD::RETURN_DATE, DB::FIELD_SETTING::TEXT},
                 SQL_cell{ DB::BOOKS::FIELD::ENABLED,     DB::FIELD_SETTING::INT}
        });
}

void init_people_db(SQLWork* db) {
    db->open();
    db->create_table_if_not_exists({
                 SQL_cell{ DB::PEOPLE::FIELD::ID,      DB::FIELD_SETTING::INT_PRIMARY},
                 SQL_cell{ DB::PEOPLE::FIELD::BOOK_ID, DB::FIELD_SETTING::TEXT},
                 SQL_cell{ DB::PEOPLE::FIELD::NAME,    DB::FIELD_SETTING::TEXT},
                 SQL_cell{ DB::PEOPLE::FIELD::PHONE,   DB::FIELD_SETTING::TEXT},
                 SQL_cell{ DB::PEOPLE::FIELD::ADDRESS, DB::FIELD_SETTING::TEXT},
                 SQL_cell{ DB::PEOPLE::FIELD::AGE,     DB::FIELD_SETTING::INT},
                 SQL_cell{ DB::PEOPLE::FIELD::SEX,     DB::FIELD_SETTING::INT}
        });
}


void add_admin_account_if_not_exists(SQLWork* db) {
    if (db->get_text(DB::ACCOUNTS::FIELD::LOGIN, "admin", 2) == "") {

        const string salt = Account::get_generated_salt();
        const string salted_hash_password = Account::get_generated_hash("admin", salt);

        db->push_back({ "'admin'", "'Admin'", "'" + salted_hash_password + "'", "'" + salt + "'", "1", "1", "1" });
    }
}


