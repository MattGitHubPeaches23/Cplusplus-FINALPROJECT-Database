// Copyright (c) 2019, Matthew Chalifoux.

#ifndef PARSE_TABLE_H
#define PARSE_TABLE_H
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
#include "sql.h"
#include <iomanip>
#include <cstring>
#include <iostream>
using namespace std;
const int M_C = 19; // max columns
const int m_r = 17;   // max rows
class Temp_Table{
public:
    Temp_Table(){used = false; temp = NULL;}
    vector<string> field_types;
    vector<vector<string> >  field_values;
    string name;
    bool used;

    Temp_Table *temp;
};

class Parse_Table{
public:
    Parse_Table(){num_fields = 0; num_temp = 0; link = NULL;}
    string tabl_name;
    vector<string> fiel_types;
    vector<vector<string> > fiel_insert;
    int num_fields;
    int num_temp;
    bool is_empty(){if(num_fields == 0){return true;}}
    void add_to_link(string nameee, vector<string> fielddd);

    Parse_Table *link;
};
void Parse_Table::add_to_link(string nameee, vector<string> fielddd){

    tabl_name = nameee;
    for(int p = 0; p < fielddd.size(); ++p){
        string h = fielddd[p];
        fiel_types.push_back(h);
    }
    num_fields = fielddd.size();

}
#endif // PARSE_TABLE_H
