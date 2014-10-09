import java.io.*;
import java.util.*;

public class movetofront {
    static int[] ans;

    static class Pair {
        private Treap first;
        private Treap second;

        public Pair(Treap first, Treap second) {
            this.first = first;
            this.second = second;
        }
    }

    static class Treap {
        public int priority;
        public int cost;
        public int size;
        public Treap left;
        public Treap right;

        public Treap(int cost) {
            this.cost = cost;
            this.priority = (int)(Math.random() * Integer.MAX_VALUE);
            this.size = 1;
        }

        public static int size(Treap t) {
            return t != null ? t.size : 0;
        }

        public void resize() {
            size = size(left) + size(right) + 1;
        }

        public static Treap merge(Treap t1, Treap t2) {
            if (t1 == null || t2 == null) {
                if (t1 == null) {
                    return t2;
                } else {
                    return t1;
                }
            }
            if (t1.priority > t2.priority) {
                t1.right = merge(t1.right, t2);
                t1.resize();
                return t1;
            } else {
                t2.left = merge(t1, t2.left);
                t2.resize();
                return t2;
            }
        }

        public static Pair split(Treap t, int key, int add) {
            Treap t1 = null, t2 = null;
            if (t != null) {
                int curKey = add + size(t.left);
                if (key <= curKey) {
                    Pair p = split(t.left, key, add);
                    t1 = p.first;
                    t.left = p.second;
                    t2 = t;
                } else {
                    Pair p = split(t.right, key, add + size(t.left) + 1);
                    t.right = p.first;
                    t2 = p.second;
                    t1 = t;
                }
                t.resize();
            }
            return new Pair(t1, t2);
        }

        public static void traverse(Treap t, int k) {
            if (t == null) return;
            ans[k + size(t.left)] = t.cost;
            traverse(t.left, k);
            traverse(t.right, k + size(t.left) + 1);
        }
    }

    public static void main(String[] args) throws IOException {
        ans = new int[100500];

        FastScanner in = new FastScanner(new FileReader("movetofront.in"));
        PrintWriter out = new PrintWriter("movetofront.out");
        Treap t = new Treap(1);
        int n = in.nextInt(), m = in.nextInt();

        for (int i = 2; i <= n; i++) {
            t = Treap.merge(t, new Treap(i));
        }

        for (int i = 0; i < m; i++) {
            int a = in.nextInt(), b = in.nextInt();
            Pair p1 = Treap.split(t, a - 1, 0);
            Pair p2 = Treap.split(p1.second, b - a + 1, 0);
            t = Treap.merge(Treap.merge(p2.first, p1.first), p2.second);
        }

        Treap.traverse(t, 0);
        for (int i = 0; i < n; i++) {
            out.printf("%d ", ans[i]);
        }
        out.printf("\n");
        out.close();
    }

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
