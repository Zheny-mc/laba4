#define BLACK false
#define WHITE true
#define NOT_INITIALIZE -1

class Cell
{
public:
    Cell();

    void set_color(bool _color);
    bool is_white();
    bool is_black();

    void set_number(int _number);
    int  get_number();

    void set_lantern();
    void delete_lantern();
    bool is_lantern();

    void set_illuminated();
    void delete_illuminated();
    bool is_illuminated_cell();

    void set_mark_prohidited();
    void delete_mark_prohidited();
    bool is_mark_prohidited_cell();
    
private:
    bool color;
    int  number;
    bool illuminated;
    bool dual_illuminated;
    bool lantern;
    bool put_lantern;
};