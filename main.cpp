#include <iostream>
#include "cell.h"
#include "spreadsheet.h"
#include "date.h"
#include "test.h"

int main()
{   
    Color r = Color::Red;
    Spreadsheet sp(4, 5);
    Cell cl("30082003", r);    
    Date dt((Month(12)), (Day(99)), (Year(2003)));
    dt.print();
    dt = cl.toDate();
    dt.print();
    // testCellValues();
    // testSpreadsheetValue();
    sp.setCellAt(1, 1, cl);
    std::cout << sp.getRowCount() << std::endl;
    sp.addRow(3);
    std::cout << sp.getRowCount() << std::endl;
    sp.init();
    sp.print();
}