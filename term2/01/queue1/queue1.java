import java.io.FileReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.lang.ArrayIndexOutOfBoundsException;

public class queue1 {
    static FastScanner in;
    static PrintWriter out;
    static Vector vector;

    public static void main(String[] args) throws IOException {
        // holy f*cking shit
        // (sorry, but you've got to understand -- i'm new to Java)
        in = new FastScanner(new FileReader("queue1.in"));
        out = new PrintWriter("queue1.out");
        vector = new Vector();

        int m = in.nextInt();

        for (int i = 0; i < m; i++) {
            String c = in.next();
            if (c.equals("+")) {
                vector.add(in.nextInt());
            } else {
                out.println(vector.delFront());
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

        private int right;
        private int left;
        private int[] vector;

        Vector() {
            vector = new int[256];
            left = 0;
            right = 0;
        }
            
        public void add(int x) {
            if (right == vector.length) {
                vector = Arrays.copyOf(vector, vector.length * A);
            }
            vector[right++] = x;
        }

        public void set(int i, int x) {
            if (!(0 <= i && i < right)) {
                throw new ArrayIndexOutOfBoundsException();
            }
            vector[i] = x;
        }
        
        public int get(int i) {
            if (!(0 <= i && i < right)) {
                throw new ArrayIndexOutOfBoundsException();
            }
            return vector[i];
        }

        public int delFront() {
            if (right - left <= 0) {
                throw new ArrayIndexOutOfBoundsException();
            }
            if ((right - left) * C <= vector.length) {
                int len = vector.length;
                vector = Arrays.copyOfRange(vector, left, right);
                vector = Arrays.copyOf(vector, len / B);
                right -= left;
                left = 0;
            }
            return vector[left++];
        }

        public int size() {
            return right - left;
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
