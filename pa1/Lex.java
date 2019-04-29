import java.io.*;
import java.util.Scanner;
public class Lex {

    public static List sort(List L, String[] A, int index, int start, int end){

        List templist = L;
        templist.moveFront();
        while(templist.index() != -1) {
            int comp = A[index].compareTo(A[templist.get()]);
            if(comp == 0){
                templist.insertAfter(index);
                return templist;
            }else if(comp < 0){
                templist.insertBefore(index);
                return templist;
            }else{	// comp > 0
                templist.moveNext();
            }
        }
        templist.append(index);
        return templist;


        
        /*while(templist.index() != -1) {
            System.out.println(templist.get());
            System.out.println(index + "index");
            if (A[templist.get()].substring(0, 1).compareTo(A[index].substring(0, 1)) == 0) {
                if(A[templist.get()].compareTo(A[index]) > 0){
                    templist.insertBefore(index);
                    //System.out.println(A[templist.get()] + A[index] + "1");
                    return templist;
                }else{
                    while(A[templist.get()].compareTo(A[index]) < 0){
                        templist.moveNext();
                    }
                    templist.insertBefore(index);
                    //System.out.println(A[templist.get()] + A[index] + "2");
                    return templist;
                }
            } else if (A[templist.get()].compareTo(A[index]) > 0) {
                templist.insertBefore(index);
                //System.out.println(A[templist.get()] + A[index] + "3");
                return templist;
            }
            templist.moveNext();
        }
        templist.append(index);
        return  templist;*/


        /*int mid = end/2;
        L.moveFront();
        while(L.index() != mid){
            L.moveNext();
        }
        if(A[L.get()].substring(0,1).compareTo(A[index]) == 0){
            L.insertBefore(index);
            return L;
        }else if(A[L.get()].substring(0,1).compareTo(A[index]) < 0){
            L.moveNext();
            if(L.get() != -1) {
                if (A[L.get()].substring(0, 1).compareTo(A[index]) > 0) {
                    L.insertBefore(index);
                    return L;
                }else{
                    return sort(L, A, index, mid + 1, end);
                }
            }else{
                L.movePrev();
                L.insertAfter(index);
                return L;
            }
        }else{
            L.movePrev();
            if(L.get() != -1) {
                if (A[L.get()].substring(0, 1).compareTo(A[index]) < 0) {
                    L.insertAfter(index);
                    return L;
                }else{
                    return sort(L, A, index, start, mid - 1);
                }
            }else{
                L.moveNext();
                L.insertBefore(index);
                return L;
            }

        }*/
    }

    public static void main(String[] args) throws IOException {
        Scanner in = null; // read file
        PrintWriter out = new PrintWriter(new FileWriter(args[1])); // write to report file
        String line = null; // string to take in inputs
        int numline = 0;
        // check number of command line arguments is at least 2
        if (args.length < 2) {
            System.out.println("Usage: Simulation <input file> <output file>");
            System.exit(1);
        }
        BufferedReader reader = new BufferedReader(new FileReader(args[0]));
        while (reader.readLine() != null) numline++;
        reader.close();

        String[] A = new String[numline];
        // open files
        in = new Scanner(new File(args[0]));
        int count = 0;
        //gets strings from in file
        while (in.hasNextLine()) {
            line = in.nextLine().trim();
            //System.out.println(line);
            A[count] = line;
            count++;
        }

        List sorted = new List();

        for(int x = 0; x < A.length; x++){
            if(sorted.length() == 0 ){
                sorted.append(x);
            }else{
                //System.out.println(A[x]);
                sorted = sort(sorted, A, x, 0, sorted.length());
            }
            //System.out.println(sorted);
        }
        sorted.moveFront();
        for(int x = 0; x < A.length; x++){
            System.out.println(A[sorted.get()]);
            out.write(A[sorted.get()] + "\n");
            sorted.moveNext();
        }
        out.close();
        in.close();

    }
}
