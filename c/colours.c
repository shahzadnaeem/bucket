#include <stdio.h>

int main()
{
  puts ( "\x1b[31mRED\n" );
  puts ( "\x1b[31;1mRED BOLD\n" );
  puts ( "\x1b[0mReset?\n" );
}
