#include "csv.h"
#include <fstream>

int main(void)
{
    std::ofstream cvs_file;
    cvs_file.open("example.csv");
    CSV csv;
    csv.create_row();
    csv.append(0,"int");
    csv.append(0,"double");
    csv.create_row();
    csv.append(1,64);
    csv.append(1,128.50);
    csv.write(cvs_file);
    cvs_file.close();
    return 0;
}
