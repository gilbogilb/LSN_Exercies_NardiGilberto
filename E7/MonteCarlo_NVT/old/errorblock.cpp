//cpp code to try to get a error(blocksize) relation
//gn may 26th, 2021

#include <iostream>
#include <fstream>

#include "DataBlocks.h"

int count(std::ifstream& in){
    int c=0;
    double tmp;
    while(!in.eof()){
        in >> tmp;
        c++;
    }

    in.clear();
    in.seekg(0);

return --c;
}

int main() {

    std::ifstream in("output/autocorrU.dat");
    int blocksizes[20] = {100,  122,  150,  185,  227,  279,  343,  422,  519,  637,  783,  962, 1183, 1453,
 1785, 2194, 2695, 3312, 4069, 4999,};
    int filesize = count(in);
    std::ofstream out("error_blocks.dat");

    std::cout << filesize << "\n\n";

    DataBlockingTool tool("trash.dat",blocksizes[0]);
    double tmp;

    for(int i=0; i<filesize; ++i){
        in >> tmp >> tmp;
        tool.AppendValue(tmp);
    }

    out << tool.GetSize() << " " << tool.GetError() << std::endl;
    std::cout << tool.GetSize() << " " << tool.GetError() << std::endl;
    in.clear();
    in.seekg(0);

    for(int i=1; i<20; ++i){
        tool.Reset("trash.dat",blocksizes[i]);
        for(int j=0; j<filesize; ++j){
        in >> tmp >> tmp;
        tool.AppendValue(tmp);
    }

    out << tool.GetSize() << " " << tool.GetError() << std::endl;
    std::cout << tool.GetSize() << " " << tool.GetError() << std::endl;
    in.clear();
    in.seekg(0);
    }

in.close();
out.close();

return 0;
}