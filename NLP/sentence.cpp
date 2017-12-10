#include <iostream>
#include <fstream>
using namespace std;
int main ()
{
    ifstream fin("199801.txt");
    ofstream ofs;
    ofstream ofh;
    ofs.open("sentence.txt");
    ofh.open("hand_word.txt");
    char ch;
    int flag = 0;
    while((ch=fin.get())!=EOF)
    {
        if(ch == '[')
        {
            continue;
        }
        if(ch == '/')
        {
            flag = 2;
        }
        if(flag == 0)
        {
            ofh<<ch;
            ofs<<ch;
        }
        if(ch == ' ')
        {
            if(flag == 1)
            {
                ofh<<"  ";
            }
            flag--;
        }
    }
    cout<<"Merge complete";
    cout<<
    return 0;
}
