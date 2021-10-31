#include "ChoisePageButtons.h"

ChoisePageButtons::ChoisePageButtons(QWidget* parent, Ui::QtWidgetsApplication1Class* ui, QWidget* page, const int NUMBER_OF_ELEMENTS_ON_PAGE, int* current_page, Page& _page)
	: QMainWindow(parent), NUMBER_OF_ELEMENTS_ON_PAGE(NUMBER_OF_ELEMENTS_ON_PAGE), _page(_page) {
	this->current_page = current_page;
	this->page = page;
}



void ChoisePageButtons::set_number_of_elements(int number_of_elements) {
	this->number_of_elements = number_of_elements;
}

void ChoisePageButtons::show() {
	delete_buttons();
	if (number_of_elements > NUMBER_OF_ELEMENTS_ON_PAGE) {
		const int NUMBER_OF_PAGES = (number_of_elements / NUMBER_OF_ELEMENTS_ON_PAGE) + (number_of_elements % NUMBER_OF_ELEMENTS_ON_PAGE > 0 ? 1 : 0);
		if (NUMBER_OF_PAGES < 7) {
			for (int i = 0; i < NUMBER_OF_PAGES; i++) {
				create_button(i, i);
			}
		}
		else if (*current_page < 4) {
			for (int i = 0; i < 5; i++) {
				create_button(i, i);
			}
			create_line(5);
			create_button(6, NUMBER_OF_PAGES - 1);
		}
		else if (*current_page >= NUMBER_OF_PAGES - 4) {
			create_button(0, 0);
			create_line(1);
			for (int i = 2, page = NUMBER_OF_PAGES - 5; i < 7; i++, page++) {
				create_button(i, page);
			}
		}
		else {
			create_button(0, 0);
			create_line(1);
			create_button(2, *current_page - 1);
			create_button(3, *current_page);
			create_button(4, *current_page + 1);
			create_line(5);
			create_button(6, NUMBER_OF_PAGES - 1);
		}
	}
}

void ChoisePageButtons::create_button(int num_in_list, int page_num) {
	QPushButton* choise_page_button = new QPushButton(QString::fromStdString(to_string(page_num + 1)), page);
	choise_page_button->setGeometry(START_X + (num_in_list * ADD), START_Y, SIZE, SIZE);
	choise_page_button->setObjectName("choise_page_button");
	if (*current_page == page_num) {
		choise_page_button->setStyleSheet("QPushButton#choise_page_button { background: #FFE2B9; border-radius: 10px; }");
	}
	else {
		choise_page_button->setStyleSheet("QPushButton#choise_page_button { background: #FFD69C; border-radius: 10px; } QPushButton#choise_page_button::hover { background: #FFE2B9; }");
	}
	choise_page_button->show();
	connect(choise_page_button, &QPushButton::clicked, this,
		[=]() {
			*current_page = choise_page_button->text().toInt() - 1;
			_page.update_window();
		});
	choise_page_button->show();
}

void ChoisePageButtons::create_line(int num_in_list) {
	QLabel* line = new QLabel("", page);
	line->setStyleSheet("background: #FFD69C");
	line->setGeometry(START_X + (num_in_list * ADD), START_Y + SIZE / 2 - 1, SIZE, 3);

	line->show();
}

void ChoisePageButtons::delete_buttons() {
	qDeleteAll(page->findChildren<QPushButton*>(QString::fromStdString("choise_page_button")));
}