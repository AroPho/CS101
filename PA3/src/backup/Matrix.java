import java.awt.*;
import java.io.*;


public class Matrix {

    private class Point{
        int column;
        double ent;

        Point(int c, double x){
            column = c;
            ent = x;
        }
        public boolean equals(Object x){
            Point e;
            if(x instanceof Point) {
                e = (Point) x;
                if (column == e.column && ent == e.ent) {
                    return true;
                }
            }
            return false;
        }
        public String toString(){
            return ("(" + column + ", " + ent + ")");
        }

    }

    private int size;
    private int nonzeros;
    private List[] matrix;

    // Constructor
    Matrix(int n){ // Makes a new n x n zero Matrix. pre: n>=1
        if(n > 0) {
            size = n;
            nonzeros = 0;
            matrix = new List[n];
            for(int x = 0; x < n;x++){
                matrix[x] = new List();
            }
        }
    }

    // Access functions
    int getSize() {// Returns n, the number of rows and columns of this Matrix
        return size;
    }
    int getNNZ(){ // Returns the number of non-zero entries in this Matrix
        return nonzeros;
    }

    public boolean equals(Object x) {
        Matrix temp;
        if(x instanceof Matrix) {
            temp = (Matrix) x;
            //System.out.println(temp);
            if(getSize() != temp.getSize()) {
                return false;
            }
            for(int i = 0; i < getSize(); i++) {
                if(!(matrix[i].equals(temp.matrix[i]))){
                    return false;
                }
            }

        }
        return true;
    } // overrides Object's equals() method

    public double dot(List A, List B) {
        double product = 0.0;
        A.moveFront();
        B.moveFront();
        while(A.index() != -1 && B.index() != -1)
        {
            Point ent1 = (Point) A.get();
            Point ent2 = (Point) B.get();
            if(ent1.column > ent2.column) {
                B.moveNext();
            }else if(ent1.column < ent2.column) {
                A.moveNext();
            }else {
                product += (ent1.ent * ent2.ent);
                A.moveNext();
                B.moveNext();
            }
        }
        return product;
    }

    // Manipulation procedures

    void makeZero(){
        for(int x = 0; x < size; x++){
            matrix[x].clear();
        }
        nonzeros = 0;
    } // sets this Matrix to the zero state

    Matrix copy(){
        Matrix A = new Matrix(size);
        for(int x = 0; x < size; x++){
            matrix[x].moveFront();
            while(matrix[x].index() != -1){
                Point temp = (Point) matrix[x].get();
                A.changeEntry(x+1, temp.column, temp.ent);
                matrix[x].moveNext();
            }
        }
        return A;
    }// returns a new Matrix having the same entries as this Matrix

    void changeEntry(int i, int j, double x){
        Point temp = new Point(j, x);
        Point current;
        //System.out.println(i);
        List list = matrix[i-1];
        if(list.length() == 0 && temp.ent != 0){
            list.append(temp);
            nonzeros++;
        }else {
            list.moveFront();
            current = (Point) list.get();
            while(list.index() != -1 && current.column < j){
                //System.out.print(list.index());
                list.moveNext();
                current = (Point) list.get();
            }if(list.index() == -1){
                if(temp.ent != 0){
                    list.append(temp);
                    nonzeros++;
                }
            }else if(current.column > j){
                if(temp.ent != 0){
                    list.insertBefore(temp);
                    nonzeros++;
                }
            }else if(current.column == temp.column){
                if(temp.ent != 0){
                    list.insertBefore(temp);
                    list.delete();

                }else{
                    //System.out.println(list);
                    list.delete();
                    nonzeros--;
                }
            }
        }
    }
    // changes ith row, jth column of this Matrix to x
    // pre: 1<=i<=getSize(), 1<=j<=getSize()

    Matrix scalarMult(double x){
        Matrix A = new Matrix(size);
        for(int i = 1; i <= size;i++){
            List Ltemp = matrix[i-1];
            Point temp;
            Ltemp.moveFront();
            while(Ltemp.get() != null){
                temp = (Point) Ltemp.get();
                A.changeEntry(i, temp.column, (temp.ent * x) );
                Ltemp.moveNext();
            }
        }
        return A;
    }

    // returns a new Matrix that is the scalar product of this Matrix with x

    Matrix add(Matrix M) {
        Matrix A = new Matrix(size);
        Point aent, bent;
        if(this == M){
            A = this.scalarMult(2);
            return A;
        }
        for (int i = 1; i <= size; i++) {
            List a = this.matrix[i-1];
            List b = M.matrix[i-1];
            a.moveFront();
            b.moveFront();
            int count = 1;
            while(count <= size){
                if(a.index() != -1 && b.index() == -1){
                        aent = (Point) a.get();
                        if(aent.column == count){
                        A.changeEntry(i, aent.column, aent.ent);
                        a.moveNext();
                        }
                }else if(b.index() != -1 && a.index() == -1){
                        bent = (Point) b.get();
                        if(bent.column == count){
                        A.changeEntry(i, bent.column, bent.ent);
                        b.moveNext();
                        }
                }else{
                    aent = (Point) a.get();
                    bent = (Point) b.get();
                    //System.out.println(this);
                    //System.out.println(a.get());
                    if(aent.column == bent.column){
                        if(aent.column == count) {
                            A.changeEntry(i, aent.column, (aent.ent + bent.column));
                            a.moveNext();
                            b.moveNext();
                        }else{
                            a.moveNext();
                            b.moveNext();
                        }
                    }else if(aent.ent == count && bent.ent != count){
                        A.changeEntry(i,count, aent.ent);
                        a.moveNext();
                    }else if(bent.ent == count && aent.ent != count){
                        A.changeEntry(i,count, bent.ent);
                        b.moveNext();
                    }
                }
                count++;
            }
        }
        return A;
    }
    // returns a new Matrix that is the sum of this Matrix with M
    // pre: getSize()==M.getSize()

    Matrix sub(Matrix M){
        Matrix A = new Matrix(size);
        Point aent, bent;
        if(this == M){
            return A;
        }
        for (int i = 1; i <= size; i++) {
            List a = this.matrix[i-1];
            List b = M.matrix[i-1];
            a.moveFront();
            b.moveFront();
            int count = 1;
            while(count <= size){
                if(a.index() != -1 && b.index() == -1){
                  aent = (Point) a.get();  
                  if(aent.column == count) {
                        A.changeEntry(i, aent.column, aent.ent);
                        a.moveNext();
                    }
                }else if(b.index() != -1 && a.index() == -1){
                    bent = (Point) b.get();
                    if(bent.column == count) {
                        A.changeEntry(i, bent.column, -bent.ent);
                        b.moveNext();
                    }
                }else{
                    aent = (Point) a.get();
                    bent = (Point) b.get();
                    //System.out.println(this);
                    //System.out.println(a.get());
                    if(aent.column == bent.column){
                        if(aent.column == count) {
                            A.changeEntry(i, aent.column, (aent.ent - bent.column));
                            a.moveNext();
                            b.moveNext();
                        }else{
                            a.moveNext();
                            b.moveNext();
                        }
                    }else if(aent.ent == count && bent.ent != count){
                        A.changeEntry(i,count, aent.ent);
                        a.moveNext();
                    }else if(bent.ent == count && aent.ent != count){
                        A.changeEntry(i,count, -bent.ent);
                        b.moveNext();
                    }
                }
                count++;
            }
        }
        return A;
    }

    // returns a new Matrix that is the difference of this Matrix with M
    // pre: getSize()==M.getSize()
    Matrix transpose(){
        Matrix temp = new Matrix(size);
        for(int x  = 0; x < size; x++){
            List a = this.matrix[x];
            a.moveFront();
            while(a.index() != -1){
                Point ent = (Point) a.get();
                temp.changeEntry(ent.column, x+1, ent.ent);
                a.moveNext();
            }
        }
        return temp;
    }
    // returns a new Matrix that is the transpose of this Matrix

    Matrix mult(Matrix M){
        if(getSize() != M.getSize()){
            return null;
        }
        Matrix temp = M.transpose();
        //System.out.println(this);
        //System.out.println(temp);
        Matrix A = new Matrix(size);
        for(int y = 1; y <= size; y++){
            for(int x = 1; x <= size;x++){
                //System.out.println("(" + x +", " + y +")");
                if(this.matrix[y-1].length()!= 0 && temp.matrix[x-1].length() != 0) {
                    A.changeEntry(y, x, dot(this.matrix[y - 1], temp.matrix[x - 1]));
                }
            }
        }
        return A;
    }
    // returns a new Matrix that is the product of this Matrix with M
    // pre: getSize()==M.getSize()

    // Other functions
    public String toString(){
        String out = "";
        int count = 0;
        for(int i = 0; i < size; i++){
            if(matrix[i].length() != 0){
                out += ((i+1) + ": " + matrix[i] + "\n");
            }
        }
        return out;
    }// overrides Object's toString() method

    public static void main(String[] args){
        int i, j, n=3;
        Matrix A = new Matrix(n);
        Matrix B = new Matrix(n);

        A.changeEntry(1,1,1); B.changeEntry(1,1,1);
        A.changeEntry(1,2,2); B.changeEntry(1,2,0);
        A.changeEntry(1,3,3); B.changeEntry(1,3,1);
        A.changeEntry(2,1,4); B.changeEntry(2,1,0);
        A.changeEntry(2,2,5); B.changeEntry(2,2,1);
        A.changeEntry(2,3,6); B.changeEntry(2,3,0);
        A.changeEntry(3,1,7); B.changeEntry(3,1,1);
        A.changeEntry(3,2,8); B.changeEntry(3,2,1);
        A.changeEntry(3,3,9); B.changeEntry(3,3,1);

        System.out.println(A.getNNZ());
        System.out.println(A);

        System.out.println(B.getNNZ());
        System.out.println(B);

        /*Matrix C = A.scalarMult(1.5);
        System.out.println(C.getNNZ());
        System.out.println(C);


        Matrix D = A.add(A);
        System.out.println(D.getNNZ());
        System.out.println(D);

        Matrix E = A.sub(A);
        System.out.println(E.getNNZ());
        System.out.println(E);

        Matrix F = B.transpose();
        System.out.println(F.getNNZ());
        System.out.println(F);

        Matrix G = B.mult(B);
        System.out.println(G.getNNZ());
        System.out.println(G);*/

        Matrix H = A.copy();
        /*System.out.println(H.getNNZ());
        System.out.println(H);
        System.out.println(A.equals(H));
        System.out.println(A.equals(B));
        System.out.println(A.equals(A));

        A.makeZero();
        System.out.println(A.getNNZ());
        System.out.println(A);*/

        System.out.println(A.matrix[0] + " " + H.matrix[0]);
        System.out.println(A.matrix[0].equals(H.matrix[0]));
    }
}
