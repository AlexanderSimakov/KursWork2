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

struct Search {
	string name;
	string command;
};

class Searching : public QMainWindow
{
	Q_OBJECT
public:
	Searching(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, QWidget* page, SQLWork* db, Page& _page, vector<int>& id);
	void delete_widgets();
	void init(vector<Search> search_commands, int* current_page);
	void clear_field();
	void show();
	void set_default_search_method();

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

	void create_search_button();
	void create_search_field();
	void crete_search_choise_method_button();

};

