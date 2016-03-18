package tc.elp.java.datastructures;

/**
 * Created by borga on 19/02/16.
 */
public class StackByArray extends DynamicArray implements Stack {

    public StackByArray(int capacity) {
        super(capacity);
    }

    public StackByArray() {
        super();
    }

    public boolean empty(){
        if (this.size() == 0) return true;
        else return false;
    };

    public int top(){
        return this.get(this.size()-1);
    };

    public void push(int element) {
        super.push(element);
    }

    public void pop() {
        this.removeLast();
    }

    public String toString() { return super.toString(); }

}
