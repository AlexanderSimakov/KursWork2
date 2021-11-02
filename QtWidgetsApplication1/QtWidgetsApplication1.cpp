#include "QtWidgetsApplication1.h"
#include <QFontDatabase>

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.lineEdit_9->setVisible(false);
    QFontDatabase::addApplicationFont("Fonts/Ubuntu-RI.ttf");
    adjust_fonts();
}

void QtWidgetsApplication1::init() {
    login_page = new LoginPage(this, &ui, accounts_db);
    book_page = new BookPage(this, &ui, books_db, people_db);
    account_page = new AccountPage(this, &ui, accounts_db);
}

void QtWidgetsApplication1::set_accounts_db(SQLWork* db) {
    this->accounts_db = db;
}

void QtWidgetsApplication1::set_books_db(SQLWork* db) {
    this->books_db = db;
}

void QtWidgetsApplication1::set_people_db(SQLWork* db) {
    this->people_db = db;
}

void QtWidgetsApplication1::log_in() 
{
    current_account = login_page->get_authorized_account();
    if (current_account.get_role() == 1) {
        ui.choise_account_page->setEnabled(true);
        ui.choise_account_page->setVisible(true);
        ui.stackedWidget->setCurrentWidget(ui.adminMainPage);
        open_books_page();
    }
    else if (current_account.get_role() == 0) {
        ui.choise_account_page->setEnabled(false);
        ui.choise_account_page->setVisible(false);
        ui.stackedWidget->setCurrentWidget(ui.adminMainPage);
        open_books_page();
    }
}

void QtWidgetsApplication1::back_to_accounts() 
{
    ui.stackedWidget->setCurrentWidget(ui.adminMainPage);
    open_accounts_page();
}

void QtWidgetsApplication1::back_to_authorization() {
    if (QMessageBox::Yes == QMessageBox::question(this, "Exit Confirmation", "Exit?", QMessageBox::Yes | QMessageBox::No)) {
        login_page->open();
        qDeleteAll(ui.page_2->children());
    }
}

void QtWidgetsApplication1::open_books_page() {
    update_current_account_info();
    clear_all_mark_buttons();
    mark_books_button();
    login_page->clear_error_message();
    login_page->clear_password_input();
    ui.adminMainPage_my_account_button->setText(QString::fromStdString(current_account.get_name()));
    ui.stackedWidget->setCurrentWidget(ui.adminMainPage);
    ui.stackedWidget_2->setCurrentWidget(ui.page_3);
    book_page->start();
}

void QtWidgetsApplication1::open_subsriber_page() {
    update_current_account_info();
    clear_all_mark_buttons();
    mark_subscriber_button();
    ui.stackedWidget->setCurrentWidget(ui.adminMainPage);
    ui.stackedWidget_2->setCurrentWidget(ui.page);
    people_page = new PeoplePage(this, &ui, people_db, books_db);
    people_page->start();
}

void QtWidgetsApplication1::open_accounts_page() {
    update_current_account_info();
    clear_all_mark_buttons();
    mark_accounts_button();
    ui.stackedWidget->setCurrentWidget(ui.adminMainPage);
    ui.stackedWidget_2->setCurrentWidget(ui.page_2);
    account_page->start();
}

void QtWidgetsApplication1::open_editing_current_account_page() {
    account_page->open_edit_account_page(current_account, false, false, false);
}

void QtWidgetsApplication1::update_current_account_info() {
    string id = to_string(current_account.get_id());
    current_account.set_login(accounts_db->get_text("ID", id, 0));
    current_account.set_name(accounts_db->get_text("ID", id, 1));
    current_account.set_salted_hash_password(accounts_db->get_text("ID", id, 2));
    current_account.set_salt(accounts_db->get_text("ID", id, 3));
    current_account.set_role(accounts_db->get_int("ID", id, 4));
    current_account.set_access(accounts_db->get_int("ID", id, 5));
}

void QtWidgetsApplication1::clear_all_mark_buttons() {
    ui.choise_books_page->setStyleSheet("QPushButton#choise_books_page{ background: #FFD69C; border: 10px; } QPushButton#choise_books_page:hover{ background: #FFE2B9; }");
    ui.choise_subscriber_page->setStyleSheet("QPushButton#choise_subscriber_page{ background: #FFD69C; border: 10px; } QPushButton#choise_subscriber_page:hover{ background: #FFE2B9; }");
    ui.choise_account_page->setStyleSheet("QPushButton#choise_account_page{ background: #FFD69C; border: 10px; } QPushButton#choise_account_page:hover{ background: #FFE2B9; }");
}

void QtWidgetsApplication1::mark_books_button() {
    ui.choise_books_page->setStyleSheet("QPushButton#choise_books_page{ background: #FFE2B9; border: 10px; } ");
}

void QtWidgetsApplication1::mark_subscriber_button() {
    ui.choise_subscriber_page->setStyleSheet("QPushButton#choise_subscriber_page{ background: #FFE2B9; border: 10px; } ");
}

void QtWidgetsApplication1::mark_accounts_button() {
    ui.choise_account_page->setStyleSheet("QPushButton#choise_account_page{ background: #FFE2B9; border: 10px; } ");
}

void QtWidgetsApplication1::adjust_fonts() {
    ui.choise_books_page->setFont(QFont("Ubuntu", 14));
    ui.choise_subscriber_page->setFont(QFont("Ubuntu", 14));
    ui.choise_account_page->setFont(QFont("Ubuntu", 14));
    ui.adminMainPage_my_account_button->setFont(QFont("Ubuntu", 12));
    ui.exit_button->setFont(QFont("Ubuntu", 14));
}

