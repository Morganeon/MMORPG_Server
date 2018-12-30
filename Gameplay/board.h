#ifndef BOARD_H
#define BOARD_H

#include <QString>



class Board
{
public:
    Board(int width, int height);
    Board(QString filename);
    void setData(int x, int y, int val);
    int getData(int x, int y);
    int getWidth() {return m_width;}
    int getHeight() {return m_height;}

private:
    void getDataFromFile(QString filename);

    int m_width;
    int m_height;
    int * m_data;
};

#endif // BOARD_H
