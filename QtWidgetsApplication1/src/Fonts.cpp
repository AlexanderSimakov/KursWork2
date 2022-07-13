#include "Fonts.h"

QFont Fonts::getFont(FontSize size) {
	QFontDatabase::addApplicationFont("Fonts/Ubuntu-RI.ttf");
	QFont font("Ubuntu", size);
	return font;
	
}

string Fonts::getColorCode(FontColor color) {
	switch (color)
	{
	case DARK:
		return "color: #737373";
		break;
	case LITE:
		return "color: #FFFFFF";
		break;
	case RED:
		return "color: #FF7373";
		break;
	default:
		return "color: #000000";
		break;
	}
}
