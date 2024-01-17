#pragma once
#include "Part.h"

class Head : public Part
{

protected:
	void Update() override;
	void move(int _select,int _nowSelect);
private:
	int nowSelect = 0;
	int Select = 0;
};

