#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;
struct node
{
    int num = 0;
    string word[1000];
};
node f1word[20000];

struct sum_count
{
    int A_count;
    int B_count = 0;
    int AB_count = 0;
};
sum_count node_count[20000];

int main()
{
    ifstream fin1("hand_word.txt");
    string line,word;
    int f1count = 0;
    while (getline (fin1, line))
    {
        if(line.compare("  ")==0 || line.compare("")==0)
        {
            continue;
        }
        stringstream ss(line);
        while(ss >> word)
        {
            f1word[f1count].word[f1word[f1count].num] = word;
            f1word[f1count].num++;
        }
        node_count[f1count].A_count = f1word[f1count].num;
        f1count++;
    }


    int f2count = 0;
    ifstream fin2("Stanford_word.txt");
    int Acount=0,Bcount=0,ABcount=0;
    while(getline(fin2, line))
    {
        if(line.compare("  ")==0 || line.compare("")==0)
        {
            continue;
        }
        stringstream ss(line);
        while(ss >> word)
        {
            for(int i=0;i<f1word[f2count].num;i++)
            {
                if(word.compare(f1word[f2count].word[i])== 0)
                {
                    node_count[f2count].AB_count++;
                    break;
                }
            }
            node_count[f2count].B_count++;
        }
        Acount += node_count[f2count].A_count;
        Bcount += node_count[f2count].B_count;
        ABcount += node_count[f2count].AB_count;
        f2count++;
    }
    ofstream fout;
    fout.open("Analysis_result.txt");
    fout<<"标准分词总数:      "<<Acount<<endl;
    fout<<"stanford分词总数:  "<<Bcount<<endl;
    fout<<"正确标注的单词数   "<<ABcount<<endl;
    float R= float(ABcount)/float(Acount);
    float P= float(ABcount)/float(Bcount);
    float F = 2*R*P/(R+P);
    fout<<"R值: "<<R<<endl;
    fout<<"P值: "<<P<<endl;
    fout<<"F值: "<<F;

//    for(int i=0;i<f1count;i++)
//    {
//        fout<<"line"<<i+1<<"  "<<node_count[i].A_count<<"  "<<node_count[i].B_count<<"  "<<node_count[i].AB_count<<endl;
//    }
    cout<<"Complete Analysis";
    return 0;
}
