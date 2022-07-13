#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include <QGroupBox>
#include <vector>
#include <string>
#include "SQLWORK.h"
#include "constants.h"
#include "Page.h"

using namespace std;

struct Search
{
	QString name;
	QString command;
};

class Searching : public QMainWindow
{
	Q_OBJECT
public:
	Searching(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, QWidget* page, SQLWork* db, Page& _page, vector<int>& id);
	void delete_widgets(); // удаление виджета поиска с экрана
	void init(vector<Search> search_commands, int* current_page); // инициализация виджета поиска
	void clear_field(); // очистка поля ввода
	void show(); // вывод на экран
	void set_default_search_method(); // установка метода поиска по умолчанию

private:
	Page& _page;
	SQLWork* db;
	QWidget* page;
	vector<int>& id;
	vector<Search> search_commands;

	QComboBox* combo_box;
	QLineEdit* lineEdit;
	QPushButton* button;

	int* current_page;

	void create_search_button(); // инициализация кнопки поиска
	void create_search_field(); // инициализация поля ввода поискового запроса
	void crete_search_choise_method_button(); // инициализация виджета выбора метода поиска
};

