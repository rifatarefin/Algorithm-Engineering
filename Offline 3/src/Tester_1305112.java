import java.util.Random;
import java.util.stream.IntStream;

public class Tester_1305112 {
    public static void main(String[] args) {
        Random random=new Random();
        Splay_1305112 splay=new Splay_1305112(100);
        int i=0;
        int k=10004;
        while (i<1004)
        {
            splay.insert(random.nextInt()%k);
            i++;
        }
        long time=System.nanoTime();
        long t1=0,t2=0,t3=0;
        while(i<k)
        {
            //BTreePrinter.printNode(splay.root);
            long x1=System.nanoTime();
            splay.insert(random.nextInt()%k);
            splay.insert(random.nextInt()%k);
            t1+=System.nanoTime()-x1;
            x1=System.nanoTime();
            splay.search(random.nextInt()%k);
            t2+=System.nanoTime()-x1;
            x1=System.nanoTime();
            splay.delete(random.nextInt()%k);
            t3+=System.nanoTime()-x1;

            i+=4;
        }
        long t=System.nanoTime()-time;
        System.out.println(t/1000.0);
        System.out.println("per operation time: "+t/(1000.0*k));
        System.out.println("Insertion "+(t1*2.0)/(1000.0*k));
        System.out.println("Search "+(t2*4.0)/(1000.0*k));
        System.out.println("Delete "+(t3*4.0)/(1000.0*k));
    }


}
