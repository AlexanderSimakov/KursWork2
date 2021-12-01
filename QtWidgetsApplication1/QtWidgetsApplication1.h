#pragma once
#include <QtWidgets/QMainWindow>
#include <QAction>
#include "ui_QtWidgetsApplication1.h"
#include "SQLWORK.h"
#include "constants.h"
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
    void set_accounts_db(SQLWork* db); // передача таблицы аккаунтов
    void set_books_db(SQLWork* db); // передача таблицы книг
    void set_people_db(SQLWork* db); // передача таблицы людей
    void init();


private slots:
    void log_in(); // слот срабатывающий на нажатие кнопки авторизации
    void back_to_accounts(); // слот срабатывающий на нажатие кнопки возвращения к аккаунтам
    void back_to_authorization(); // слот срабатывающий на нажатие кнопки выхода
    void open_books_page(); // слот срабатывающий на нажатие кнопки выбора страницы книг
    void open_subsriber_page(); // слот срабатывающий на нажатие кнопки выбора страницы людей
    void open_accounts_page(); // слот срабатывающий на нажатие кнопки выбора страницы аккаунтов
    void open_editing_current_account_page(); // слот срабатывающий на нажатие кнопки редактирования своего аккаунта
   
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

    void update_current_account_info(); // обновление информации о аккаунте из которого был произведен вход

    void clear_all_mark_buttons(); // убирает выделение с кнопок выбора страниц
    void mark_books_button(); // выделяет кнопку выбора страницы книг
    void mark_subscriber_button(); // выделяет кнопку выбора страницы людей
    void mark_accounts_button(); // выделяет кнопку выбора страницы аккаунтов

    void adjust_fonts(); // настройка стилей шрифтов для страницы
};
