
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.lang.ArrayIndexOutOfBoundsException;
 
public class stack1 {
    static FastScanner in;
    static PrintWriter out;
    static Vector vector;
 
    public static void main(String[] args) throws IOException {
        // holy f*cking shit
        // (sorry, but you've got to understand -- i'm new to Java)
        in = new FastScanner(new FileReader("stack1.in"));
        out = new PrintWriter("stack1.out");
        vector = new Vector();
 
        int m = in.nextInt();
 
        for (int i = 0; i < m; i++) {
            String c = in.next();
            if (c.equals("+")) {
                vector.add(in.nextInt());
            } else {
                out.println(vector.del());
            }
        }
 
        out.close();
    }
 
    // (C) avbelyy
    static class Vector {
        private static final int DEFAULT_SIZE = 256;
        private static final int A = 2; // size increasing multiplier
        private static final int B = 2; // size decreasing multiplier
        private static final int C = 4; // size decreasing threshold
 
        private int used;
        private int[] vector;
 
        Vector() {
            vector = new int[256];
            used = 0;
        }
             
        public void add(int x) {
            if (used == vector.length) {
                vector = Arrays.copyOf(vector, vector.length * A);
            }
            vector[used++] = x;
        }
 
        public void set(int i, int x) {
            if (!(0 <= i && i < used)) {
                throw new ArrayIndexOutOfBoundsException();
            }
            vector[i] = x;
        }
         
        public int get(int i) {
            if (!(0 <= i && i < used)) {
                throw new ArrayIndexOutOfBoundsException();
            }
            return vector[i];
        }
 
        public int del() {
            if (used == 0) {
                throw new ArrayIndexOutOfBoundsException();
            }
            if (used * C <= vector.length) {
                vector = Arrays.copyOf(vector, vector.length / B);
            }
            return vector[--used];
        }
 
        public int size() {
            return used;
        }
    }
 
    // (C) andrewzta
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;
 
        FastScanner(InputStreamReader in) throws IOException {
            br = new BufferedReader(in);
        }
 
        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                    return "";
                }
            }
            return st.nextToken();
        }
 
        int nextInt() {
            return Integer.parseInt(next());
        }
    }
}
