// Copyright (c) 2019, Matthew Chalifoux.

#ifndef TABLE_H
#define TABLE_H
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
#include <iomanip>
#include <iostream>
using namespace std;
template<typename K,typename V>
class Table{
public:
    Table(string t_name, vector<string> f_vector);
    void insert(vector<string> f_value_vector);
    int number_of_fields;
    int file_number;
    int number_of_main_indices;
    string table_name = "";
    vector<string> field_values_vector;
    vector<string> fields_name_vector;

    vector<MMap<K,V> > store;


    int get_size(int p){return store[p].get_size(p);}

};



template<typename K,typename V>
void Table<K,V>::insert(vector<string> f_value_vector){
    for(int p = 0; p < f_value_vector.size(); ++p){
        field_values_vector.push_back(f_value_vector[p]);
    }
    int y = 0;
    if(0 == store.size()){
        for(int p = 0; p < number_of_main_indices; ++p){
            MPair<K,V> here(field_values_vector[p],file_number);
            string temp = field_values_vector[p];
            BPlusTree<MPair<K,V> > sub;
            sub.insert(here);
            MMap<K,V> sub2;
            sub2.insert(field_values_vector[p],file_number);
            store.push_back(sub2);
        }
    }
    else if(0 != store.size()){
        for(int p = 0; p < number_of_fields; ++p){
            store[p].insert(f_value_vector[p],file_number);
            y+=1;
        }
    }

    file_number += 1;
}
template<typename K,typename V>
Table<K,V>::Table(string t_name, vector<string> f_vector){
    table_name = t_name;
    file_number = 0;
    number_of_main_indices = f_vector.size();
    number_of_fields = f_vector.size();
    for(int p = 0; p < f_vector.size(); ++p){
        fields_name_vector.push_back(f_vector[p]);
    }
}
#endif // TABLE_H
