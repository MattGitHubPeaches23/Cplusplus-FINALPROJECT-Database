// Copyright (c) 2019, Matthew Chalifoux.

#ifndef GLRIR_H
#define GLRIR_H
#include "ftokenizer.h"
#include "multimap.h"
#include "bplustree.h"
#include "stokenizer.h"
#include <iostream>
#include <fstream>
#include "file_record.h"
#include "utilities.h"
#include "consts.h"
#include <iomanip>
using namespace std;
long get_last_record(fstream& f){
    //this is for testing only! Do not use this in your project!
    const bool debug = true;
    file_record frec;
    int recno = 0;
    while (!f.eof()){
        frec.read(f, recno);
        if (debug){
            cout<<"recno: "<<setw(4)<<recno<<frec<<endl;
        }
        recno++;
    }
    if (debug){
        cout<<"found last record: "<<recno<<endl;
    }
    return recno;

}
vector<string> input_record(){
    string s;
    vector<string> v;
    cout<<": ";
    getline(cin, s);
    while (!s.empty()){
        v.push_back(s);
        cout<<": ";
        getline(cin, s);
    }
    return v;
}

//************************** MAIN **********************************************

//int main(int argc, char *argv[])
//{
//    long recno;
//    fstream f;
////    recno = get_last_record(f);
////    cout<<endl<<endl<<". . . . . . "<<"recno: "<<recno<<
////                      ". . . . . . ."<<endl;

//    vector<string> v;
//    v = input_record();
//    file_record frec(recno);
//    while (!v.empty()){
//        //prep the record to be written into file:
//        for (int i = 0; i<v.size(); i++){
//            strcpy(frec.record[i+1], v[i].c_str());
//        }

//        open_fileRW(f, DATABASE_FILE_NAME);
//        //seek to the end of file:
//        f.seekg (0, f.end);

//        //write into the file and retrieve the record number of the
//        //  record
//        recno = frec.write(f);

//        //close the file right away.
//        f.close();

//        cout<<"record was written into the file at: "<<recno<<endl;

//        //read the record you just saved:
//        open_fileRW(f, DATABASE_FILE_NAME);
//        frec.read(f, recno);
//        cout<<"reading the record from file:"<<endl;

//        cout<<"recono: "<<setw(4)<<recno<<" "<<frec<<endl;
//        cout<<"-----------------------------------"<<endl;

//        cout<<"list of all records so far: "<<endl;
//        for (int i= 0; i<=recno; i++){
//            frec.read(f, i);
//            cout<<"recono: "<<setw(4)<<i<<" "<<frec<<endl;
//        }
//        f.close();

//        cout<<"---- DONE -------"<<endl;
//        v = input_record();

//    }
//    cout <<endl<<endl<<endl<< "================================" << endl;
//    return 0;
//}

#endif // GLRIR_H
