#include <iostream>
#include <fstream>
using namespace std;
int main ()
{
    ifstream fin("199801.txt");
    ofstream ofh;
    ofh.open("train1.data");
    char ch;
    int num = 2;
    int flag = 2;
    int BI = 0;
    while((ch=fin.get())!=EOF)
    {
        if(ch == '[')
        {
            continue;
        }
        if(ch == '\n')
        {
            ofh<<ch;
            flag = 2;
            BI = 0;
            continue;
        }
        if(ch == '/')
        {
            flag = 2;
            BI = 0;
            continue;
        }
        if(ch == ' ')
        {
            flag--;
            continue;
        }
        if(flag == 0 && BI == 0)
        {
            ofh<<ch;
            num--;
            if(num==0)
            {
                ofh<<"\tB"<<endl;
                BI = 1;
                num = 2;
            }
            continue;
        }
        if(flag == 0 && BI == 1)
        {
            ofh<<ch;
            num--;
            if(num==0)
            {
                ofh<<"\tI"<<endl;
                num = 2;
            }
            continue;
        }

    }
    cout<<"Merge complete";
    return 0;
}
