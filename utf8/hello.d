/**
*/
void hello()
{
    import std.stdio : writeln;
    import std.string : format;
    import std.range : chain;
    
    // ------------------------------------------------------------------------

    writeln("Hello World!");

    writeln( format( "%s: %d\n", __FILE__, __LINE__ ) );

    auto a = [ 1, 2, 3];
    auto b = [ 5, 4, 3 ];

    auto c = chain( a, b );

    writeln( c );
}

/**
*/
string[] readFile( int i, string file )
{
    import std.stdio : File, writeln;
    import std.array : appender;
    import std.string : strip;

    cast(void)(i);

    File f = File( file, "r" );

    string[] lines;

    while ( ! f.eof() ) {
        lines ~= strip(f.readln());
    }

    f.close();

    return lines;
}

/**
*/
void fileCounter( string [] args )
{
    import std.stdio : writeln;
    import std.string : format;
    import std.algorithm : filter, map, sum;
    import std.conv : to;
    
    foreach ( int i, string arg; args[1..$] ) {
        const auto lines = readFile( i + 1, arg );
        const auto nlines = lines.length;
        const auto tot = lines
                            .filter!( l => l != "")
                            .map!(to!int).sum;

        writeln( format( "File #%d: '%s': lines: %d, sum = %d", i, arg, nlines, tot ) );
    }

}

/**
*/
void unicode2utf8( string[] args )
{
    import std.array : appender;
    import std.stdio : write, writeln;
    import std.string : format;
    import std.conv : ConvException, to, hexString;
    import std.uni : toUpper;

    foreach ( int i, string arg; args[1..$] ) {
        try {        
            const auto codePoint = to!int( arg, 16 );
            dchar u32 = cast(dchar) codePoint;

            // writeln( format( "%d (0x%X) => %s", codePoint, codePoint, u32 ) );

            auto u8 = format( "%s", u32 );
            auto op = appender!string;

            op ~= "echo -e \"";

            foreach( ch; u8 ) 
            {
                auto c = cast(ubyte) ch;
                op ~= format( "\\x%2x", c );
            }

            op ~= "\" # ";
            op ~= u8;
            op ~= " U+" ~ arg.toUpper;

            writeln( op.data );
        } catch ( ConvException e )
        {
            writeln( format( "'%s' is NOT valid Unicode HEX", arg ) );
        }
    }

}

void main( string[] args )
{
    // hello();

    // fileCounter( args );

    unicode2utf8( args );
}
