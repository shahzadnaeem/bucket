#include <iostream>
#include <exception>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "misc.h"

using namespace std;
 
struct Foo {
    int count = std::uncaught_exceptions();
    ~Foo() {
        std::cout << (count == std::uncaught_exceptions()
            ? "~Foo() called normally\n"
            : "~Foo() called during stack unwinding\n");
    }
};

void fooExceptions()
{
    Foo f;
    try {
        Foo f;
        std::cout << "Exception thrown\n";
        throw std::runtime_error("test exception");
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << '\n';
    }
}

void vecOps()
{
    vector<int> vi { 1, 3, 5, 7, 10, 8, 6};

    for_each( vi.begin(), vi.end(), []( auto& i ) { cout << i << endl; } );

    vector<string> vs { Q_UNIQ(x), Q_UNIQ(y), Q_UNIQ(y), Q_UNIQ2(z) };

    for_each( vs.begin(), vs.end(), []( auto& i ) { cout << i << endl; } );
}

void scopedGuards()
{
    char file[] = "/tmp/shaz.delete.me.XXXXXX";
    auto fd = mkstemp( file );
    SCOPE_EXIT { close(fd); unlink(file); };
    char cmd[1024];
    sprintf( cmd, "/bin/bash -c \"ls -l /proc/self/fd/%d\"", fd );

    cout << "Look... (" << cmd << ")" << endl;

    system( cmd );
}

int main()
{
    scopedGuards();
}
