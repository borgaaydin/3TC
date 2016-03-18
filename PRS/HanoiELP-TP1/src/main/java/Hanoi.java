import tc.elp.java.datastructures.Stack;
import tc.elp.java.datastructures.StackByArray;
import tc.elp.java.datastructures.StackByLinkedList;

/**
 * Created by borga on 19/02/16.
 */
public class Hanoi {


    public static void move(Stack src, Stack dest) {
        int tmp = src.top();
        src.pop();
        dest.push(tmp);
    }

    public static void hanoi(Stack src, Stack tmp, Stack dest, int N) {
        if(N > 1) {
            hanoi(src,dest,tmp,N-1);
            move(src,dest);
            hanoi(tmp,src,dest,N-1);
        }
        else {
            move(src,dest);
        }
    }

    public static void main( String[] args )
    {
        final int N = 9;
        Stack s1 = new StackByArray();
        Stack s2 = new StackByLinkedList();
        Stack s3 = new StackByArray();
        for(int i=N;i>0;i--){
            s1.push(i);
        }
        System.out.println("--- Test 1 ---");
        System.out.println("");
        System.out.println("Setting up Hanoi of size "+N+":");
        System.out.println(s1.toString());
        System.out.println(s2.toString());
        System.out.println(s3.toString());
        System.out.println("--- --- ---");
        hanoi(s1,s1,s3,N);
        System.out.println("After the execution of Hanoi Algorithm:");
        System.out.println(s1.toString());
        System.out.println(s2.toString());
        System.out.println(s3.toString());
        System.out.println("--- --- ---");
        System.out.println("");
        System.out.println("--- Test 2 ---");
        System.out.println("Call for Hanoi Algorithm with a size of 4:");
        hanoi(s3,s2,s1,4);
        System.out.println(s1.toString());
        System.out.println(s2.toString());
        System.out.println(s3.toString());
    }
}
