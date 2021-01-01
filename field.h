#include <string>
#include <fstream>
#include <sstream>
#include "colormod.h"
#include "cell.h"
#include "List.cpp"

using std::string;
using std::ifstream;

#define CHAR_WHITE '*'
#define MAP "map.txt"

int to_int(char chr);
char to_char(int chr);

class Coor_cell
{
public:
    int y;
    int x;
    
    Coor_cell(int _y=0, int _x=0) : y(_y), x(_x) {}
};

class Field
{
public:
    Field();
    ~Field();

    int get_size();

    List<Coor_cell> find_free_seats();
    List<Coor_cell> find_seats_for_black_cell(int _y, int _x);
    
    void mark_illuminated_area(int _y, int _x);
    void install_lantern(int y, int x);

    void remove_mark_illuminated_area(int _y, int _x);
    void remove_lantern(int y, int x);

    bool is_full_covered_field();

    string to_show();

private:
    void create_field();
    bool is_check_board(int y, int x);

private:
    int SIZE;
    Cell** map;

public:
    List<Coor_cell> coor_black_cell;

};


