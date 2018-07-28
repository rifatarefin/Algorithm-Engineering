import java.util.*;

class Suffix
{
    int index;
    int[] rank=new int[2];
}

class Compare implements Comparator<Suffix>
{

    @Override
    public int compare(Suffix suffix, Suffix t1) {
        if(suffix.rank[0]==t1.rank[0])
        {
            return suffix.rank[1]-t1.rank[1];//String.valueOf(suffix.rank[1]).compareTo(String.valueOf(t1.rank[1])) ;
        }
        else return suffix.rank[0]-t1.rank[0];//String.valueOf(suffix.rank[0]).compareTo(String.valueOf(t1.rank[0])) ;
    }
}
public class Substring {
    public void naive(String text)
    {
        Set<String>set=new TreeSet<>();
        int n=text.length();
        for (int i=0;i<n;i++)
        {
            for (int j=i+1;j<=n;j++)
            {
                String s=text.substring(i,j);
                //System.out.println(s);
                set.add(s);
            }
        }
        //for (String s:set) System.out.println(s);
        System.out.println("Number of distinct substrings: "+set.size());
    }

    List<Integer>buildSuffixArray(String txt)
    {
        int n=txt.length();
        //ArrayList<Suffix>suffixes=new ArrayList<>(n);

        Suffix[] suffixes=new Suffix[n];

        for (int i = 0; i < n; i++)
        {
            suffixes[i]=new Suffix();
            suffixes[i].index = i;
            suffixes[i].rank[0] = txt.charAt(i) - 'a';
            suffixes[i].rank[1] = ((i+1) < n)? (txt.charAt(i+1) - 'a'): -1;
        }
        Arrays.sort(suffixes,new Compare());
        int[] ind=new int[n];
        for (int k = 4; k < 2*n; k = k*2)
        {

            int rank = 0;
            int prev_rank = suffixes[0].rank[0];
            suffixes[0].rank[0] = rank;
            ind[suffixes[0].index] = 0;


            for (int i = 1; i < n; i++)
            {

                if (suffixes[i].rank[0] == prev_rank &&
                        suffixes[i].rank[1] == suffixes[i-1].rank[1])
                {
                    prev_rank = suffixes[i].rank[0];
                    suffixes[i].rank[0] = rank;
                }
                else
                {
                    prev_rank = suffixes[i].rank[0];
                    suffixes[i].rank[0] = ++rank;
                }
                ind[suffixes[i].index] = i;
            }


            for (int i = 0; i < n; i++)
            {
                int nextindex = suffixes[i].index + k/2;
                suffixes[i].rank[1] = (nextindex < n)?
                        suffixes[ind[nextindex]].rank[0]: -1;
            }


            Arrays.sort(suffixes,new Compare() );
        }

        List<Integer>suff=new ArrayList<>();
        for(int i=0;i<n;i++)suff.add(suffixes[i].index);
        return suff;
    }

    List<Integer>LCP(String txt, List<Integer>suffixArr)
    {
        int n = suffixArr.size();



        List<Integer>lcp=new ArrayList<>(Collections.nCopies(n,0));


        List<Integer>invSuff=new ArrayList<>(Collections.nCopies(n,0));


        for (int i=0; i < n; i++)
            invSuff.set(suffixArr.get(i),i);


        int k = 0;
        for (int i=0; i<n; i++)
        {

            if (invSuff.get(i) == n-1)
            {
                k = 0;
                continue;
            }


            int j = suffixArr.get(invSuff.get(i)+1);


            while (i+k<n && j+k<n && txt.charAt(i+k)==txt.charAt(j+k))
                k++;

            lcp.set(invSuff.get(i),k); // lcp for the present suffix.


            if (k>0)
                k--;
        }


        return lcp;

    }
    void substr(String txt)
    {
        int n = txt.length();

        List<Integer>suffixArr = buildSuffixArray(txt);
        List<Integer>lcp = LCP(txt, suffixArr);


        int result = n - suffixArr.get(0);

        for (int i = 1; i < lcp.size(); i++)

            //  subtract lcp from the length of suffix
            result += (n - suffixArr.get(i)) - lcp.get(i - 1);

        //result++;  // For empty string
        System.out.println("Distinct Substrings: "+result);
    }

    public static void main(String[] args) {
        String s="banana";
        Substring substring=new Substring();
       // substring.naive(s);
        substring.substr(s);


    }
}
