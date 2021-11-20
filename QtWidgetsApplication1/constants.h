#pragma once
#include <string>
#include <QFont>
#include <QString>

namespace DB 
{

	namespace ACCOUNTS 
	{
		const QString FILENAME = "accounts.db";
		const QString NAME = "ACCOUNTS";

		namespace FIELD 
		{
			const QString LOGIN = "LOGIN";
			const QString NAME = "NAME";
			const QString HASH = "HASH";
			const QString SALT = "SALT";
			const QString ROLE = "ROLE";
			const QString ACCESS = "ACCESS";
			const QString ID = "ID";
		}

		namespace INT 
		{
			const int LOGIN = 0;
			const int NAME = 1;
			const int HASH = 2;
			const int SALT = 3;
			const int ROLE = 4;
			const int ACCESS = 5;
			const int ID = 6;
		}
	}

	namespace BOOKS 
	{
		const QString FILENAME = "books.db";
		const QString NAME = "BOOKS";

		namespace FIELD 
		{
			const QString ID = "ID";
			const QString NAME = "NAME";
			const QString AUTHOR = "AUTHOR_NAME";
			const QString GENRE = "GENRE";
			const QString YEAR = "YEAR";
			const QString PAGES = "AMOUNT_OF_PAGE";
			const QString CONTENT = "CONTENT";
			const QString IMG_PATH = "PATH_TO_IMG";
			const QString GIVE_DATE = "DATE_OF_GIVING";
			const QString RETURN_DATE = "DATE_OF_REPEAT";
			const QString ENABLED = "ENABLED";
		}

	}

	namespace PEOPLE 
	{
		const QString FILENAME = "people.db";
		const QString NAME = "PEOPLE";

		namespace FIELD 
		{
			const QString ID = "ID";
			const QString BOOK_ID = "BOOK_ID";
			const QString NAME = "NAME";
			const QString PHONE = "PHONE";
			const QString ADDRESS = "ADDRESS";
			const QString AGE = "AGE";
			const QString SEX = "SEX";
		}

	}

	namespace FIELD_SETTING 
	{
		const QString TEXT_PRIMARY = "TEXT PRIMARY KEY NOT NULL";
		const QString INT_PRIMARY = "INT PRIMARY KEY NOT NULL";
		const QString TEXT = "TEXT NOT NULL";
		const QString INT = "INT NOT NULL";
	}
}

namespace FONTS 
{
	const QFont UBUNTU_8("Ubuntu", 8);
	const QFont UBUNTU_10("Ubuntu", 10);
	const QFont UBUNTU_12("Ubuntu", 12);
	const QFont UBUNTU_14("Ubuntu", 14);
	const QFont UBUNTU_16("Ubuntu", 16);
}




namespace COLORS 
{
	const QString BLUE = "#7AB2FF";
	const QString LIGHT_BLUE ="#9CC5FF";
	const QString WHITE = "#FFFFFF";
	const QString CREAM = "#FFD69C";
	const QString LIGHT_CREAM = "#FFE2B9";
	const QString TRANSPARENT = "transparent";
	const QString RED = "#F5685D";
	const QString DARK_GREEN = "#7FBF52";
	const QString PURPLE = "#D69CFF";
	const QString LIGHT_PURPLE = "#DDADFF";
	const QString GREEN = "#AEFF75";
	const QString LIGHT_GREEN = "#C1FF96";
	const QString LIGHT_RED = "#FF7373";
	const QString BACK = "#FFF1DE";
}

namespace STYLE 
{

	namespace COLOR 
	{
		const QString RED = "color: #F5685D; ";
		const QString WHITE = "color: #FFFFFF; ";
		const QString DARK_GREEN = "color: #7fbf52; ";
	}

	namespace BACKGROUNG 
	{
		const QString TRANSPARENT = "background: transparent; ";
		const QString GREEN = "background: #AEFF75; ";
		const QString LIGHT_RED = "background: #FF7373; ";
		const QString CREAM = "background-color: #FFD69C; ";
		const QString LIGHT_CREAM = "background: #FFE2B9; ";
		const QString LIGHT_GREEN = "background: #C1FF96; ";
		const QString BLUE = "background: #7AB2FF; ";
		const QString LIGHT_BLUE = "background: #9CC5FF; ";
		const QString PURPLE = "background: #D69CFF; ";
		const QString LIGHT_PURPLR = "background: #DDADFF; ";

	}

	namespace BORDER 
	{
		const QString RADIUS_5 = "border-radius: 5px; ";
		const QString RADIUS_10 = "border-radius: 10px; ";
		const QString RADIUS_20 = "border-radius: 20px; ";
		const QString RADIUS_30 = "border-radius: 30px; ";
		const QString SIZE_10 = "border: 10px; ";
		const QString SIZE_2 = "border: 2px; ";
		const QString SOLID = "border-style: solid; ";
		const QString LITE_CREAM = "border-color: #FFE2B9; ";
		const QString DARK_GREEN = "border-color: #7FBF52; ";
		const QString RED = "border-color: #F5685D; ";


		namespace WIDTH 
		{
			const QString _2 = "border-width: 2px; ";
		}
	}

	namespace ALIGN 
	{
		const QString RIGHT = "text-align: right; ";
	}

	namespace PADDING 
	{
		const QString RIGHT_10 = "padding-right: 10px; ";
		const QString LEFT_10 = "padding-left: 10px; ";
	}
}

const int SALT_SIZE = 16;


