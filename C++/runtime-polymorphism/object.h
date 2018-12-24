
#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void draw( const int& x, ostream& out, size_t pos  )
{
    out << string( pos, ' ' ) << x << endl;
}

class object_t {
  public:
    object_t( const int& x) : self_(x)
    {}

    friend void draw( const object_t& x, ostream& out, size_t pos )
    {
        draw( x.self_, out, pos );
    }

  private:
    int self_;
};

using document_t = vector<object_t>;

void draw( const document_t& doc, ostream& out, size_t pos )
{
    string indent( pos, ' ' );

    out << indent << "<Document>" << endl;
    for( const auto& e: doc )
    {
        draw( e, out, pos + 2 );
    }
    out << indent << "</Document>" << endl;
}
