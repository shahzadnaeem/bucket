package org.shahzad.hello;

public class Hello {

    private String message;
    private int times;

    public Hello( String message, int times ) {

        this.message = message;
        this.times   = times;
    }

    public String getMessage() {
        return this.message;
    }

    public int getTimes() {
        return this.times;
    }

    public void say( Sayer s ) {
        for ( int i = 0; i < this.times; i ++ ) {
            s.op( this.message, i );
        }
    }
}

