#pragma once

#include <list>

using namespace std;

class LgbDrawableBag
{
public:

	LgbDrawableBag(void)
	~LgbDrawableBag(void);

	int getSelectedIcons( const CPoint *point, list< LgbDrawable * > &selected);
};
