#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct node
{
    int sum = 0;
    int conuter[100000]={0};
    string everyword[100000];
};
node wordsum[100];
int main()
{
    FILE* fp;
    FILE* ft;
    fp = fopen("199801.txt", "r");
    char str[1000];
    int word_count = 0;
    int type_count[100]={0};
    string type_word[100];
    while (fscanf(fp, "%s", str) != EOF)
    {
        int flag1=0;
        int flag2=0;
        int num = 0;
        //move []
        char str1[1000]={'/0'};
        if(str[0]=='[')
        {
             for(int i=0;i<str[strlen(str)-1];i++)
             {
               str1[i] = str[i+1];
             }
             strcpy(str,str1);
        }
        int q = 0;
        for(int i=1;str[strlen(str)-i]!='/';i++)
        {
            num++;
            if(str[strlen(str)-i] == ']')
            {
                strncpy(str1,str,strlen(str)-i);
                num = 0;
                q = 1;
            }
        }
        if(q==1){strcpy(str,str1);}

        string str_tem;
        string str_char = str;
        for(int i=num;i>0;i--)
        {
            str_tem += str[strlen(str)-i];
        }
        for(int i=0;i<word_count;i++)
        {
            if(str_tem.compare(type_word[i])==0)
            {
                type_count[i]++;
                flag1 = 1;
                for(int j=1;j<wordsum[i].sum;j++)
                {
                     if(str_char.compare(wordsum[i].everyword[j])==0)
                      {
                          wordsum[i].conuter[j]++;
                          flag2 = 1;
                          break;
                      }
                }
                if(flag2==0)
                {
                    wordsum[i].everyword[wordsum[i].sum] = str_char;
                    wordsum[i].conuter[wordsum[i].sum]++;
                    wordsum[i].sum++;
                }
                break;
            }
        }
        if(flag1 == 0)
        {
            type_word[word_count] = str_tem;
            type_count[word_count]++;
            wordsum[word_count].everyword[0] = str_tem;
            wordsum[word_count].sum++;
            wordsum[word_count].everyword[1] = str_char;
            wordsum[word_count].conuter[1]++;
            wordsum[word_count].sum++;
            word_count++;
        }
    }
    int num_tem;
    string str_tem;
    node wordsum_tem;
    for(int i=0;i<word_count-1;i++)
    {
        for(int j=i+1;j<word_count;j++)
        {

            if(type_count[j]>type_count[i])
            {

                num_tem=type_count[j];
                type_count[j] = type_count[i];
                type_count[i] = num_tem;
                str_tem = type_word[j];
                type_word[j] = type_word[i];
                type_word[i] = str_tem;
                wordsum_tem = wordsum[j];
                wordsum[j] = wordsum[i];
                wordsum[i] = wordsum_tem;
            }
        }
        for(int x=1;x<wordsum[i].sum-1;x++)
        {
            for(int y=x+1;y<wordsum[i].sum;y++)
            {
               if(wordsum[i].conuter[y]>wordsum[i].conuter[x])
               {
                   num_tem = wordsum[i].conuter[y];
                   wordsum[i].conuter[y] = wordsum[i].conuter[x];
                   wordsum[i].conuter[x] = num_tem;
                   str_tem = wordsum[i].everyword[y];
                   wordsum[i].everyword[y] = wordsum[i].everyword[x];
                   wordsum[i].everyword[x] = str_tem;
               }
            }
        }
    }
    int i = word_count;
    for(int x=1;x<wordsum[i].sum-1;x++)
    {
        for(int y=x+1;y<wordsum[i].sum;y++)
        {
           if(wordsum[i].conuter[y]>wordsum[i].conuter[x])
           {
               num_tem = wordsum[i].conuter[y];
               wordsum[i].conuter[y] = wordsum[i].conuter[x];
               wordsum[i].conuter[x] = num_tem;
               str_tem = wordsum[i].everyword[y];
               wordsum[i].everyword[y] = wordsum[i].everyword[x];
               wordsum[i].everyword[x] = str_tem;
           }
        }
    }
    ofstream ofs;
    ofs.open("data.txt");
    for(int i=0;i<word_count;i++)
    {
        ofs<<"Top"<<i+1<<": ";
        ofs<<type_word[i]<<"--->"<<type_count[i]<<endl;
        for(int j=1;j<=10&&j<wordsum[i].sum;j++)
        {
            ofs<<"top"<<j<<":   "<<wordsum[i].everyword[j]<<"--->"<<wordsum[i].conuter[j]<<endl;
        }
        ofs<<endl;
    }
    ofs.close();
    fclose(fp);
    cout<< "Complete statistics"<<endl;
    return 0;
}
