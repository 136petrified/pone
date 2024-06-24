#ifndef PONE_BOARD_HPP
#define PONE_BOARD_HPP

class Board {
public:
    Board();
    Board(int length, int width);

    void setLength(const int &length);
    int getLength() const;
    
    void setWidth(const int &width);
    int getWidth() const;

    ~Board();
private:
    int length, width;
};

#endif // PONE_BOARD_HPP