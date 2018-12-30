#include "mapdata.h"

#include <QDebug>

MapData::MapData(QString tile, QString block)
{
    m_tiles = new Board(tile);
    m_block = new Board(block);
    qInfo()<< m_tiles->getData(0,0) << m_tiles->getData(1,1);
}

MapData::~MapData()
{
    delete m_tiles;
    delete m_block;
}
