import java.io.*;
import java.util.Scanner;

public class Sparse {
    public static void main(String[] args) throws IOException {
        Scanner in = null;
        PrintWriter  out = new PrintWriter(new FileWriter(args[1]));
        String line;
        int size, a, b, i, j;
        double entry;
        // check number of command line arguments is at least 2
        if (args.length < 2) {
            System.out.println("Usage: Sparse <input file> <output file>");
            System.exit(1);
        }
        // open files
        in = new Scanner(new File(args[0]));
        line = in.nextLine().trim();

        String[] s = line.split(" ");
        size = Integer.parseInt(s[0]);
        a = Integer.parseInt(s[1]);
        b = Integer.parseInt(s[2]);
        Matrix A = new Matrix(size);
        Matrix B = new Matrix(size);
        int count = 0;
        in.nextLine().trim();
        while(count < a && in.hasNextLine()){
            line = in.nextLine().trim();
            s = line.split(" ");
            i = Integer.parseInt(s[0]);
            j = Integer.parseInt(s[1]);
            entry = Double.parseDouble(s[2]);
            A.changeEntry(i, j, entry);
            count++;
        }count = 0;
        in.nextLine().trim();
        while(count < b && in.hasNextLine()){
            line = in.nextLine().trim();
            s = line.split(" ");
            i = Integer.parseInt(s[0]);
            j = Integer.parseInt(s[1]);
            entry = Double.parseDouble(s[2]);
            B.changeEntry(i, j, entry);
            count++;
        }

        out.println("A has " + A.getNNZ() + " non-zero entries:");
        out.println(A);
        out.println("B has " + B.getNNZ() + " non-zero entries:");
        out.println(B);
        out.println("(1.5)*A =");
        Matrix C = A.scalarMult(1.5);
        out.println(C);


        Matrix D = A.add(B);
        out.println("A+B =");
        out.println(D);
        D = A.add(A);
        out.println("A+A =");
        out.println(D);

        Matrix E = B.sub(A);
        out.println("B-A =");
        out.println(E);
        E = A.sub(A);
        out.println("A-A =");
        out.println(E);

        Matrix F = A.transpose();
        out.println("Transpose(A) =");
        out.println(F);

        Matrix G = A.mult(B);
        out.println("A*B =");
        out.println(G);
        G = B.mult(B);
        out.println("B*B =");
        out.println(G);

        in.close();
        out.close();
    }
}
