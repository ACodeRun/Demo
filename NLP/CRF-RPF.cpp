#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    FILE* fp;
    fp = fopen("result.txt", "r");
    ofstream ofs;
    ofs.open("data.txt");
    char str[4];
    int line = 0;
    int wordsum1 = 0,wordsum2 = 0,wordsum12 = -1;
    char BI ;
    int wordjudge = 1;
    while (fscanf(fp, "%s", str) != EOF)
    {
        line ++ ;
        if(line%3 == 1 )
        {
            continue;
        }
        if(line%3 == 2)
        {
            BI = str[0];
            if(BI == 'B')
            {
                wordsum1++;
            }
        }
        if(line%3 == 0)
        {
            if(str[0] == 'B')
            {
                wordsum2++;
            }
            if(wordjudge == 1)
            {
                if(BI == 'B' && str[0] =='B')
                {
                    wordsum12++;
                }
                if(BI != str[0])
                {
                    wordjudge = 0;
                }
            }
            if(BI == 'B' && str[0] =='B')
            {
                wordjudge = 1;
            }
        }
    }
    float R = float(wordsum12)/float(wordsum1);
    float P = float(wordsum12)/float(wordsum2);
    cout<<"wordsum1=  "<<wordsum1<<endl;
    cout<<"wordsum2=  "<<wordsum2<<endl;
    cout<<"wordsum12= "<<wordsum12<<endl;
    cout<<"R= "<<R<<endl;
    cout<<"p= "<<P<<endl;
    cout<<"F=2*P*R/(P+R)="<<2*P*R/(P+R)<<endl;

    ofs<<"wordsum1=  "<<wordsum1<<endl;
    ofs<<"wordsum2=  "<<wordsum2<<endl;
    ofs<<"wordsum12= "<<wordsum12<<endl;
    ofs<<"R= "<<R<<endl;
    ofs<<"p= "<<P<<endl;
    ofs<<"F=2*P*R/(P+R)="<<2*P*R/(P+R)<<endl;
    return 0;
}
