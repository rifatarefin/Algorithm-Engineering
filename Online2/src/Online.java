import java.util.HashMap;
import java.util.Map;

public class Online {
    int n;
    int radix=95;
    int q1=857663;
    int q2=107;
    Map<Long,Integer>sub=new HashMap<>();
    Map<Long,Integer>sub2=new HashMap<>();
    
    private long hash(String string, int m, int q, int offset)
    {
        long hs=0;
        for(int i=offset;i<offset+m;i++)                   //pattern hash
            hs=(radix*hs+(string.charAt(i)-' '))%q;
        return hs;
    }

    void distinctSub(String text)
    {
        int cnt=0;
        int n=text.length();
        for (int i=1;i<=n;i++)
        {

            int D=1;
            for(int j=1;j<i;j++)                  //d^(m-1)
                D=(D*radix)%q1;

            int D2=1;
            for(int j=1;j<i;j++)                  //d^(m-1)
                D2=(D2*radix)%q2;
            
            long hash1=hash(text,i,q1,0);
            long hash2=hash(text,i,q2,0);
            
            for (int j=0;i+j<=n;j++)
            {

                String s=text.substring(j,j+i);
                //System.out.println(s);

                if(sub.containsKey(hash1) )
                {
                    if(!sub2.containsKey(hash2))
                    {
                        sub.put(hash1,i);
                        sub2.put(hash2,i);
                        cnt++;
                    }

                }
                else
                {
                    sub.put(hash1,i);
                    sub2.put(hash2,i);
                    cnt++;
                }

                if(i+j<n)
                {
                    hash1 = (hash1 +q1 -(D * (text.charAt(j ) - ' ')) % q1) % q1;
                    hash1 = (hash1 * radix + text.charAt(j + i) - ' ') % q1;

                    hash2 = (hash2 +q2 -(D2 * (text.charAt(j ) - ' ')) % q2) % q2;
                    hash2 = (hash2 * radix + text.charAt(j + i) - ' ') % q2;
                }

            }
            sub.clear();
            sub2.clear();
        }
        System.out.println(cnt);
    }

    public static void main(String[] args) {
        String txt="jkhasdhhasdhhasiwkksallkasjdhwiiasdns";
        Online online=new Online();
        online.distinctSub(txt);
    }
}
