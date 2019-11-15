#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define gap_opening 400
#define gap_penalty 20

void printer(int m,int n,int** arr){
    int i,j;
    for(i=0;i<m;i++){

        for(j=0;j<n;j++){
            cout<< arr[i][j]<<" ";        }
        cout<<"\n";
    }
}

int** init_matrix(int m,int n){
    int **arr=0;
    arr = new int*[m];
    int i,j;
    for(i=0;i<m;i++){
        arr[i]=new int[n];
        for(j=0;j<n;j++){
            arr[i][j]=0;        }
    }
    return arr;
}


int score_calculator(char a,char b){
    if(a==b){
        if(a=='A' and b=='A')
            return -91;
        else if(a=='C' and b=='C')
            return -100;

        else if(a=='G' and b=='G')
            return  -100;

        else if(a=='T' and b=='T')
            return -91;

    }

    else
    {
        if(a=='A' and b=='C')
            return 114;
        else if(a=='A' and b=='G')
            return 31;
        else if(a=='A' and b=='T')
            return 123;
        else if(a=='C'  and b=='A')
            return 114;

        else if(a=='C' and b=='G')
            return 125;

        else if(a=='C' and b=='T')
            return 31;

        else if(a=='G' and b=='A')
            return 31;

        else if(a=='G' and b=='C')
            return 125;

        else if(a=='G' and b=='T')
            return 114;

        else if(a=='T' and b=='A')
            return 123;

        else if(a=='T' and b=='C')
            return 31;

        else if(a=='T' and b=='G')
            return 114;

    }
}



int scorer(string& str1,string& str2) {
    int l2 = str2.length();
    int l1 = str1.length();
    int i, j;
    int **m = init_matrix(l1 + 1, l2 + 1);
    int **x = init_matrix(l1 + 1, l2 + 1);
    int **y = init_matrix(l1 + 1, l2 + 1);

    int **mtrace = init_matrix(l1 + 1, l2 + 1);
    int **xtrace = init_matrix(l1 + 1, l2 + 1);
    int **ytrace = init_matrix(l1 + 1, l2 + 1);

    for(i=1;i<l1+1;i++){
        m[i][0]=INT16_MAX;
        x[i][0]=gap_opening+(i-1)*gap_penalty;
        y[i][0]=INT16_MAX;

    }
    for(i=1;i<l2+1;i++){
        m[0][i]=INT16_MAX;
        x[0][i]=INT16_MAX;
        y[0][i]=gap_opening+(i-1)*gap_penalty;;
    }


    for(i=1;i<l1+1;i++){
        for(j=1;j<l2+1;j++){
            m[i][j]=score_calculator(str1[i-1],str2[j-1])+min(min(m[i-1][j-1],x[i-1][j-1]),y[i-1][j-1]);
            x[i][j]=min(min(gap_opening+m[i-1][j],gap_penalty+x[i-1][j]),gap_opening+y[i-1][j]);
            y[i][j]=min(min(gap_opening+m[i][j-1],gap_opening+x[i][j-1]),gap_penalty+y[i][j-1]);

        }
    }
    //trace for m
    for(i=1;i<l1+1;i++){
        for(j=1;j<l2+1;j++){
            int cost=score_calculator(str1[i-1],str2[j-1]);
            int temp=cost + min(min(m[i-1][j-1],x[i-1][j-1]), y[i-1][j-1]);
            if(temp==m[i-1][j-1]+cost){
                mtrace[i][j]=0;
            }
            else if (temp==x[i-1][j-1]+cost){
                mtrace[i][j]=1;
            }
            else if(temp==y[i-1][j-1]+cost){
                mtrace[i][j]=2;
            }


            temp=min(min(gap_opening+m[i-1][j],gap_penalty+x[i-1][j]),gap_opening+y[i-1][j]);
            if(temp==gap_opening+m[i-1][j]){
                xtrace[i][j]=0;
            }
            else if (temp==gap_penalty+x[i-1][j]){
                xtrace[i][j]=1;
            }
            else if(temp==gap_opening+y[i-1][j]){
                xtrace[i][j]=2;
            }


            temp=min(min(gap_opening+m[i][j-1],gap_opening+x[i][j-1]),gap_penalty+y[i][j-1]);
            if(temp==gap_opening+m[i][j-1]){
                ytrace[i][j]=0;
            }
            else if (temp==gap_opening+x[i][j-1]){
                ytrace[i][j]=1;
            }
            else if(temp==gap_penalty+y[i][j-1]){
                ytrace[i][j]=2;
            }

        }
    }




    string rstr1="";
    string rstr2="";
    i=l1;
    j=l2;

    int temp=min(min(mtrace[i][j],xtrace[i][j]),ytrace[i][j]);
    int id;

    if(temp==mtrace[i][j]){
        id=0;


    }
    else if (temp==xtrace[i][j]){
        id=1;


    }
    else if(temp==ytrace[i][j]){
        id=2;


    }

    while (i>0 or j>0 ){
        if(id==0){
            if(mtrace[i][j]==0){
                rstr1+=str1[i-1];
                rstr2+=str2[j-1];
                i--;
                j--;
                id=0;
            }
            else if(mtrace[i][j]==1){
                rstr1+=str1[i-1];
                rstr2+=str2[j-1];
                i--;
                j--;
                id=1;
            }
            else if(mtrace[i][j]==2){
                rstr1+=str1[i-1];
                rstr2+=str2[j-1];
                i--;
                j--;
                id=2;
            }

        }
        else if(id==1){
            if(xtrace[i][j]==0){
                rstr1+=str1[j-1];
                rstr2+="_";
                i--;
                id=0;
            }
            else if(xtrace[i][j]==1){
                rstr1+=str1[j-1];
                rstr2+="_";
                i--;
                id=1;
            }
            else if(xtrace[i][j]==2){
                rstr1+=str1[j-1];
                rstr2+="_";
                i--;
                id=2;
            }

        }
        else if(id==2){
            if(ytrace[i][j]==0){
                rstr2+=str2[i-1];
                rstr1+="_";
                j--;
                id=0;
            }
            else if(ytrace[i][j]==1){
                rstr2+=str2[i-1];
                rstr1+="_";
                j--;
                id=1;
            }
            else if(ytrace[i][j]==2){
                rstr2+=str2[i-1];
                rstr1+="_";
                j--;
                id=2;
            }

        }
;
//        cout<<i<<" "<<j<<endl;
    }
    while (j>0){
        rstr1+=str1[j-1];
        rstr2+="_";
        j--;

    }
    while (i>0){
        rstr2+=(str2[i-1]);
        rstr1+="_";
        i--;

    }

    reverse(rstr1.begin(), rstr1.end());
    reverse(rstr2.begin(), rstr2.end());
    cout<<m[l1][l2]<<endl;
    cout<<rstr1<<endl;
    cout<<rstr2<<endl;




}
    int main() {
        string seq1;
        string seq2;
        getline(cin, seq1);
        getline(cin, seq2);
        scorer(seq1,seq2);

    return 0;
}