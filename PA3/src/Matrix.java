import java.io.*;


public class Matrix {

    private class Point{
        int column;
        double ent;

        Point(int c, double x){
            column = c;
            ent = x;
        }
        public boolean equals(Point e){
            if( column != e.column){
                return false;
            }else{
                return true;
                /*if(ent == e.ent) {
                    return true;
                }return false;*/
            }
        }
        private String toString(Point e){
            if( e==null ){
                return "";
            }else{
                return ("(" + e.column + ", " + e.ent + ")");
            }
        }

    }

    private int size;
    private int nonzeros;
    private List[] matrix;

    // Constructor
    Matrix(int n){ // Makes a new n x n zero Matrix. pre: n>=1
        if(n > 0) {
            List[] matrix = new List[n];
            size = n;
            nonzeros = 0;
        }
    }

    // Access functions
    int getSize() {// Returns n, the number of rows and columns of this Matrix
        return size;
    }
    int getNNZ(){ // Returns the number of non-zero entries in this Matrix
        return nonzeros;
    }

    public boolean equals(Object x){
        return false;
    } // overrides Object's equals() method

    public int dot(Matrix A, Matrix B, int r, int c){
        double[] product = new double[size];
        int sum;
        Point aent, bent;
        List a = A.matrix[r];
        List b = B.matrix[0];
        a.moveFront();
        b.moveFront();
        int count = 1;
        while(count <= 3){
            aent = (Point) a.get();
            bent = (Point) b.get();
            if(aent.column == count && bent.column == c){
                product[count - 1] = aent.ent * bent.ent;
                count++;
                a.moveNext();
            }


        }


    }

    // Manipulation procedures

    void makeZero(){
        for(int x = 0; x < size; x++){
            matrix[x].clear();
        }
    } // sets this Matrix to the zero state

    Matrix copy(){
        Matrix A = new Matrix(size);
        for(int x = 0; x < size; x++){
            matrix[x].moveFront();
            while(matrix[x].index() != -1){
                Point temp = (Point) matrix[x].get();
                A.changeEntry(x, temp.column, temp.ent);
                matrix[x].moveNext();
            }
        }
        return A;
    }// returns a new Matrix having the same entries as this Matrix

    void changeEntry(int i, int j, double x){
        Point temp = new Point(j, x);
        if(matrix[i].length() == 0 && x != 0){
            matrix[i].append(temp);
            nonzeros++;
        }else {
            matrix[i].moveFront();
            while (matrix[i].index() < i) {
                matrix[i].moveNext();
            }
            if (matrix[i].index() == -1) {
                matrix[i].prepend(temp);
                nonzeros++;
            }else if(matrix[i].index() == i){
                if(x == 0){
                    matrix[i].delete();
                    nonzeros--;
                }else if(matrix[i].get() == temp){
                    return;
                }else{
                    matrix[i].insertAfter(temp);
                    matrix[i].delete();
                    nonzeros++;
                }
            }else{
                if(x != 0) {
                    matrix[i].insertBefore(temp);
                    nonzeros++;
                }
            }
        }
    }
    // changes ith row, jth column of this Matrix to x
    // pre: 1<=i<=getSize(), 1<=j<=getSize()

    Matrix scalarMult(double x){
        Matrix A = new Matrix(size);
        for(int i = 0; i < size;i++){
            List Ltemp = A.matrix[i];
            Point temp;
            Ltemp.moveFront();
            while(Ltemp.get() != null){
                temp = (Point) Ltemp.get();
                changeEntry(i, temp.column, temp.ent * x );
                Ltemp.moveNext();
            }
        }
        return A;
    }

    // returns a new Matrix that is the scalar product of this Matrix with x

    Matrix add(Matrix M) {
        Matrix A = new Matrix(size);
        for (int i = 0; i < size; i++) {
            List a = matrix[i];
            List b = M.matrix[i];
            a.moveFront();
            b.moveFront();
            Point aent, bent;
            int count = 1;
            while (count <= size) {
                if(a.index() != -1 && b.index() != -1) {
                    aent = (Point) a.get();
                    bent = (Point) b.get();
                    if (aent.equals(bent) && aent.column == count) {
                        A.changeEntry(i, count, aent.ent + bent.ent);
                        a.moveNext();
                        b.moveNext();
                    } else if (aent.column != count && bent.column != count) {
                        a.moveNext();
                        b.moveNext();
                    } else if (aent.column == count) {
                        A.changeEntry(i, count, aent.ent);
                        a.moveNext();
                    } else {
                        A.changeEntry(i, count, bent.ent);
                        b.moveNext();
                    }
                }else if(a.index() != -1 && b.index() == -1){
                    aent = (Point) a.get();
                    if(aent.column == count) {
                        A.changeEntry(i, count, aent.ent);
                        a.moveNext();
                    }
                }else if(b.index() != -1 && a.index() == -1){
                    bent = (Point) a.get();
                    if(bent.column == count) {
                        A.changeEntry(i, count, bent.ent);
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
        for(int i = 0; i < size;i++){
            List a = matrix[i];
            List b = M.matrix[i];
            a.moveFront();
            b.moveFront();
            Point aent = (Point) a.get();
            Point bent = (Point) b.get();
            int count = 1;
            while(count <= size){
                if(a.index() != -1 && b.index() != -1) {
                    if (aent.equals(bent) && aent.column == count) {
                        A.changeEntry(i, count, aent.ent - bent.ent);
                        a.moveNext();
                        b.moveNext();
                    } else if (aent.column != count && bent.column != count) {
                        a.moveNext();
                        b.moveNext();
                    } else if (aent.column == count) {
                        A.changeEntry(i, count, aent.ent);
                        a.moveNext();
                    } else {
                        A.changeEntry(i, count, -bent.ent);
                        b.moveNext();
                    }
                }else if(a.index() != -1 && b.index() == -1){
                    aent = (Point) a.get();
                    if(aent.column == count) {
                        A.changeEntry(i, count, aent.ent);
                        a.moveNext();
                    }
                }else if(b.index() != -1 && a.index() == -1){
                    bent = (Point) a.get();
                    if(bent.column == count) {
                        A.changeEntry(i, count, -bent.ent);
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
        return this;
    }
    // returns a new Matrix that is the transpose of this Matrix

    Matrix mult(Matrix M){
        return this;
    }
    // returns a new Matrix that is the product of this Matrix with M
    // pre: getSize()==M.getSize()

    // Other functions
    public String toString(){
        return "fuck";
    } // overrides Object's toString() method





}
