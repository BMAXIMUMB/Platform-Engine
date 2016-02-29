// column.h

#ifndef _COLUMN_H_
#define _COLUMN_H_

#include "background.h"

class CColumn :public CBackgroundElement
{

private:

	ColumnSettings info;

	// –асчитывает цвет колонны в зависимости от глубины
	// „ем дальше, тем темнее
	color4 CalculateColor(void);

	// –асчитывает размер по Y в зависимости от глубины
	float CalculateSizeY(void);

	// –асчитывает множитель движени€ колонны в зависимости от глубины
	// „ем дальше колонна, тем медленнее двигаетс€
	float CalculateMoveFactor(void);

public:

	void Create(PE::CWorld *world, ColumnSettings cs);

};

#endif //_COLUMN_H_