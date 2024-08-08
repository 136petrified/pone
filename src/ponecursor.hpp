#ifndef PONE_CURSOR_HPP
#define PONE_CURSOR_HPP

class Cursor {
public:
    // Cursor constructor
    // ---------------------------------------------  
    Cursor();
    Cursor(const unsigned &x, const unsigned &y);

    // Cursor setter/getter functions
    // ---------------------------------------------
    unsigned getX() const;
    void setX();

    unsigned getY() const;
    void setY();

    // Cursor destructor
    // ---------------------------------------------
    ~Cursor();

private:
    // Cursor attributes
    // ---------------------------------------------
    unsigned x, y;      // where is the cursor?
};

#endif // PONE_CURSOR_HPP