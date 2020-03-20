import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.regex.*;

public class Solution {

    public static class Node {
        public Map<Character, Node> children = new HashMap<>();
        public int size;

        public void add(char c) {
            if (children.get(c) != null) {
                return;
            }
            children.put(c, new Node());
        }
    }

    public static class Trie {
        public Node root = new Node();

        public void add (String s) {
            Node current = root;
            for (char c : s.toCharArray())
            {
                current.add(c);
                current = current.children.get(c);
                current.size++;
            }
        }

        public int find(String s) {
            Node current = root;
            for (char c : s.toCharArray())
            {
                current = current.children.get(c);
                if (current == null)
                    return 0;
            }
            return current.size;
        }
    }

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        int n = scanner.nextInt();
        scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

        Trie trie = new Trie();

        for (int nItr = 0; nItr < n; nItr++) {
            String[] opContact = scanner.nextLine().split(" ");

            String op = opContact[0];

            String contact = opContact[1];

            if (op.equals("add"))
                trie.add(contact);
            else
            {
                System.out.println(trie.find(contact));
            }
        }

        scanner.close();
    }
}
