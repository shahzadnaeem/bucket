
#pragma once

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

void draw( const int& x, ostream& out, size_t pos  )
{
    out << string( pos, ' ' ) << x << endl;
}

class object_t {
  public:
    object_t( const int& x) : self_(make_unique<int_model_t>(x))
    {}

    object_t( const object_t& x) : self_(make_unique<int_model_t>(*x.self_))
    {}

    object_t& operator=( const object_t& x)
    {
        object_t tmp(x); self_ = move(tmp.self_); return *this;
    }

    friend void draw( const object_t& x, ostream& out, size_t pos )
    {
        x.self_->draw( out, pos );
    }

  private:
    struct int_model_t {
        int_model_t( const int& x ) : data_(x)
        {}

        void draw( ostream& out, size_t pos ) const
        {
            ::draw( data_, out, pos );
        }

        int data_;
    };

    unique_ptr<int_model_t> self_;
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
