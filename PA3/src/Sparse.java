import java.io.*;
import java.util.Scanner;

public class Sparse {
    public static void main(String[] args) throws IOException {
        Scanner in = null;
        PrintWriter rpt = new PrintWriter(new FileWriter(args[0] + ".rpt"));
        PrintWriter trc = new PrintWriter(new FileWriter(args[0] + ".trc"));
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
        while(count < a && in.hasNextLine()){
            line = in.nextLine().trim();
            s = line.split(" ");
            i = Integer.parseInt(s[0]);
            j = Integer.parseInt(s[1]);
            entry = Double.parseDouble(s[2]);
            A.changeEntry(i, j, entry);
            count++;
        }count = 0;
        while(count < b && in.hasNextLine()){
            line = in.nextLine().trim();
            s = line.split(" ");
            i = Integer.parseInt(s[0]);
            j = Integer.parseInt(s[1]);
            entry = Double.parseDouble(s[2]);
            B.changeEntry(i, j, entry);
            count++;
        }
    }
}
