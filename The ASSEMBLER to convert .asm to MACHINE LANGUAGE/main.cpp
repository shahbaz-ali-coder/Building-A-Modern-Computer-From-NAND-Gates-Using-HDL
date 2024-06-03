#include <iostream>
#include<algorithm>
#include<fstream>
#include<string>
#include<iomanip>
#include<unordered_map>
using namespace std;
string stobitos(string temp){
    if(temp[0]=='0') return "0000000000000000";
    int num=stoi(temp);
    string ans="";
    while(num>0){
        if(num%2==0){
            ans+='0';
        }else{
            ans+='1';
        }
        num/=2;
    }
    reverse(ans.begin(),ans.end());
    while(ans.length()!=16){
        ans="0"+ans;
    }
    return ans;
}
int main()
{
    unordered_map <string,string> mymap;
    mymap["SP"]="0";
    mymap["LCL"]="1";
    mymap["ARG"]="2";
    mymap["THIS"]="3";
    mymap["THAT"]="4";
    mymap["R0"]="0";
    mymap["R1"]="1";
    mymap["R2"]="2";
    mymap["R3"]="3";
    mymap["R4"]="4";
    mymap["R5"]="5";
    mymap["R6"]="6";
    mymap["R7"]="7";
    mymap["R8"]="8";
    mymap["R9"]="9";
    mymap["R10"]="10";
    mymap["R11"]="11";
    mymap["R12"]="12";
    mymap["R13"]="13";
    mymap["R14"]="14";
    mymap["R15"]="15";
    mymap["SCREEN"]="16384";
    mymap["KBD"]="24576";
    unordered_map <string,string> myc;
    myc["0"]="0101010";
    myc["1"]="0111111";
    myc["-1"]="0111010";
    myc["D"]="0001100";
    myc["A"]="0110000";
    myc["!D"]="0001101";
    myc["!A"]="0110001";
    myc["-D"]="0001111";
    myc["-A"]="0110011";
    myc["D+1"]="0011111";
    myc["A+1"]="0110111";
    myc["D-1"]="0001110";
    myc["A-1"]="0110010";
    myc["D+A"]="0000010";
    myc["D-A"]="0010011";
    myc["A-D"]="0000111";
    myc["D&A"]="0000000";
    myc["D|A"]="0010101";
    myc["M"]="1110000";
    myc["!M"]="1110001";
    myc["-M"]="1110011";
    myc["M+1"]="1110111";
    myc["M-1"]="1110010";
    myc["D+M"]="1000010";
    myc["D-M"]="1010011";
    myc["M-D"]="1000111";
    myc["D&M"]="1000000";
    myc["D|M"]="1010101";
    unordered_map<string ,string> mycdest;
    mycdest["M"]="001";
    mycdest["D"]="010";
    mycdest["MD"]="011";
    mycdest["A"]="100";
    mycdest["AM"]="101";
    mycdest["AD"]="110";
    mycdest["AMD"]="111";
    unordered_map<string,string> mycjmp;
    mycjmp["JGT"]="001";
    mycjmp["JEQ"]="010";
    mycjmp["JGE"]="011";
    mycjmp["JLT"]="100";
    mycjmp["JNE"]="101";
    mycjmp["JLE"]="110";
    mycjmp["JMP"]="111";

    ifstream infile;
    infile.open("amarfile.txt");
    ofstream outfile;
    outfile.open("out.hack");
    string str;
    int line=0;
    while(getline(infile,str)){
        if(str.length()==0){
            continue;
        }else if(str[0]=='/'){
            continue;
        }else if(str[0]=='('){
            int r=0;
            str=str.substr(1);
            while(str[r]!=')'){
                r++;
            }
            str=str.substr(0,r);
            mymap[str]=to_string(line);
        }else{
            line++;
        }

    }
    infile.close();
    infile.open("amarfile.txt");
    int n=16;
    while(getline(infile,str)){
        if(str.length()==0){
            continue;
        }else if(str[0]=='/'){
            continue;
        }else if(str[0]=='('){
            continue;
        }else if(str[0]=='@'){
           str=str.substr(1);
           if(str[0]>='0' && str[0]<='9'){
                int olen=0;
                while(str[olen]!='\0' && str[olen]!=' ' && str[olen]!='/'){
                    olen++;
                }
                string ans1=stobitos(str.substr(0,olen));
                outfile<<ans1<<endl;
           }else{
                int olen=0;
                while(str[olen]!='\0' && str[olen]!=' ' && str[olen]!='/'){
                    olen++;
                }
                str=str.substr(0,olen);
                if(mymap.find(str)!=mymap.end()){
                        string ans=stobitos(mymap[str]);
                        outfile<<ans<<endl;
                }else{
                    mymap[str]=to_string(n++);
                    string ans=stobitos(mymap[str]);
                    outfile<<ans<<endl;
                }
           }
        }else{
            //c instruction
            string dest="000",comp="0000000",jump="000";
            int len=0;
            while(str[len]!='\0' && str[len]!=' ' && str[len]!='/'){
                len++;
            }
            str=str.substr(0,len);
            int isequal=0,iscol=0,equalr=0,coll=str.length();
            for(int i=0;i<str.length();i++){
                if(str[i]=='='){
                    isequal=1;
                    equalr=i;
                }
                if(str[i]==';'){
                    iscol=1;
                    coll=i;
                }
            }
            string ans="111";
            if(isequal){
                dest=mycdest[str.substr(0,equalr)];
                comp=myc[str.substr(equalr+1,(coll-equalr-1))];
            }else {
                comp=myc[str.substr(0,coll)];
            }
            if(iscol){
                jump=mycjmp[str.substr(coll+1,3)];
            }
            ans=ans+comp+dest+jump;
            outfile<<ans<<endl;
        }
    }
    return 0;
}
