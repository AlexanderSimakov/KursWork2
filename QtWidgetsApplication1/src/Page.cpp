#include "Page.h"

int Page::get_min_nonexist(vector<int> vect) 
{
	int min_nonexistent = 1;

	if (vect.size() != 0)
	{
		for (int i = 0; i < *max_element(vect.begin(), vect.end()) + 2; i++)
		{
			if (vect.end() == find(vect.begin(), vect.end(), min_nonexistent))
				break;

			min_nonexistent++;
		}
	}
	return min_nonexistent;
}

QString Page::get_current_format_date() 
{
	time_t now = time(0);
	tm* ltm = localtime(&now);

	QString day;
	QString month;

	int day_i = ltm->tm_mday;
	if (day_i < 10) 
		day = "0" + QString::number(day_i);
	else 
		day = QString::number(day_i);

	int month_i = 1 + ltm->tm_mon;
	if (month_i < 10)
		month = "0" + QString::number(month_i);
	else
		month = QString::number(month_i);

	QString year(QString::number(1900 + ltm->tm_year));
	QString date = day + "." + month + "." + year;

	return date;
}
