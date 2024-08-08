#ifndef PONE_CURSOR_HPP
#define PONE_CURSOR_HPP

class Cursor {
public:
    // Cursor constructor
    // ---------------------------------------------  
    Cursor();
    Cursor(const unsigned &x = 0, const unsigned &y = 0);

    // Cursor setter/getter functions
    // ---------------------------------------------
    unsigned getX() const;
    void setX(const unsigned &x);

    unsigned getY() const;
    void setY(const unsigned &y);

    // Cursor destructor
    // ---------------------------------------------
    ~Cursor();

private:
    // Cursor attributes
    // ---------------------------------------------
    unsigned x, y;      // where is the cursor?
};

#endif // PONE_CURSOR_HPP