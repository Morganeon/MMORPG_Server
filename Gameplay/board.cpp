#include "board.h"

#include <QFile>

Board::Board(int width, int height)
{
    m_width = width;
    m_height = height;
    m_data = new int[width*height];
}

Board::Board(QString filename)
{
    getDataFromFile(filename);
}

void Board::setData(int x, int y, int val)
{
    m_data[y*m_width+x] = val;
}

int Board::getData(int x, int y)
{
    return m_data[y*m_width+x];
}

void Board::getDataFromFile(QString filename)
{
    QFile f(filename);
    f.open(QFile::ReadOnly);
    QByteArray data = f.readAll();
    QList<QByteArray> lines = data.split('\n');
    QList<QByteArray> values = lines.at(0).split(',');
    m_width = values.size();
    m_height = lines.size();
    m_data = new int[m_width*m_height];
    for (int j=0;j<m_height;j++)
    {
        values = lines.at(j).split(',');
        for (int i=0;i<m_width;i++)
        {
            m_data[j*m_width+i] = values.at(i).toInt();
        }
    }
}
