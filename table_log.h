// Copyright (c) 2019, Matthew Chalifoux.

#ifndef TABLE_LOG_H
#define TABLE_LOG_H
#include "ftokenizer.h"
#include "multimap.h"
#include "bplustree.h"
#include "stokenizer.h"
#include <fstream>
#include "file_record.h"
#include "utilities.h"
#include "consts.h"
#include "glrir.h"
#include "table.h"
#include <iomanip>
#include <iostream>
using namespace std;

template<typename K,typename V>
class Table_Log{
public:
    Table_Log(){
        num_of_tables = 0; num_of_indices = 0;
    }
    void select(string t_name, vector<string> fields);
    void insert(string t_name, Table<K,V> full_table);
    int num_of_tables;
    vector<string> table_names;
    vector<Table<K,V> > tables;

    int num_of_indices;
    vector<string> indices_field_names;
    vector<MMap<K,V> > indices;
};

//***************************** C P P *********************************

template<typename K, typename V>
void Table_Log<K,V>::insert(string t_name, Table<K, V> full_table){
    table_names.push_back(t_name);
    tables.push_back(full_table);
    num_of_tables += 1;
}


template<typename K,typename V>
void Table_Log<K,V>::select(string t_name, vector<string> fields){
    //check if name exists and set index of table
    bool name_exists = false;
    int t_name_index = 0;
    for(int p = 0; p < table_names.size(); ++p){
        if(t_name == table_names[p]){
            name_exists = true;
            t_name_index = p;
            cout << "NAME EXISTS" << endl;
        }
    }
    if(name_exists == false){
        cout << "NAME DOES NOT EXIST" << endl;
        return;
    }
    //check is fields exist and set index of tables
    int field_index[fields.size()];
    bool fields_exist[fields.size()];
    for(int p = 0; p < fields.size(); ++p){
        fields_exist[p] = false;
    }
    for(int p = 0; p < fields.size(); ++p){
        for(int j = 0; j < tables[t_name_index].fields_name_vector.size(); ++j){
            if(fields[p] == tables[t_name_index].fields_name_vector[j]){
                fields_exist[p] = true;
                field_index[p] = j;
                //cout << "FIELD EXISTS" << endl;
            }
        }
    }
    int check = 0;
    for(int p = 0; p < fields.size(); ++p){
        if(fields_exist[p] == true){
            check += 1;
        }
    }
    if(check == fields.size()){
        cout << "ALL FIELDS EXIST" << endl;
    }
    else if(check != fields.size()){
        cout << "A FIELD WAS ENTERED THAT DOES NOT EXIST" << endl;
        return;
    }

    for(int p = 0; p < fields.size(); ++p){
        //cout << "field index["<<p<<"]= "<< field_index[p] << endl;
    }


    //cout << "fields size = " << fields.size() << endl;
    //cout table to screen
    for(int p = 0; p < fields.size(); ++p){
        cout << setw(25) << fields[p];
    }
    cout << endl;
    cout << endl;

    int h = 0;
    int v = 0;
    for(int s = 0; s < tables[t_name_index].file_number; ++s){
        h = v;
        for(int j = 0; j < fields.size(); ++j){
            v = h + field_index[j];
            cout << setw(25) << tables[t_name_index].field_values_vector[v];
        }
        v = h;
        v += 3;
        cout << endl;
    }
}

#endif // TABLE_LOG_H
