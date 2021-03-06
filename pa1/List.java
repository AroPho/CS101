import java.lang.String;
import java.lang.IndexOutOfBoundsException;

public class List {
    private class Node{
        int data;
        Node next;
        Node prev;

        Node(int x){
            data = x;
            next = null;
            prev = null;
        }
    }

    private Node head;
    private Node tail;
    private Node cursor;
    private int cursorInd;
    private int numItems;

    public List(){
        head = tail = cursor =null;
        cursorInd = -1;
        numItems = 0;
    }

    public int length(){
        return numItems;
    }

    public int index(){
        return cursorInd;
    }

    public int front() throws IndexOutOfBoundsException{
        if(numItems > 0) {
            return head.data;
        }else{
            throw new IndexOutOfBoundsException("list is empty");
        }
    }

    public int back(){
        if(numItems > 0) {
            return tail.data;
        }else{
            throw new IndexOutOfBoundsException("list is empty");
        }
    }

    public int get(){
        if(numItems > 0 && cursorInd >= 0 && cursorInd < numItems ) {
            return cursor.data;
        }else{
            return -1;
        }
    }

    public boolean equals(List L){
        if(numItems != L.numItems){
            return false;
        }else{
            Node temp = head;
            Node tempL = L.head;
            for(int x = 0; x < numItems; x++){
                if(temp.data != tempL.data){
                    return false;
                }else{
                    temp = temp.next;
                    tempL = tempL.next;
                }
            }
            return true;
        }
    }
    public void clear(){
        head = tail = cursor = null;
        numItems = 0;
        cursorInd = -1;
    }
    public void moveFront() throws IndexOutOfBoundsException{
        if(numItems == 0){
            //throw new IndexOutOfBoundsException("List is Empty");
        }else{
            cursor = head;
            cursorInd = 0;
        }
    }

    public void moveBack(){
        if(numItems == 0){
            //throw new IndexOutOfBoundsException("List is Empty");
        }else{
            cursor = tail;
            cursorInd = numItems - 1;
        }
    }

    public void movePrev(){
        if(cursorInd != -1 && cursor != head){
            cursor = cursor.prev;
            cursorInd--;
        }else if(cursor == head){
            cursor = null;
            cursorInd = -1;
        }
    }

    public void moveNext(){
        if(cursor != null && cursor != tail){
            cursor = cursor.next;
            cursorInd++;
        }else if(cursor == tail){
            cursor = null;
            cursorInd = -1;
        }
    }

    public void prepend(int data){
        if(numItems == 0){
            head = tail = new Node(data);
            numItems++;
        }else{
            Node temp = head;
            head = new Node(data);
            head.next = temp;
            temp.prev = head;
            numItems++;
            if(cursorInd != -1 ){
                cursorInd++;
            }
        }
    }

    public void append(int data){
        if(numItems == 0){
            head = new Node(data);
            tail = head;
            numItems++;
        }else{
            tail.next = new Node(data);
            tail.next.prev = tail;
            tail = tail.next;
            numItems++;
        }
    }

    public void insertBefore(int data){
        if(numItems !=0 && cursorInd >= 0){
            if(cursorInd == 0){
                prepend(data);
            }else{
                Node A = cursor.prev;
                Node temp = new Node(data);
                A.next = temp;
                temp.prev = A;
                temp.next = cursor;
                cursor.prev = temp;
                cursorInd++;
                numItems++;
            }
        }
    }

    public void insertAfter(int data){
        if(numItems !=0 && cursorInd >= 0){
            if(cursor == tail){
                append(data);
            }else{
                Node A = cursor.next;
                Node temp = new Node(data);
                A.prev = temp;
                temp.next = A;
                temp.prev = cursor;
                cursor.next = temp;
                numItems++;
            }
        }
    }

    public void deleteFront(){
        if(numItems != 0){
            head = head.next;
            head.prev = null;
            numItems--;
            if(cursorInd == 0){
                cursorInd--;
                cursor = null;
            }else if(cursorInd != -1 ){
                cursorInd--;
            }
        }
    }

    public void deleteBack(){
        if(numItems > 0){
            if (cursor == tail){
                cursor = null;
                cursorInd = -1;
            }
            if(numItems == 1){
                tail = null;
                head = null;
                numItems--;
            }else {
                tail = tail.prev;
                tail.next = null;
                numItems--;
            }
        }
    }
    void delete(){
        if(cursorInd == 0 && numItems > 0){
            deleteFront();
        }else if(cursorInd == numItems - 1 && numItems > 0){
            deleteBack();
        }else if(cursorInd >= 0 && numItems != 0){
            Node curprev  = cursor.prev;
            Node curnext = cursor.next;
            curprev.next = curnext;
            curnext.prev = curprev;
            numItems--;
            cursorInd = -1;
            cursor = null;
        }
    }
    private String myString(Node H){
        if( H==null ){
            return "";
        }else{
            return (H.data+ " " +myString(H.next));
        }
    }

    public String toString(){
        return myString(head);
    }

    public List copy(){
        List A = new List();
        Node temp = head;
        while(temp != null){
            A.append(temp.data);
            temp = temp.next;
        }
        return A;
    }

    public List concat(List L){
        List A = new List();
        Node temp = L.head;
        A = copy();
        while(temp != null){
            A.append(temp.data);
            temp = temp.next;
        }
        return A;
    }
    /*public static void main(String[] args){
        List A = new List();
        List B = new List();

        for(int i=1; i<=20; i++){
            A.append(i);
            B.prepend(i);
        }
        System.out.println(A);
        System.out.println(B);

        for(A.moveFront(); A.index()>=0; A.moveNext()){
            System.out.print(A.get()+" ");
        }
        System.out.println();
        for(B.moveBack(); B.index()>=0; B.movePrev()){
            System.out.print(B.get()+" ");
        }
        System.out.println();

        List C = A.copy();
        System.out.println(A.equals(B));
        System.out.println(B.equals(C));
        System.out.println(C.equals(A));
        System.out.println(C);
        System.out.println(A);

        A.moveFront();
        for(int i=0; i<5; i++) A.moveNext(); // at index 5
        A.insertBefore(-1);                  // at index 6
        for(int i=0; i<9; i++) A.moveNext(); // at index 15
        A.insertAfter(-2);
        for(int i=0; i<5; i++) A.movePrev(); // at index 10
        A.delete();
        System.out.println(A);
        System.out.println(A.length());
        A.deleteBack();
        System.out.println(A);
        A.clear();
        System.out.println(A.length());
    }*/
}

// Output of this program:
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// false
// false
// true
// 1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
// 21
// 0

