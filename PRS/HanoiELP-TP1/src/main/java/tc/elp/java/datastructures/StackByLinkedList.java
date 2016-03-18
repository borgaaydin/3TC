package tc.elp.java.datastructures;

/**
 * Created by borga on 19/02/16.
 */
public class StackByLinkedList extends LinkedListNode implements Stack {

    private LinkedListNode root;

    public StackByLinkedList(int value) {
        super(value);
    }

    public StackByLinkedList() {
        super(0);
    }

    public boolean empty(){
        if(root==null) return true;
        else return false;
    };

    public int top(){
        return root.value();
    };

    public void push(int element) {
        LinkedListNode tmp = root;
        LinkedListNode newRoot = new LinkedListNode(element, tmp);
        root = newRoot;
    }

    public void pop() {
        root = root.next();
    }

    public String toString() {
        String s = "";
        LinkedListNode cur = root;

        while(cur != null) {
            s += " ," + cur.value();
            cur = cur.next();
        }
        String reverse = new StringBuffer(s).reverse().toString();
        return reverse;
    }

}
