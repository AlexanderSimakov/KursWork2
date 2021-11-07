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

/*
colors:
#7ab2ff + blue
#9CC5FF + light blue
#FFFFFF + white
#FFD69C + cream 
#FFE2B9 + light cream
transparent 
#f5685d + red
#7fbf52 + dark green
#D69CFF + purple
#ddadff + light purple
#AEFF75 + green
#c1ff96 + light green
#FF7373 + light red
#FFF1DE + фон

*/

const int SALT_SIZE = 16;


