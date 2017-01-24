package sn;

class Hello {

    private String message;
    private int times;

    public Hello( String message, int times ) {

        this.message = message;
        this.times   = times;
    }

    public void say() {
        for ( int i = 0; i < this.times; i ++ ) {
            System.out.format( "%2d - %s\n", i, this.message );
        }
    }
}

public class Main {

    public static void main( String[] args ) {

        int defaultCount = 10;
        Hello hello;

        try {
            if ( args.length == 2 ) {
                hello = new Hello( args[0], Integer.parseInt( args[1] ) );
            } else if ( args.length == 1 ) {
                hello = new Hello( args[0], defaultCount );
            } else {
                hello = new Hello( "Hello there", defaultCount );
            }

            hello.say();
        } catch ( Throwable e ) {
            System.out.format( "%s - %s\n", "Splat!", e.getMessage() );
            e.printStackTrace();
        }
    }
}

