#include "resProperties.h"


void resProperties::setId(int resId)
{
	id = resId;
	switch(id) {
	case ID_BSTONE:
		alw = ID_BSTONE_ALW;
		weight = 5;
		score = 22;
		break;
    case ID_SSTONE:
		alw = ID_SSTONE_ALW;
		weight = 3;
		score = 11;
		break;
	case ID_BGOLD:
		alw = ID_BGOLD_ALW;
		weight = 5;
		score = 500;
		break;
    case ID_SGOLD:
        alw = ID_SGOLD_ALW;
        weight = 2;
        score = 50;
        break;
	case ID_DIAMOND:
		alw = ID_DIAMOND_ALW;
		weight = 1;
		score = 600;
		break;
	case ID_BAG:
		alw = ID_BAG_ALW;
		weight = 3;
		score = 450;
		break;
	case -1:
		alw = 0;
		weight = 0;
		score = 0;
		break;
	}
}

resProperties::resProperties(int resId)
{
	this->setId(resId);
    /// thay bằng return thử
}
