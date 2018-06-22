import java.util.Scanner;

public class Splay_1305112 {
    private Node<Integer> root;

    public Splay_1305112(int val) {
        root=new Node<>(val);
    }

    private Node<Integer>rotateRight(Node<Integer> node)
    {
        Node<Integer>x=node.left;
        node.left=x.right;
        x.right=node;
        return x;
    }

    private Node<Integer>rotateLeft(Node<Integer> node)
    {
        Node<Integer>x=node.right;
        node.right=x.left;
        x.left=node;
        return x;
    }

    private Node<Integer>splay(Node<Integer> node, int val)
    {
        if(node==null)return null;
        if(val<node.data)
        {
            if(node.left==null)return node;
            if(val<node.left.data)
            {
                node.left.left=splay(node.left.left,val);
                node=rotateRight(node);
            }
            else if(val>node.left.data)
            {
                node.left.right=splay(node.left.right,val);
                if(node.left.right!=null)node.left=rotateLeft(node.left);
            }
            if(node==null)return node;
            else return rotateRight(node);
        }
        else if(val>node.data)
        {
            if(node.right==null)return node;
            if(val<node.right.data)
            {
                node.right.left=splay(node.right.left,val);
                if(node.right.left!=null)node.right=rotateRight(node.right);
            }
            else if(val>node.right.data)
            {
                node.right.right=splay(node.right.right,val);
                node=rotateLeft(node);
            }
            if(node.right==null)return node;
            else return rotateLeft(node);
        }
        else return node;
    }
    public boolean search(int key)
    {
        root=splay(root,key);
        return root.data==key;

    }
    public void insert(int val)
    {
        if(root==null)
        {
            root=new Node<>(val);
            return;
        }
        root=splay(root,val);
        if(val<root.data)
        {
            Node<Integer>node=new Node<>(val);
            node.left=root.left;
            node.right=root;
            root.left=null;
            root=node;
        }
        else if(val>root.data)
        {
            Node<Integer>node=new Node<>(val);
            node.right=root.right;
            node.left=root;
            root.right=null;
            root=node;
        }

    }

    public void delete(int val)
    {
        if(root==null)return;
        root=splay(root,val);
        if(root.data==val)
        {
            if(root.left==null)root=root.right;
            else
            {
                Node<Integer>t=root.right;
                root=root.left;
                splay(root,val);
                root.right=t;
            }
        }
    }


    public static void main(String[] args) {
        Splay_1305112 splay=new Splay_1305112(5);

        splay.insert(8);
        splay.insert(15);
        splay.insert(3);
        splay.insert(13);

        Scanner scanner=new Scanner(System.in);
        while (true)
        {
            BTreePrinter.printNode(splay.root);
            System.out.println("Options:\t1.Search\t2.Insert\t3.Delete");
            int op=scanner.nextInt();
            if(op<1 || op>3)continue;
            System.out.println("Enter Number");
            int num=scanner.nextInt();
            if(op==1) System.out.println(splay.search(num));
            else if(op==2)splay.insert(num);
            else splay.delete(num);

        }


    }
}
