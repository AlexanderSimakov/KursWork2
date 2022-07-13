#pragma once
#include <QFont>
#include <QFontDatabase>
#include <string>

using namespace std;

enum FontSize{SMALL = 8, MEDIUM = 10, LARGE = 12, EXTRA_LARGE = 14};
enum FontColor{DARK, LITE, RED};

class Fonts
{
public:
	static QFont getFont(FontSize size);
	static string getColorCode(FontColor color);




};

