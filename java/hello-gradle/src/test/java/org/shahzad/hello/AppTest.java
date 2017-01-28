package org.shahzad.hello;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;

class TestSayer implements Sayer {

    public boolean needInit   = true;
    public String  msg        = null;
    public boolean msgChanged = false; 
    public int     count      = 0;

    public void op( String s, int i ) {
        if ( needInit ) {
            this.msg      = s;
            this.count    = 1;
            this.needInit = false;
        } else {
            if ( this.msg != s ) {
                msgChanged = true;
            }

            this.count ++;
        }
    }
}

/**
 * Unit test for simple App.
 */
public class AppTest 
    extends TestCase
{
    /**
     * Create the test case
     *
     * @param testName name of the test case
     */
    public AppTest( String testName )
    {
        super( testName );
    }

    /**
     * @return the suite of tests being tested
     */
    public static Test suite()
    {
        return new TestSuite( AppTest.class );
    }

    public void testHelloContructor()
    {
        String msg = "My words";
        int    num = 102;

        Hello h = new Hello( msg, num );

        assertEquals( msg, h.getMessage() );
        assertEquals( num, h.getTimes() );
    }

    public void testHelloSay() {

        String msg = "My words";
        int    num = 102;

        Hello h      = new Hello( msg, num );
        TestSayer ts = new TestSayer();

        h.say( ts );

        assertEquals( num, ts.count );
        assertFalse( ts.needInit );
        assertFalse( ts.msgChanged );
        assertEquals( msg, ts.msg );
    }
}
