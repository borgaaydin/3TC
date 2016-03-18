package tc.elp.java.datastructures;

import java.util.Arrays;

/**
 * Created by borga on 18/02/16.
 */
public class DynamicArray {
    // The storage for the elements.
    // The capacity is the length of this array.
    private int[] myArray;

    // The number of elements (logical size).
    // It must be smaller than the capacity.
    private int mySize;

    // Constructs an empty DynamicArray
    public DynamicArray()
    {
        myArray = new int[0];
        mySize = 0;
    }

    // Constructs an empty DynamicArray with the
    // specified initial capacity.
    public DynamicArray(int capacity)
    {
        if (capacity < 16)
            capacity = 16;
        myArray = new int[capacity];
        mySize = 0;
    }

    // Increases the capacity, if necessary, to ensure that
    // it can hold at least the number of elements
    // specified by the minimum capacity argument.
    public void checkCapacity(int minCapacity)
    {
        int oldCapacity = myArray.length;
        if (minCapacity > oldCapacity)
        {
            int newCapacity = (oldCapacity * 2);
            if (newCapacity < minCapacity)
                newCapacity = minCapacity;
            myArray = Arrays.copyOf(myArray, newCapacity);
        }
    }

    // Appends the specified element to the end.
    public void push(int element)
    {
        checkCapacity(mySize + 1);
        myArray[mySize++] = element;
    }

    public void push(int index, int element){
        rangeCheck(index);
        checkCapacity(mySize + 1);

        int[] newArray = new int[mySize + 1];
        for(int i = 0; i < index; i++) {
            newArray[i] = myArray[i];
        }
        myArray[index] = element;
        for(int i = index+1; i < mySize+1; i++) {
            newArray[i] = myArray[i];
        }

        for(int i = 0; i < mySize+1; i++) {
            myArray[i] = newArray[i];
        }

    }

    // Checks if the given index is in the range.
    private void rangeCheck(int index)
    {
        if (index >= mySize || index < 0)
            throw new IndexOutOfBoundsException("Index: " +
                    index + ", Size: " + mySize);
    }

    // Returns the element at the specified position.
    public int get(int index)
    {
        rangeCheck(index);
        return myArray[index];
    }

    public void removeLast(){
        rangeCheck(0);
        myArray[mySize-1]=0;
        mySize--;
    }

    public int size()
    {
        return mySize;
    }

    public int capacity()
    {
        return myArray.length;
    }

    public String toString(){
        String toString = " ";
        for(int i = 0; i < mySize; i++) {
            toString += myArray[i] + ", ";
        }
        return toString;
    }
}
