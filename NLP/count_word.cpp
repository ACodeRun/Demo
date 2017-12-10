#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <sstream>
using namespace std;

struct node
{
    int counter = 0;
    string everyword;
};
node word[9999999];

int main()
{
    int word_count = 0;
    int word_style = 0;
    FILE* fp;
    fp = fopen("Stanford_word.txt", "r");
    char str[1000];
    while (fscanf(fp, "%s", str) != EOF)
    {
        int flag = 0;
        word_count++;
        string str_char = str;
        for(int i=0;i<word_style;i++)
        {
            if(str_char.compare(word[i].everyword)==0)
            {
                word[i].counter++;
                flag = 1;
                for(int j=i;j>0;j--)
                {
                    if(word[j].counter>word[j-1].counter)
                    {
                        node word_temp;
                        word_temp = word[j];
                        word[j] = word[j-1];
                        word[j-1] = word_temp;
                    }
                }
                break;
            }
        }
        if(flag == 0)
        {
           word[word_style].everyword = str_char;
           word[word_style].counter++;
           word_style++;
        }
    }
    ofstream ofs;
    ofs.open("Stanfordword_count.txt");
    ofs<<"分词个数:  "<<word_count<<endl;
    for(int i=0;i<word_style;i++)
    {
        ofs<<"TOP"<<i+1<<"   频度:"<<word[i].counter<<"   "<<word[i].everyword<<endl;
    }
    ofs.close();
    fclose(fp);
    cout<< "Complete statistics"<<endl;
    return 0;
}
