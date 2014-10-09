import java.io.FileReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.lang.ArrayIndexOutOfBoundsException;
 
public class brackets {
    static FastScanner in;
    static PrintWriter out;
    static Vector vector;
 
    public static void main(String[] args) throws IOException {
        in = new FastScanner(new FileReader("brackets.in"));
        out = new PrintWriter("brackets.out");

        String brackets = new String();

        while ((brackets = in.next()) != null) {
            int length = brackets.length();
            boolean flag = true;
            vector = new Vector();
            for (int i = 0; i < length; i++) {
                char c = brackets.charAt(i);
                if (c == '(' || c == '[') {
                    vector.add(c);
                } else {
                    if (vector.size() == 0) {
                        flag = false;
                        break;
                    }
                    char vc = vector.del();
                    if ((c == ')' && vc != '(') || (c == ']' && vc != '[')) {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag && vector.size() == 0) {
                out.println("YES");
            } else {
                out.println("NO");
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
        private char[] vector;
 
        Vector() {
            vector = new char[256];
            used = 0;
        }
             
        public void add(char x) {
            if (used == vector.length) {
                vector = Arrays.copyOf(vector, vector.length * A);
            }
            vector[used++] = x;
        }
 
        public void set(int i, char x) {
            if (!(0 <= i && i < used)) {
                throw new ArrayIndexOutOfBoundsException();
            }
            vector[i] = x;
        }
         
        public char get(int i) {
            if (!(0 <= i && i < used)) {
                throw new ArrayIndexOutOfBoundsException();
            }
            return vector[i];
        }
 
        public char del() {
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
 
    // (C) andrewzta & avbelyy
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
                } catch (NullPointerException e) {
                    return null;
                }
            }
            return st.nextToken();
        }
 
        int nextInt() {
            return Integer.parseInt(next());
        }
    }
}
