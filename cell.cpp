#include "cell.h"

Cell::Cell()
{
    color = WHITE;
    number = NOT_INITIALIZE;
    illuminated = false;
    lantern = false;
    put_lantern = false;
}

void Cell::set_color(bool _color)
{
    color = _color;
}

bool Cell::is_white()
{
    return color == WHITE? true : false;
}

bool Cell::is_black()
{
    return color == BLACK? true : false;
}

void Cell::set_number(int _number)
{
    number = _number;
}

int Cell::get_number()
{
    return number;
}


void Cell::set_lantern()
{
    lantern = true;
    set_illuminated();
}

void Cell::delete_lantern()
{
    lantern = false;
    delete_illuminated();
}

bool Cell::is_lantern()
{
    return lantern;
}


void Cell::set_illuminated()
{
    if (illuminated)
        dual_illuminated = true;
    else
        illuminated = true;
}

void Cell::delete_illuminated()
{
    if (dual_illuminated)
        dual_illuminated = false;
    else
        illuminated = false;
}

bool Cell::is_illuminated_cell()
{
    return illuminated;
}


void Cell::set_mark_prohidited()
{
    put_lantern = true;//поставить фонарь нельзя
}

void Cell::delete_mark_prohidited()
{
    put_lantern = false;
}

bool Cell::is_mark_prohidited_cell()
{
    return put_lantern;
}