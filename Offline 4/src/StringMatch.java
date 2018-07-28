import org.apache.commons.lang3.RandomStringUtils;
import org.apache.commons.lang3.text.*;

import java.math.BigInteger;
import java.nio.charset.Charset;
import java.util.Random;

public class StringMatch {

    int radix=95;
    int q1=857663;//BigInteger.probablePrime(20,new Random()).intValue();
    int q2=107;//BigInteger.probablePrime(7,new Random()).intValue();           //936889
    int m;
    int n;
    int[] kmpNext;

    public void naive(String text, String pattern)
    {
        System.out.println("Index of matches in naive method:");
        int len=text.length()-pattern.length();
        for(int i=0;i<=len;i++)
        {
            String sub=text.substring(i,i+pattern.length());
            if(sub.equals(pattern)) System.out.println(i);
        }
    }

    private long hash(String string, int m, int q, int offset)
    {
        long hs=0;
        for(int i=offset;i<offset+m;i++)                   //pattern hash
            hs=(radix*hs+(string.charAt(i)-' '))%q;
        return hs;
    }

    public void RabinKarp(String text, String pattern)
    {
        m=pattern.length();
        n=text.length();
        if(n<m)return;

        int D=1;
        for(int i=1;i<m;i++)                  //d^(m-1)
            D=(D*radix)%q1;

        int D2=1;
        for(int i=1;i<m;i++)                  //d^(m-1)
            D2=(D2*radix)%q2;

        long patternHash=hash(pattern,m, q1,0);
        long patternHash2=hash(pattern,m,q2,0);
        long textHash=hash(text,m, q1,0);
        long textHash2=hash(text,m, q2,0);

        System.out.println(q1+" "+q2);
        System.out.println("Index of matches in Rabin Karp method:");
        for(int i=0;i<=n-m;i++)
        {
            //System.out.println(textHash);
            if(textHash==patternHash)
            {
                if(patternHash2==textHash2 )//&& text.substring(i,i+m).equals(pattern))
                    System.out.println(i);
            }
            if(i<n-m) {
                textHash = (textHash +q1 -(D * (text.charAt(i ) - ' ')) % q1) % q1;
                textHash = (textHash * radix + text.charAt(i + m) - ' ') % q1;

                textHash2 = (textHash2 +q2 -(D2 * (text.charAt(i ) - ' ')) % q2) % q2;
                textHash2 = (textHash2 * radix + text.charAt(i + m) - ' ') % q2;

            }

        }


    }

    public void KMP(String text, String pattern)
    {
        m=pattern.length();
        n=text.length();
        kmpNext=new int[m];
        kmpNext[0]=0;
        int k=0;
        for(int q=1;q<m;q++)
        {
            while (k>0 && pattern.charAt(k)!=pattern.charAt(q))
                k=kmpNext[k-1];
            if(pattern.charAt(q)==pattern.charAt(k))
            {
                k++;

            }
            kmpNext[q]=k;
        }
        //for(int i:kmpNext) System.out.println(i);
        System.out.println("Index of matches in KMP method:");
        int len=0;
        for(int i=0;i<n;i++)
        {
            while (len>0 && pattern.charAt(len)!=text.charAt(i))
                len=kmpNext[len-1];
            if(pattern.charAt(len)==text.charAt(i))
                len++;
            if(len==m)
            {
                System.out.println(i-m+1);
                len=kmpNext[m-1];
            }
            //System.out.println(len);
        }
    }

    public static void main(String[] args) {
        StringMatch stringMatch=new StringMatch();
        Substring substring=new Substring();

        String text="", pattern, sub;
//        text= RandomStringUtils.randomAlphabetic(1500000).toLowerCase();
        pattern= RandomStringUtils.randomAlphabetic(50000).toLowerCase();
        for (int i=0;i<10;i++)text+=pattern;
        //System.out.println(text);
        System.out.println(pattern);
        sub=RandomStringUtils.randomAlphabetic(950).toLowerCase();
//        text="aaba";
//        pattern="a";

        long t1=System.currentTimeMillis();
        //stringMatch.naive(text,pattern);
        //stringMatch.RabinKarp(text,pattern);
        //stringMatch.KMP(text,pattern);
        substring.naive(sub);
        //substring.substr(sub);
        long time=System.currentTimeMillis()-t1;
        System.out.println("Time: "+(time/1000.0)+" Seconds");
    }
}
