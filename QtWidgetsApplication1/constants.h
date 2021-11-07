#pragma once
#include <string>

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

const int SALT_SIZE = 16;





