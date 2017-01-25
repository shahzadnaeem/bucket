package org.shahzad.hello;

class SimpleSayer implements Sayer {

    public void op( String s, int i ) {

        System.out.format( ":o %2d - %s\n", i, s );
    }
}

class CountingSayer implements Sayer {

    private int calls = 0;

    public void op( String s, int i ) {

        System.out.format( "[%d] %2d - %s\n", this.calls, i, s );

        this.calls ++;
    }
}

public class App {

    public static void main( String[] args ) {

        int defaultCount = 10;
        Hello hello;
        Sayer sayer = new CountingSayer();

        try {
            if ( args.length == 2 ) {
                hello = new Hello( args[0], Integer.parseInt( args[1] ) );
            } else if ( args.length == 1 ) {
                hello = new Hello( args[0], defaultCount );
            } else {
                hello = new Hello( "Hello there", defaultCount );
            }

            hello.say( sayer );
        } catch ( Throwable e ) {
            System.out.format( "%s - %s\n", "Splat!", e.getMessage() );
            e.printStackTrace();
        }
    }
}
