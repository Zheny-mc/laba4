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

                coor_black_cell.push_back(Coor_cell(y, x, to_int(cur_value)));
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

List<Coor_cell> Field::find_prohibition_places()
{
    List<Coor_cell> seats;
    int y, x;
    int _y, _x;

    for (int i = 0; i < coor_black_cell.size(); i++)
    {
        if (coor_black_cell[i].number == PROHIBITION_PLACES)
        {
            _y = coor_black_cell[i].y;
            _x = coor_black_cell[i].x;

            //вверх
            y = _y - 1;
            if (is_check_board(y, _x) && map[y][_x].is_white())
                seats.push_back(Coor_cell(y, _x));
            
            //вниз
            y = _y + 1;
            if (is_check_board(y, _x) && map[y][_x].is_white())
                seats.push_back(Coor_cell(y, _x));
            
            //влево
            x = _x - 1;
            if (is_check_board(_y, x) && map[_y][x].is_white())
                seats.push_back(Coor_cell(_y, x));
            
            //вправо
            x = _x + 1;
            if (is_check_board(_y, x) && map[_y][x].is_white())
                seats.push_back(Coor_cell(_y, x));    
        }
    }

    return seats;
}

void Field::install_prohibition_place(int y, int x)
{
    map[y][x].set_mark_prohidited();
}

List<Coor_cell> Field::find_not_illuminate_seat()
{
    List<Coor_cell> seats;
    
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            if ( map[y][x].is_white() && 
                !map[y][x].is_lantern() && 
                !map[y][x].is_mark_prohidited_cell() &&
                !map[y][x].is_illuminated_cell() &&
                is_not_neighbor_black_cell(y, x) )
            {
                seats.push_back(Coor_cell(y, x));
                goto out;
            }
        }
    }

    out:
        return seats;
}

bool Field::is_not_neighbor_black_cell(int _y, int _x)
{
    bool neighbor = false;

    int y, x;
    //вверх
    y = _y - 1;
    if (is_check_board(y, _x) && map[y][_x].is_black() && map[y][_x].get_number() != 5)
        neighbor = true;
    //вниз
    y = _y + 1;
    if (is_check_board(y, _x) && map[y][_x].is_black() && map[y][_x].get_number() != 5)
        neighbor = true;
    //влево
    x = _x - 1;
    if (is_check_board(_y, x) && map[_y][x].is_black() && map[y][_x].get_number() != 5)
        neighbor = true;
    //вправо
    x = _x + 1;
    if (is_check_board(_y, x) && map[_y][x].is_black() && map[y][_x].get_number() != 5)
        neighbor = true;    

    return !neighbor;
}

List<Coor_cell> Field::make_coor_black_cells()
{
    List<Coor_cell> seats;
    int y, x;
    int _y, _x;
    
    for (int i = 0; i < coor_black_cell.size(); i++)
    {
        if (coor_black_cell[i].number != PROHIBITION_PLACES)
        {
            int num_lampern = 0;
            _y = coor_black_cell[i].y;
            _x = coor_black_cell[i].x;
            
            //вверх
            y = _y - 1;
            if (is_check_board(y, _x) && (!map[y][_x].is_mark_prohidited_cell() && !map[y][_x].is_illuminated_cell()) )
                num_lampern++;
            
            //вниз
            y = _y + 1;
            if (is_check_board(y, _x) && (!map[y][_x].is_mark_prohidited_cell() && !map[y][_x].is_illuminated_cell()) )
                num_lampern++;
            
            //влево
            x = _x - 1;
            if (is_check_board(_y, x) && (!map[_y][x].is_mark_prohidited_cell() && !map[_y][x].is_illuminated_cell()) )
                num_lampern++;
            
            //вправо
            x = _x + 1;
            if (is_check_board(_y, x) && (!map[_y][x].is_mark_prohidited_cell() && !map[_y][x].is_illuminated_cell()) )
                num_lampern++;

            if (coor_black_cell[i].number == num_lampern)
                seats.push_back(coor_black_cell[i]);
        }        
    }
    
    return seats;
}

List<Coor_cell> Field::find_seats_around_black_cell()
{
    List<Coor_cell> seats = make_coor_black_cells();
    List<Coor_cell> coor_lampern;
    int y, x;
    int _y, _x;
    
    for (int i = 0; i < seats.size(); i++)
    { 
        _y = seats[i].y;
        _x = seats[i].x;
        
        //вверх
        y = _y - 1;
        if (is_check_board(y, _x) && (!map[y][_x].is_mark_prohidited_cell() && !map[y][_x].is_illuminated_cell()) )
            coor_lampern.push_back(Coor_cell(y, _x));
        
        //вниз
        y = _y + 1;
        if (is_check_board(y, _x) && (!map[y][_x].is_mark_prohidited_cell() && !map[y][_x].is_illuminated_cell()) )
            coor_lampern.push_back(Coor_cell(y, _x));
        
        //влево
        x = _x - 1;
        if (is_check_board(_y, x) && (!map[_y][x].is_mark_prohidited_cell() && !map[_y][x].is_illuminated_cell()) )
            coor_lampern.push_back(Coor_cell(_y, x));
        
        //вправо
        x = _x + 1;
        if (is_check_board(_y, x) && (!map[_y][x].is_mark_prohidited_cell() && !map[_y][x].is_illuminated_cell()) )
            coor_lampern.push_back(Coor_cell(_y, x));
    }
    
    return coor_lampern;
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
                ss << bg_black << fg_white << map[y][x].get_number() << fg_def << bg_def;
            if (map[y][x].is_white())
            {
                if (!map[y][x].is_illuminated_cell())
                {
                    if (map[y][x].is_mark_prohidited_cell())
                        ss << bg_white << 'x' << bg_def;
                    else 
                        ss << bg_white << ' ' << bg_def;
                }    
                else if (map[y][x].is_illuminated_cell() && !map[y][x].is_lantern())
                {
                    if (map[y][x].is_mark_prohidited_cell())
                        ss << bg_blue << 'x' << bg_def;
                    else                
                        ss << bg_blue << ' ' << bg_def;
                }
                else if (map[y][x].is_illuminated_cell() && map[y][x].is_lantern())
                    ss << bg_blue << fg_yellow << '*' << fg_def << bg_def;
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