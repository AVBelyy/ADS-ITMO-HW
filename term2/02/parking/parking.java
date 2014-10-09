import java.io.*;
import java.util.*;

public class parking {
    static FastScanner in;
    static PrintWriter out;
    static BinarySearchTree bst;
    static Node head;
    static int n, m;

    public static void outpuTbinarYtreE(Node x, char c, int i) {
        if (x == null) return;
        System.err.printf(" %c%d:[%d; %d]{%d}", c, i, x.l, x.r, x.balance);
        outpuTbinarYtreE(x.left, 'l', i + 1);
        outpuTbinarYtreE(x.right, 'r', i + 1);
    }

    public static void main(String[] args) throws IOException {
        in = new FastScanner(new FileReader("parking.in"));
        out = new PrintWriter("parking.out");
        bst = new AVLTree();
        n = in.nextInt();
        m = in.nextInt();
        for (int i = 0; i < m; i++) {
            String command = in.next();
            int x = in.nextInt() - 1;
            if (command.equals("enter")) {
                Node node = bst.search(x);
                int place;
                if (node == null) {
                    place = x;
                } else {
                    place = node.r + 1;
                }
                System.out.println(place % n + 1);
                Node lnode = bst.search((place - 1 + n) % n);
                Node rnode = bst.search((place + 1) % n);
                int l, r;
                if (lnode == rnode && lnode != null) {
                    // it can only happen in one situation
                    l = 0;
                    r = n - 1;
                } else {
                    l = lnode == null ? place : lnode.l;
                    r = rnode == null ? place : rnode.r;
                    bst.remove(lnode);
                }
                bst.remove(rnode);
                bst.add(l % n, r % n);
            } else {
                Node node = bst.search(x);
                bst.remove(node);
                if (node.l == 0 && node.r == n - 1) {
                    bst.add((x + 1) % n, (x - 1 + n) % n);
                } else {
                    if (x != node.l) bst.add(node.l, (x - 1 + n) % n);
                    if (x != node.r) bst.add((x + 1) % n, node.r);
                }
            }
            //System.err.printf("%s %d --", command, x);
            //outpuTbinarYtreE(head, ' ', 0);
            //System.err.printf("\n");
        }
        out.close();
    }

    static class Node {
        Node parent;
        Node left, right;
        final int l, r;
        int balance;

        public Node(int l, int r) {
            this.l = l;
            this.r = r;
            this.balance = 0;
        }
    }

    private interface BinarySearchTree {
        public void add(int l, int r);
        public void remove(Node x);
        public Node search(int x);
    }

    static class AVLTree implements BinarySearchTree {
        public void add(int l, int r) {
            Node cur = head;
            Node newNode = new Node(l, r);
            if (head == null) {
                head = newNode;
                return;
            }
            while (cur != null) {
                if (l < cur.l) {
                    if (cur.left != null) {
                        cur = cur.left;
                    } else {
                        newNode.parent = cur;
                        cur.left = newNode;
                        break;
                    }
                } else if (l > cur.r) {
                    if (cur.right != null) {
                        cur = cur.right;
                    } else {
                        newNode.parent = cur;
                        cur.right = newNode;
                        break;
                    }
                }
            }
            Node prev = newNode;
            while (cur != null) {
                if (cur.left == prev) {
                    cur.balance++;
                } else {
                    cur.balance--;
                }
                if (cur.balance == -2) {
                    // left rotate time!
                    Node B = cur.right, P = cur.left;
                    if (B != null) {
                        Node Q = B.left, R = B.right;
                        if (B.balance <= 0) {
                            // small left rotate time!
                            set(cur, B);
                            B.left = cur;
                            B.right = R;
                            cur.left = P;
                            cur.right = Q;
                            cur.parent = B;
                            if (R != null) R.parent = B;
                            if (P != null) P.parent = cur;
                            if (Q != null) Q.parent = cur;
                            if (B.balance == -1) {
                                cur.balance = 0;
                                B.balance = 0;
                            } else if (B.balance == 0) {
                                cur.balance = -1;
                                B.balance = 1;
                            }
                            cur = B;
                        }
                    }
                } else if (cur.balance == 2) {
                    // right rotate time!
                    Node B = cur.left;
                    if (B != null) {
                        Node P = B.left, Q = B.right, R = cur.right;
                        if(B.balance >= 0) {
                            // small right rotate time!
                            set(cur, B);
                            B.left = P;
                            B.right = cur;
                            cur.parent = B;
                            cur.left = Q;
                            cur.right = R;
                            if (P != null) P.parent = B;
                            if (Q != null) Q.parent = cur;
                            if (R != null) R.parent = cur;
                            if (B.balance == 1) {
                                cur.balance = 0;
                                B.balance = 0;
                            } else if (B.balance == 0) {
                                cur.balance = 1;
                                B.balance = -1;
                            }
                            cur = B;
                        }
                    }
                }
                if (cur.balance == 0) break;
                prev = cur;
                cur = cur.parent;
            }
        }

        public Node min(Node x) {
            while (x.left != null) {
                x = x.left;
            }
            return x;
        }

        private void set(Node x, Node y) {
            if (x == head) {
                head = y;
            } else {
                if (x == x.parent.left) {
                    x.parent.left = y;
                } else {
                    x.parent.right = y;
                }
                if (y != null) y.parent = x.parent;
            }
        }

        public void remove(Node x) {
            if (x == null) return;
            if (x.left == null && x.right == null) {
                set(x, null);
            } else if (x.left != null && x.right == null) {
                set(x, x.left);
            } else if (x.left == null && x.right != null) {
                set(x, x.right);
            } else {
                Node y = min(x.right);
                set(y, null);
                y.left = x.left;
                if (x.left != null) {
                    x.left.parent = y;
                }
                y.right = x.right;
                if (x.right != null) {
                    x.right.parent = y;
                }
                set(x, y);
            }
        }

        public Node search(int x) {
            Node cur = head;
            while (cur != null) {
                if ((cur.l <= x && x <= cur.r) || ((cur.l > cur.r) && (x >= cur.l || x <= cur.r))) {
                    break;
                } else if (x < cur.l) {
                    cur = cur.left;
                } else {
                    cur = cur.right;
                }
            }
            return cur;
        }
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
