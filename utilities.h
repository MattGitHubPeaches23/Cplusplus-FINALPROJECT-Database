// Copyright (c) 2019, Matthew Chalifoux.

#ifndef UTILITIES_H
#define UTILITIES_H
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;
void open_fileRW(fstream& f, const char filename[]) throw(char*);
void open_fileW(fstream& f, const char filename[]);
bool file_exists(const char filename[]);
bool read_info(const char filename[], vector<string>& v);
bool write_info(const char filename[], const vector<string> &v);



template<class T>
void show_vector( vector<T>& v){
    for (typename vector<T>::iterator it = v.begin(); it!=v.end(); it++){
        cout<<*it<<"|";
    }
    cout<<endl;

}

// duplicates i bplustree:arrayfunc.h
//template <class T>
//ostream& operator <<(ostream& outs,  const vector<T>& v){
//    for (typename vector<T>::const_iterator it = v.begin(); it!=v.end(); it++){
//        outs<<*it<<"|";
//    }
//    return outs;
//}


//void show_vector(vector<string>& v);

//*************************** C P P ***********************************

void open_fileRW(fstream& f, const char filename[]) throw(char*){
    const bool debug = false;
    //openning a nonexistent file for in|out|app causes a fail()
    //  so, if the file does not exist, create it by openning it for
    //  output:
    if (!file_exists(filename)){
        f.open(filename, std::fstream::out|std::fstream::binary);
        if (f.fail()){
            cout<<"file open (RW) failed: with out|"<<filename<<"]"<<endl;
            throw("file RW failed  ");
        }
        else{
            if (debug) cout<<"open_fileRW: file created successfully: "<<filename<<endl;
        }
    }
    else{
        f.open (filename,
            std::fstream::in | std::fstream::out| std::fstream::binary );
        if (f.fail()){
            cout<<"file open (RW) failed. ["<<filename<<"]"<<endl;
            throw("file failed to open.");
        }
    }

}
void open_fileW(fstream& f, const char filename[]){
    f.open (filename,
            std::fstream::out| std::fstream::binary );
    if (f.fail()){
        cout<<"file open (W) failed: ["<<filename<<"]"<<endl;
        throw("file failed to open.");
    }

}
bool file_exists(const char filename[]){
    const bool debug = false;
    fstream ff;
    ff.open (filename,
        std::fstream::in | std::fstream::binary );
    if (ff.fail()){
        if (debug) cout<<"file_exists: File does NOT exist: "<<filename<<endl;
        return false;
    }
    if (debug) cout<<"file_exists: File DOES exist: "<<filename<<endl;
    return true;
}

bool read_info(const char filename[], vector<string>& v){
    ifstream f;
    f.open(filename);
    if (f.fail()){
        return false;
    }
    string s;
    getline(f, s);
    while (!f.eof()){
        v.push_back(s);
        getline(f, s);
    }
    f.close();
    return true;
}
bool write_info(const char filename[], const vector<string>& v){
    ofstream f;
    f.open(filename);
    if (f.fail()) return false;
    for (int i= 0; i<v.size(); i++){
        f<<v[i]<<endl;
    }
    f.close();
    return true;
}


#endif // UTILITIES_H
