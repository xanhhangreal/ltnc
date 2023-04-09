#ifndef RES_PROPERTIES_H_
#define RES_PROPERTIES_H_

#include "Common_Function.h"

class resProperties {
public:
	int score;
	resProperties(int resId = -1);

	void setId(int resId);
	double getAlw();
	int getId();
	double getWeight();

private:
    int id;
	double alw;
	double weight;
};

#endif // RES_PROPERTIES_H_
