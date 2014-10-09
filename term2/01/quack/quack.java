import java.io.FileReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Map;
import java.util.Arrays;
import java.util.HashMap;
import java.util.StringTokenizer;
import java.lang.ArrayIndexOutOfBoundsException;

public class quack {
    static final int MOD = 1<<16;

    static FastScanner in;
    static PrintWriter out;
    static Vector<Character> vector;
    static Vector<String> commands;
    static Map<String, Integer> jumpTable;

    public static void main(String[] args) throws IOException {
        in = new FastScanner(new FileReader("quack.in"));
        out = new PrintWriter("quack.out");
        vector = new Vector<Character>();
        commands = new Vector<String>();
        jumpTable = new HashMap<String, Integer>();

        int[] reg = new int[26];
        String cmd = new String();

        int count = 0;
        while ((cmd = in.next()) != null) {
            if (cmd.startsWith(":")) {
                jumpTable.put(cmd.substring(1), count);
            } else {
                commands.add(cmd);
                count++;
            }
        }

        for (int i = 0; i < count; i++) {
            cmd = commands.get(i);
            if (cmd.equals("+")) {
                int x = vector.delFront(), y = vector.delFront();
                vector.add((char)(x + y));
            } else if (cmd.equals("-")) {
                int x = vector.delFront(), y = vector.delFront();
                vector.add((char)(x - y));
            } else if (cmd.equals("*")) {
                int x = vector.delFront(), y = vector.delFront();
                vector.add((char)(x * y));
            } else if (cmd.equals("/")) {
                int x = vector.delFront(), y = vector.delFront();
                if (x == 0 && y == 0) {
                    vector.add((char)0);
                } else {
                    vector.add((char)(x / y));
                }
            } else if (cmd.equals("%")) {
                int x = vector.delFront(), y = vector.delFront();
                if (x == 0 && y == 0) {
                    vector.add((char)0);
                } else {
                    vector.add((char)(x % y));
                }
            } else if (cmd.startsWith(">")) {
                int x = vector.delFront();
                int r = cmd.charAt(1) - 'a';
                reg[r] = x;
            } else if (cmd.startsWith("<")) {
                int r = cmd.charAt(1) - 'a';
                vector.add((char)reg[r]);
            } else if (cmd.equals("P")) {
                int x = vector.delFront();
                out.printf("%d\n", x);
            } else if (cmd.startsWith("P")) {
                int r = cmd.charAt(1) - 'a';
                out.printf("%d\n", reg[r]);
            } else if (cmd.equals("C")) {
                int x = vector.delFront();
                out.printf("%c", x % 256);
            } else if (cmd.startsWith("C")) {
                int r = cmd.charAt(1) - 'a';
                out.printf("%c", reg[r] % 256);
            } else if (cmd.startsWith("J")) {
                i = jumpTable.get(cmd.substring(1)) - 1;
            } else if (cmd.startsWith("Z")) {
                int r = cmd.charAt(1) - 'a';
                if (reg[r] == 0) {
                    i = jumpTable.get(cmd.substring(2)) - 1;
                }
            } else if (cmd.startsWith("E")) {
                int r1 = cmd.charAt(1) - 'a', r2 = cmd.charAt(2) - 'a';
                if (reg[r1] == reg[r2]) {
                    i = jumpTable.get(cmd.substring(3)) - 1;
                }
            } else if (cmd.startsWith("G")) {
                int r1 = cmd.charAt(1) - 'a', r2 = cmd.charAt(2) - 'a';
                if (reg[r1] > reg[r2]) {
                    i = jumpTable.get(cmd.substring(3)) - 1;
                }
            } else if (cmd.equals("Q")) {
                break;
            } else {
                vector.add((char)Integer.parseInt(cmd));
            }
        }

        out.close();
    }

    // (C) avbelyy
    static class Vector<T> {
        private static final int DEFAULT_SIZE = 256;
        private static final int A = 2; // size increasing multiplier
        private static final int B = 2; // size decreasing multiplier
        private static final int C = 4; // size decreasing threshold

        private int right;
        private int left;
        private Object[] vector;

        Vector() {
            this.vector = (T[])new Object[256];
            left = 0;
            right = 0;
        }
            
        public void add(T x) {
            if (right == vector.length) {
                vector = Arrays.copyOf(vector, vector.length * A);
            }
            vector[right++] = x;
        }

        public void set(int i, T x) {
            if (!(0 <= i && i < right)) {
                throw new ArrayIndexOutOfBoundsException();
            }
            vector[i] = x;
        }
        
        public T get(int i) {
            if (!(0 <= i && i < right)) {
                throw new ArrayIndexOutOfBoundsException();
            }
            return (T)vector[i];
        }

        public T delFront() {
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
            return (T)vector[left++];
        }

        public int size() {
            return right - left;
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
