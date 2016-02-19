package tc.elp.java.datastructures;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;

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

    /**
     * Rigourous Test :-)
     */
    public void testApp()
    {
        assertTrue( true );
    }

    /**
     * Check whether the input integer is a power of 2 or not
     * @param i any strictly positive integer
     * @return true if the input integer is a power of 2
     */
    private boolean isPowerOf2(int i) {
        while((i%2) == 0)
            i /= 2;
        return (i == 1);
    }

    /**
     * Simple test
     * @return false in case of failure, true otherwise
     */
    private boolean test() {
        int nb = 0;
        int nbok = 0;

        DynamicArray a = new DynamicArray();

        final int n = 256;
        for (int i = 0; i < n; i++) {
            a.push(i);
            System.err.print(a.size() + "/" + a.capacity() + ", ");
            if (isPowerOf2(i+1)) {
                if ( (a.capacity() == a.size()) )
                    nbok++;
                nb++;
            }
        }

        System.err.println();
        System.err.println(a);

        for (int i = 0; i < n; i++) {
            if (a.get(i) == i)
                nbok++;
            nb++;
        }

        return (nb == nbok);
    }
}
