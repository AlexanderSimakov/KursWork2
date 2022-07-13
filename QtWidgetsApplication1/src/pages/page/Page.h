#pragma once
#include <vector>
#include <algorithm>
#include <QString>

using namespace std;

class Page
{
public:
	virtual void update_window() = 0; // функция обновления экрана
	static int get_min_nonexist(vector<int> vect); // возвращение минимального несуществующего элемента из вектора типа int
	QString get_current_format_date(); // возвращает текущую дату
};

