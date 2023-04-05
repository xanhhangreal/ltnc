
#ifndef LUOI_CAU_H
#define LUOI_CAU_H

#include "Common_Function.h"
#include "BaseObject.h"

const double GOC_LUOI_CAU = 150.0;

class LuoiCau : public BaseObject
{
public:
    LuoiCau();
    ~LuoiCau();

    void set_x_val(const int& xVal) {x_val_ = xVal;}
    void set_y_val(const int& yVal) {y_val_ = yVal;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}

    void set_is_move(const bool& IsMove) {is_move_ = IsMove;}
    bool get_is_move() const {return is_move_;}

    void HandleMove(const int& x_border, const int& y_border);
private:
    int x_val_;
    int y_val_;
    bool is_move_;

};

#endif // LUOI_CAU_H
