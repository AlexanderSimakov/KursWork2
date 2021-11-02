#pragma once

#include <QtWidgets/QMainWindow>
#include <QAction>
#include "ui_QtWidgetsApplication1.h"
#include "helpFunctions.h"
#include "SQLWORK.h"
#include "constants.h"
#include "authorization.h"
#include "Book.h"
#include <QMessageBox>
#include <QFileDialog>
#include "BookPage.h"
#include "AccountPage.h"
#include "PeoplePage.h"
#include "LoginPage.h"

class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = Q_NULLPTR);
    void set_accounts_db(SQLWork* db);
    void set_books_db(SQLWork* db);
    void set_people_db(SQLWork* db);
    void init();


private slots:
    void log_in();
    void back_to_accounts();
    void back_to_authorization();
    void open_books_page();
    void open_subsriber_page();
    void open_accounts_page();
    void open_editing_current_account_page();
   

private:
    SQLWork* accounts_db = nullptr;
    SQLWork* books_db = nullptr;
    SQLWork* people_db = nullptr;
    BookPage* book_page;
    AccountPage* account_page;
    PeoplePage* people_page;
    LoginPage* login_page;

    Account current_account;

    Ui::QtWidgetsApplication1Class ui;

    void update_current_account_info();

    void clear_all_mark_buttons();
    void mark_books_button();
    void mark_subscriber_button();
    void mark_accounts_button();

    void adjust_fonts();
    
};
