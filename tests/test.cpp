#include <iostream>
#include <vector>
#include <sstream>

#include "mgraph.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    mGraph m;
    string buf;
    do
    {
        getline(cin, buf);
        if(buf.empty()){
            break;
        }
        istringstream iss_buf(buf);
        Edge edg;
        iss_buf>>edg.from;
        iss_buf>>edg.to;
        m.insert(edg);
        

    } while (true);

    cout<<m.to_string();    

    return 0;
}
