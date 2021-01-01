#include "field.h"

int to_int(char chr)
{
    return int(chr) - 48;
}

char to_char(int chr)
{
    return char(chr + 48);
}

Field::Field()
{
    ifstream file(MAP);

    file >> SIZE;
    create_field();

    char cur_value;

    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            file >> cur_value;

            if (cur_value != CHAR_WHITE)
            {
                map[y][x].set_color(BLACK);
                map[y][x].set_number( to_int(cur_value) );

                coor_black_cell.push_back(Coor_cell(y, x));
            }
        }
    }

    file.close();
}

Field::~Field()
{
    for (int i = 0; i < SIZE; i++)
        delete[] map[i];
    delete[] map;
}

int Field::get_size()
{
    return SIZE;
}

List<Coor_cell> Field::find_free_seats()
{
    List<Coor_cell> seats;
    
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            if ( map[y][x].is_white() && 
                !map[y][x].is_lantern() && 
                !map[y][x].is_mark_prohidited_cell() &&
                !map[y][x].is_illuminated_cell() )
                seats.push_back(Coor_cell(y, x));
        }
    }

    return seats;
}

List<Coor_cell> Field::find_seats_for_black_cell(int _y, int _x)
{
    List<Coor_cell> seats;
    int y, x;

    //вверх
    y = _y - 1;
    if (!map[y][_x].is_mark_prohidited_cell() && is_check_board(y, _x))
        seats.push_back(Coor_cell(y, _x));
    
    //вниз
    y = _y + 1;
    if (!map[y][_x].is_mark_prohidited_cell() && is_check_board(y, _x))
        seats.push_back(Coor_cell(y, _x));
    
    //влево
    x = _x - 1;
    if (!map[_y][x].is_mark_prohidited_cell() && is_check_board(_y, x))
        seats.push_back(Coor_cell(_y, x));
    
    //вправо
    x = _x + 1;
    if (!map[_y][x].is_mark_prohidited_cell() && is_check_board(_y, x))
        seats.push_back(Coor_cell(_y, x));    

    return seats;
}

void Field::mark_illuminated_area(int _y, int _x)
{
    //вверх
    for (int y = _y-1; y >= 0; y--)
        if (map[y][_x].is_white())
            map[y][_x].set_illuminated();
        else 
            break;

    //вниз
    for (int y = _y+1; y < SIZE; y++)
        if (map[y][_x].is_white())
            map[y][_x].set_illuminated();
        else 
            break;

    //влево
    for (int x = _x-1; x >= 0; x--)
        if (map[_y][x].is_white())
            map[_y][x].set_illuminated();
        else
            break;
        

    //вправо
    for (int x = _x+1; x < SIZE; x++)
        if (map[_y][x].is_white())
            map[_y][x].set_illuminated();
        else
            break;
}
    
void Field::install_lantern(int y, int x)
{
    map[y][x].set_lantern();
    mark_illuminated_area(y, x);    
}

bool Field::is_full_covered_field()
{
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            if ( map[y][x].is_white() && 
                !map[y][x].is_illuminated_cell() )
                    return false;
        }
    }

    return true;
}

void Field::remove_mark_illuminated_area(int _y, int _x)
{
    //вверх
    for (int y = _y-1; y >= 0; y--)
        if (map[y][_x].is_white())
            map[y][_x].delete_illuminated();
        else 
            break;
    //вниз
    for (int y = _y+1; y < SIZE; y++)
        if (map[y][_x].is_white())
            map[y][_x].delete_illuminated();
        else 
            break;

    //влево
    for (int x = _x-1; x >= 0; x--)
        if (map[_y][x].is_white())
            map[_y][x].delete_illuminated();
        else
            break;
    
    //вправо
    for (int x = _x+1; x < SIZE; x++)
        if (map[_y][x].is_white())
            map[_y][x].delete_illuminated();
        else
            break;
}

void Field::remove_lantern(int y, int x)
{
    map[y][x].delete_lantern();
    remove_mark_illuminated_area(y, x);
}

string Field::to_show()
{
    Color::Modifier fg_white(Color::FG_WHITE);
    Color::Modifier fg_yellow(Color::FG_YELLOW);
    Color::Modifier fg_def(Color::FG_DEFAULT);

    Color::Modifier bg_white(Color::BG_WHITE);
    Color::Modifier bg_black(Color::BG_BLACK);
    Color::Modifier bg_blue(Color::BG_BLUE);
    Color::Modifier bg_def(Color::BG_DEFAULT);
    
    std::stringstream ss;

    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            if (map[y][x].is_black())
                ss << bg_black << fg_white << map[y][x].get_number() << fg_def;
            if (map[y][x].is_white())
            {
                if (!map[y][x].is_illuminated_cell())
                {
                    if (map[y][x].is_mark_prohidited_cell())
                        ss << bg_white << 'x';
                    else 
                        ss << bg_white << ' ';
                }    
                else if (map[y][x].is_illuminated_cell() && !map[y][x].is_lantern())
                {
                    if (map[y][x].is_mark_prohidited_cell())
                        ss << bg_blue << 'x';
                    else                
                        ss << bg_blue << ' ';
                }
                else if (map[y][x].is_illuminated_cell() && map[y][x].is_lantern())
                    ss << bg_blue << fg_yellow << '*' << fg_def;
            }  
                
        }
        ss << '\n';
    }

    ss << bg_def;

    return ss.str();
}

void Field::create_field()
{
    map = new Cell*[SIZE];
    for (int i = 0; i < SIZE; i++)
        map[i] = new Cell[SIZE];
}

bool Field::is_check_board(int y, int x)
{
    return (y < 0 || y >= SIZE || x < 0 || x >= SIZE)? false : true;
}