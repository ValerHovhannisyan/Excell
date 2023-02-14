#include <iostream>
#include "cell.h"
#include "spreadsheet.h"
#include "date.h"
/*
Spreadsheet::~Spreadsheet()
{
  std::cout << "The end!" << std::endl;
}
*/

bool Spreadsheet::operator!=(const Spreadsheet& other) const
{
    if (rowCount != other.rowCount || columnCount != other.columnCount)
    {
        return true;
    }
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            if (m_cells[i][j] != other.m_cells[i][j])
            {
                return true;
            }
        }
    }
    return false;
}

Spreadsheet::Spreadsheet(int rc, int cc)
{
    rowCount = rc;
    columnCount = cc;
    m_cells = new Cell*[rowCount];
    for (int i = 0; i < rowCount; ++i)
    {
        m_cells[i] = new Cell[columnCount];
    }
}

int Spreadsheet::getRowCount() const {
    return rowCount;
}

int Spreadsheet::getColumnCount() const {
    return columnCount;
}

void Spreadsheet::setCellAt(int r, int c, const Cell& cl)
{
    if (r >= 0 && r < rowCount && c >= 0 && c < columnCount)
    {
        for (int i = 0; i < rowCount; ++i)
        {
            for (int j = 0; j < columnCount; ++j)
            {
                if(i == r && j == c)
                {
                    m_cells[i][j] = cl;
                }
            }
        }
    }
}

void Spreadsheet::setCellAt(int r, int c, const std::string& st)
{
    if (r >= 0 && r < rowCount && c >= 0 && c < columnCount)
    {
        for (int i = 0; i < rowCount; ++i)
        {
            for (int j = 0; j < columnCount; ++j)
            {
                if (i == r && j == c)
                {
                    m_cells[i][j].setValue(st);
                }
            }
        }
    }   
}

Cell Spreadsheet::getCellAt(int r, int c)
{
    if (r >= 0 && r < rowCount && c >= 0 && c < columnCount)
    {
        for (int i = 0; i < rowCount; ++i)
        {
            for (int j = 0; j < columnCount; ++j)
            {
                if (i == r && j == c)
                {
                    return m_cells[i][j];
                }
            }
        }
    }
    return Cell();
}

void Spreadsheet::addRow(int r)
{
    if (r >= 0 && r < rowCount)
    {
        ++rowCount;
        Cell** newCells = new Cell*[rowCount];
        for (int i = 0; i < rowCount; ++i)
        {
            m_cells[i] = new Cell[columnCount];
        }
        for (int i = 0; i < r; ++i)
        {
            newCells[i] = m_cells[i];
        }
        newCells[r] = new Cell[columnCount];
        for (int i = r + 1; i < rowCount; ++i)
        {
            newCells[i] = m_cells[i - 1];
        }
        delete [] m_cells;
        m_cells = newCells;
        newCells = nullptr;
    }
}

void Spreadsheet::removeRow(int r)
{
    if (r >= 0 && r < rowCount)
    {
        --rowCount;
        Cell** newCells = new Cell*[rowCount];
        for (int i = 0; i < rowCount; ++i)
        {
            m_cells[i] = new Cell[columnCount];
        }
        for (int i = 0; i < r; ++i)
        {
            newCells[i] = m_cells[i];
        }
        for (int i = r + 1; i < rowCount; ++i)
        {
            newCells[i] = m_cells[i + 1];
        }
        delete [] m_cells;
        m_cells = newCells;
        newCells = nullptr;
    }
}

void Spreadsheet::addColumn(int c)
{
    if (c >= 0 && c < columnCount)
    {
        ++columnCount;
        for (int i = 0; i < rowCount; ++i)
        {
            Cell* tmp = new Cell[columnCount];
            for (int j = 0, t = 0; j < columnCount; ++j, ++t)
            {
                if (j == c) { --t; continue; }
                tmp[j] = m_cells[i][t];
            }
            std::swap(m_cells[i], tmp);
            delete[] tmp;
            tmp = nullptr;
        }
    }
}

void Spreadsheet::removeColumn(int c)
{
    if (c >= 0 && c < columnCount)
    {
        --columnCount;
        Cell** newCells = new Cell*[rowCount];
        for (int i = 0; i < rowCount; ++i)
        {
            m_cells[i] = new Cell[columnCount];
        }
        for (int i = 0; i < columnCount; ++i)
        {
            for (int j = 0; j < rowCount; ++j)
            {
                if (i < c)
                {
                    newCells[i][j] = m_cells[i][j];
                }
                if (i == c)
                {
                    continue;
                }
                if (i > c)
                {
                    newCells[i - 1][j] = m_cells[i][j];
                }
            }
        }
        delete [] m_cells;
        m_cells = newCells;
        newCells = nullptr;
    }
}

void Spreadsheet::swapRows(int r1, int r2)
{
    Cell* tmp;
    for (int i = 0; i < rowCount; ++i)
    {
        if (i == r1)
        {
            tmp = m_cells[r1];
            m_cells[r1] = m_cells[r2];
            m_cells[r2] = tmp;
        }
    }
}

void Spreadsheet::swapColumns(int c1, int c2)
{
    Cell tmp;
    for (int i = 0; i < columnCount; ++i)
    {
        for (int j = 0; j < rowCount; ++j)
        { 
            if (i == c1)
            {
                tmp = m_cells[c1][j];
                m_cells[c1][j] = m_cells[c2][j];
                m_cells[c2][j] = tmp;
            }
        }
    }
}

void Spreadsheet::print()
{
    std::cout << "Row = " << rowCount << std::endl;
    std::cout << "Column = " << columnCount << std::endl;
    auto it = m_cells;
    for (int i = 0; i < rowCount; ++i)
    {
        auto ptr = it[i];
        std::cout << i << " ";
         for (int j = 0; j < columnCount; ++j)
         {
            std::cout << ptr[j].getValue()  << " ";
         }
         std::cout << '\n';
    }
}

void Spreadsheet::init()
{
    for (int i = 0; i < rowCount; ++i)
    {
        for (int j = 0; j < columnCount; ++j)
        {
            this->setCellAt(i, j, "C++");
        }
    }
}