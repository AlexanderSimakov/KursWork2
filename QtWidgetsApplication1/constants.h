#pragma once
#include <string>
#include <QFont>
#include <QString>

namespace DB {

	namespace ACCOUNTS {
		const std::string FILENAME = "accounts.db";
		const std::string NAME = "ACCOUNTS";

		namespace FIELD {
			const std::string LOGIN = "LOGIN";
			const std::string NAME = "NAME";
			const std::string HASH = "HASH";
			const std::string SALT = "SALT";
			const std::string ROLE = "ROLE";
			const std::string ACCESS = "ACCESS";
			const std::string ID = "ID";
		}

	}

	namespace BOOKS {
		const std::string FILENAME = "books.db";
		const std::string NAME = "BOOKS";

		namespace FIELD {
			const std::string ID = "ID";
			const std::string NAME = "NAME";
			const std::string AUTHOR = "AUTHOR_NAME";
			const std::string GENRE = "GENRE";
			const std::string YEAR = "YEAR";
			const std::string PAGES = "AMOUNT_OF_PAGE";
			const std::string CONTENT = "CONTENT";
			const std::string IMG_PATH = "PATH_TO_IMG";
			const std::string GIVE_DATE = "DATE_OF_GIVING";
			const std::string RETURN_DATE = "DATE_OF_REPEAT";
			const std::string ENABLED = "ENABLED";
		}

	}

	namespace PEOPLE {
		const std::string FILENAME = "people.db";
		const std::string NAME = "PEOPLE";

		namespace FIELD {
			const std::string ID = "ID";
			const std::string BOOK_ID = "BOOK_ID";
			const std::string NAME = "NAME";
			const std::string PHONE = "PHONE";
			const std::string ADDRESS = "ADDRESS";
			const std::string AGE = "AGE";
			const std::string SEX = "SEX";
		}

	}

	namespace FIELD_SETTING {
		const std::string TEXT_PRIMARY = "TEXT PRIMARY KEY NOT NULL";
		const std::string INT_PRIMARY = "INT PRIMARY KEY NOT NULL";
		const std::string TEXT = "TEXT NOT NULL";
		const std::string INT = "INT NOT NULL";
	}
}

namespace FONTS {
	const QFont UBUNTU_8("Ubuntu", 8);
	const QFont UBUNTU_10("Ubuntu", 10);
	const QFont UBUNTU_12("Ubuntu", 12);
	const QFont UBUNTU_14("Ubuntu", 14);
	const QFont UBUNTU_16("Ubuntu", 16);
}




namespace COLORS {
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

namespace STYLE {

	namespace COLOR {
		const QString RED = "color: #F5685D; ";
	}

	namespace BACKGROUNG {
		const QString TRANSPARENT = "background: transparent; ";
		const QString GREEN = "background: #AEFF75; ";
		const QString LIGHT_RED = "background: #FF7373; ";
		const QString CREAM = "background-color: #FFD69C; ";
		const QString LIGHT_CREAM = "background: #FFE2B9; ";
		const QString LIGHT_GREEN = "background: #C1FF96; ";
	}

	namespace BORDER {
		const QString RADIUS_10 = "border-radius: 10px; ";
		const QString RADIUS_20 = "border-radius: 20px; ";
		const QString RADIUS_30 = "border-radius: 30px; ";
		const QString SOLID = "border-style: solid; ";

	}

	

}

const int SALT_SIZE = 16;


