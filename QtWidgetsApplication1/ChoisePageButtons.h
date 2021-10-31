#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include <QMessageBox>
#include <QPainter>
#include <string>
#include "Page.h"

using namespace std;

class ChoisePageButtons : public QMainWindow
{
	Q_OBJECT

public:
	ChoisePageButtons(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, QWidget* page, const int NUMBER_OF_ELEMENTS_ON_PAGE, int* current_page, Page& _page);
	void set_number_of_elements(int number_of_elements);
	void show();
	void delete_buttons();


private:
	Page& _page;
	QWidget* page;
	int* current_page;
	const int NUMBER_OF_ELEMENTS_ON_PAGE;
	int number_of_elements;
	const int ADD = 50;
	const int START_X = 10;
	const int START_Y = 650; // 675 true
	const int SIZE = 40;

	void create_button(int num_in_list, int page_num);
	void create_line(int num_in_list);

};

