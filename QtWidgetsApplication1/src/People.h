#pragma once
#include <string>
#include "SQLWORK.h"
#include "constants.h"
#include <QString>

class People
{
public:
	void set_id(int id); // ��������� id
	void set_book_id(int book_id); // ��������� id ������ �����
	void set_name(QString name); // ��������� �����
	void set_phone(QString phone); // ��������� ������ ��������
	void set_address(QString address); // ��������� ������
	void set_age(int age); // ��������� ��������
	void set_sex(int sex); // ��������� ����

	int get_id(); // ���������� id
	int get_book_id(); // ���������� id �����
	QString get_name(); // ���������� ���
	QString get_phone(); // ���������� ����� ��������
	QString get_address(); // ���������� �����
	int get_age(); // ���������� �������
	int get_sex(); // ���������� ���

	void add_in_db(SQLWork* people_db); // ���������� ������� � �������
	static People get_people_by_book_id(SQLWork* people_db, int book_id); // ����������� ������� �� ������� �� ��� id

private:
	int id = 0;
	int book_id = 0;
	QString name = "";
	QString phone = "";
	QString address = "";
	int age = 0;
	int sex = 0;
};

