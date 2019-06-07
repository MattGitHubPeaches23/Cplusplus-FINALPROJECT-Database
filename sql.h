// Copyright (c) 2019, Matthew Chalifoux.

#ifndef SQL_H
#define SQL_H
#include "ftokenizer.h"
#include "multimap.h"
#include "bplustree.h"
#include "stokenizer.h"
#include <iostream>
#include <fstream>
#include "file_record.h"
#include "utilities.h"
#include "consts.h"
#include "glrir.h"
#include "table.h"
#include "table_log.h"
#include "parser.h"
#include "parse_table.h"
#include <iomanip>
#include <cstring>
#include <iostream>
using namespace std;
struct File{
    string name;
    vector<string> field_names;
    vector<vector<string> > field_inserts;


    File *link;
};
class SQL{    
public:

    SQL(string file);
    SQL(){first = true;parser_time = NULL;before = false;num_file = 0;link = NULL;interactive();}
    bool first;
    bool before;
    void read_file(string file);
    void interactive();
    vector<string> get;
    vector<string> ty_pe;
    Parser *parser_time;
    File *link;
    int num_file;
};
void SQL::interactive(){

//    string blah = "";
//    string cnect = "";
    cout << "Enter command. Press enter when done. " << endl;


    string blah;
    vector<string> tt;
    cout<<": ";
    getline(cin, blah);
    while (!blah.empty()){
        tt.push_back(blah);
        cout<<": ";
        getline(cin, blah);
    }

    string cnect;
    for(int p = 0; p < tt.size(); ++p){
        cnect += tt[p];
    }

    if(0 == tt.size()){}




    else if(0 != tt.size()){
        cout << "cnect = " << endl;
        cout << cnect;


        char myArray[cnect.size()+1];//as 1 char space for null is also required
        strcpy(myArray, cnect.c_str());

        STokenizer stk(myArray);
        Token t;
        vector<string> stri;
        vector<string> tp;

        //The all too familiar golden while loop:
        stk>>t;
        stri.push_back(t.token_str());
        tp.push_back(t.type_string());
        while(stk.more()){
            //process token here...
            cout<<setw(10)<<t.type_string()<<setw(10)<<t<<endl;
            t = Token();
            stk>>t;
            stri.push_back(t.token_str());
            tp.push_back(t.type_string());
        }

        for(int p = 0; p < stri.size(); ++p){
    //        cout << get[p] << endl;
    //        cout << ty_pe[p] << endl;
            if(tp[p] == "UNKNOWN"){
                if(stri[p] == ","){
                    //cout << "it's a comma" << endl;
                    tp[p] = "COMMA";
                }
            }
            //cout << "************" << endl;
        }
        cout << "5656fyyry" << endl;
        for(int p = 0; p < stri.size() ; ++p){
//            cout << stri[p] << endl;
//            cout << tp[p] << endl;
        //    cout << "************" << endl;
        }
        vector<string> sfin;
        vector<string> tfin;
        bool turn = false;
        for(int p = 0; p < stri.size(); ++p){
            string k = stri[p];
            string m = tp[p];//took out "*" from stokenizer line 246
            if(k == "\""){
                    m = "QUOTATION";
                    if(turn == false){
                        turn = true;
                    }
                    else if(turn == true){
                        turn = false;
                    }

            }
            else if(k == "*"){
                m = "FIELDS";
            }
            if((m != "SPACE" && m != "UNKNOWN") || turn == true){
                sfin.push_back(k);
                tfin.push_back(m);
            }
        }
        cout<<"KLKLKL"<<endl;
        for(int p = 0; p < sfin.size() ; ++p){
//            cout << sfin[p] << endl;
//            cout << tfin[p] << endl;
           // cout << "************" << endl;
        }


        if(parser_time->parse_again(sfin,tfin)){ }




        Parse_Table *ptr;
        ptr = parser_time->link;

        File *kl;

        if(ptr != NULL){
            link = new File;

            kl = link;
        }


        while(ptr != NULL){
            num_file+=1;
            string wrt;
            vector<string> fn;
            vector<vector<string> > fi;

            wrt = ptr->tabl_name;

            for(int p = 0; p < ptr->fiel_types.size(); ++p){
                fn.push_back(ptr->fiel_types[p]);
                kl->field_names.push_back(fn[p]);
            }
            for(int p = 0; p < ptr->fiel_insert.size(); ++p){
                fi.push_back(ptr->fiel_insert[p]);
                kl->field_inserts.push_back(fi[p]);
            }



            kl->name = wrt;

            cout << "kll.name  " << kl->name << endl;
            for(int p = 0 ; p < kl->field_names.size(); ++p){
                cout << setw(15) <<  kl->field_names[p] << endl;
            }
            for(int p = 0; p < kl->field_inserts.size(); ++p){
                cout << setw(15) << kl->field_inserts[p] << endl;
            }
            ptr = ptr->link;
            if(ptr != NULL){
                kl->link = new File;
                kl = kl->link;
            }
        }

        interactive();



     }
}


SQL::SQL(string file){

    first = false;
    before = true;
    parser_time = NULL;
    num_file = 0;
    link = NULL;
    char *ptr2;
    for(int p = 0; p < file.size(); ++p){
        ptr2[p] = file[p];
    }
    ptr2[file.size()] = NULL;


    Token t;
    FTokenizer ftk(ptr2);
    ftk>>t;
    string g = t.token_str();
    get.push_back(g);
    string h  = t.type_string();
    ty_pe.push_back(h);

    int token_count = 0;
    while (ftk.more()){
        token_count++;
//        cout<<setw(10)<<token_count
//            <<setw(3)<<left<<":"<<setw(25)<<left<<t.token_str()
//            <<t.type_string()<<endl;
        ftk>>t;
        g = t.token_str();
        get.push_back(g);
        h  = t.type_string();
        ty_pe.push_back(h);
    }
    bool yes = false;
    for(int p = 0; p < get.size(); ++p){
//        cout << get[p] << endl;
//        cout << ty_pe[p] << endl;
//        if(get[p] == "select"){
//            yes = true;
//            int l = p + 2;
//            do{
//                if(get[l] == "*"){
//                }
//                else if(get[l] == "\""){

//                }
//            }
//        }

        if(ty_pe[p] == "UNKNOWN"){
            if(get[p] == ","){
                cout << "it's a comma" << endl;
                ty_pe[p] = "COMMA";
            }
        }
        //cout << "************" << endl;
    }

    vector<string> sfin;
    vector<string> tfin;
    bool turn = false;
    string alp = get[0];
    string k;
    string m;
    cout << get.size() << endl;
    cout << ty_pe.size() << endl;




    first = false;    

    Parser sb(get,ty_pe);
    parser_time = &sb;


    Parse_Table *ptr;
    ptr = parser_time->link;

    File *kl;

    if(ptr != NULL){
        link = new File;

        kl = link;
    }


    while(ptr != NULL){
        num_file+=1;
        string wrt;
        vector<string> fn;
        vector<vector<string> > fi;

        wrt = ptr->tabl_name;

        for(int p = 0; p < ptr->fiel_types.size(); ++p){
            fn.push_back(ptr->fiel_types[p]);
            kl->field_names.push_back(fn[p]);
        }
        for(int p = 0; p < ptr->fiel_insert.size(); ++p){
            fi.push_back(ptr->fiel_insert[p]);
            kl->field_inserts.push_back(fi[p]);
        }



        kl->name = wrt;

        cout << "kll.name  " << kl->name << endl;
        for(int p = 0 ; p < kl->field_names.size(); ++p){
            cout << setw(15) <<  kl->field_names[p] << endl;
        }
        for(int p = 0; p < kl->field_inserts.size(); ++p){
            cout << setw(15) << kl->field_inserts[p] << endl;
        }
        ptr = ptr->link;
        if(ptr != NULL){
            kl->link = new File;
            kl = kl->link;
        }
    }

    cout << "AAAAAAAAAAAAAAAAAAAAAAAAHHH" << endl;

    interactive();
}

#endif // SQL_H
