#pragma once
#include <string>
#include <QFont>

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
	const string BLUE = "#7AB2FF";
	const string LIGHT_BLUE = "#9CC5FF";
	const string WHITE = "#FFFFFF";
	const string CREAM = "#FFD69C";
	const string LIGHT_CREAM = "#FFE2B9";
	const string TRANSPARENT = "transparent";
	const string RED = "#F5685D";
	const string DARK_GREEN = "#7FBF52";
	const string PURPLE = "#D69CFF";
	const string LIGHT_PURPLE = "#DDADFF";
	const string GREEN = "#AEFF75";
	const string LIGHT_GREEN = "#C1FF96";
	const string LIGHT_RED = "#FF7373";
	const string BACK = "#FFF1DE";
}



const int SALT_SIZE = 16;


