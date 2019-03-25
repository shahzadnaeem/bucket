
#include <iostream>

#include "object.h"
#include "benchmarks.h"

using namespace std;

int main()
{
    cout << "Ok!" << endl;

    document_t doc;

    for( int i = 0; i < 5; i ++) {
        doc.emplace_back(i);
    }

    draw( doc, cout, 0);

    runTest<StringToInt>();
    runTest<StringToIntVec>();
}