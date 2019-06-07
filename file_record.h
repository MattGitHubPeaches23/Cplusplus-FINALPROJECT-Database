// Copyright (c) 2019, Matthew Chalifoux.

#ifndef FIELD_H
#define FIELD_H
#include <iostream>
#include  <fstream>
#include <string>
#include <iomanip>
using namespace std;
const int MAX_RECORD_WIDTH = 50;
struct file_record{
public:
    file_record(long r = 0);
    long rec_no();
    streampos write(fstream& outs);
    streampos read(fstream &ins, streampos recno);
    friend ostream& operator <<(ostream& out,
                          const file_record& r);


    char record[MAX_RECORD_WIDTH][MAX_RECORD_WIDTH];
};

//******************** C P P ******************************************************



file_record::file_record(long r)
{
    strcpy(record[0], to_string(r).c_str());
    for (int i = 1 ; i<MAX_RECORD_WIDTH; i++)
        record[i][0] = NULL;
}
long file_record::rec_no(){

    return stol(string(record[0]));
}

streampos file_record::write(fstream& outs){
    //write to the end of the file.

    streampos pos = outs.tellp();
    outs.write(&record[0][0], sizeof(record));
    return pos/sizeof(record);
}

streampos file_record::read(fstream& ins, streampos recno){
    streampos pos= recno * sizeof(record);
    ins.seekg(pos, ios_base::beg);
    //ins.read(&record[1][0], MAX_RECORD_WIDTH*(MAX_RECORD_WIDTH-1));
    ins.read(&record[0][0], sizeof(record));
    return ins.gcount();
}

ostream& operator <<(ostream& outs,
                      const file_record& r){
    for (int i=0; r.record[i][0]!= NULL && i<MAX_RECORD_WIDTH; i++){
            outs<<setw(15)<<r.record[i];
    }
    return outs;
}


#endif // FIELD_H
