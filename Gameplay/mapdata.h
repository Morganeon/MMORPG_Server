#ifndef MAPDATA_H
#define MAPDATA_H

#include "board.h"



class MapData
{
public:
    MapData(QString tile, QString block);
    ~MapData();
    Board * m_tiles;
    Board * m_block;

};

#endif // MAPDATA_H
