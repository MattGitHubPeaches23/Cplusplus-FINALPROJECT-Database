// Copyright (c) 2019, Matthew Chalifoux.

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
#include "parser.h"
#include "parse_table.h"
#include <iomanip>
#include <cstring>
#include <iostream>
using namespace std;



int main(int argc, char *argv[])
{
    int m = 0; // JUST TO HIDE  TESTING
    if(0 == m){
//            vector<string> f_vector;
//            f_vector.push_back("last");
//            f_vector.push_back("first");
//            f_vector.push_back("major");

//            vector<string> f_value_vector;
//            f_value_vector.push_back("Yang");
//            f_value_vector.push_back("Bo");
//            f_value_vector.push_back("Computer Science");

//            vector<string> f_value_vector2;
//            f_value_vector2.push_back("Davis");
//            f_value_vector2.push_back("John");
//            f_value_vector2.push_back("Math");

//            vector<string> f_value_vector3;
//            f_value_vector3.push_back("Johnson");
//            f_value_vector3.push_back("Mary Ann");
//            f_value_vector3.push_back("Biology");

//        //    vector<string> f_value_vector4;
//        //    f_value_vector4.push_back("Johnson");
//        //    f_value_vector4.push_back("Bo");
//        //    f_value_vector4.push_back("Biology");

//            Table<string,int> student("student", f_vector);
//            student.insert(f_value_vector);
//            student.insert(f_value_vector2);
//            student.insert(f_value_vector3);
//            //student.insert(f_value_vector4);

//            vector<string> f_vector_2;
//            f_vector_2.push_back("lname");
//            f_vector_2.push_back("fname");
//            f_vector_2.push_back("dept");
//            f_vector_2.push_back("year_hired");

//            vector<string> f_value_vector_2;
//            f_value_vector_2.push_back("Jackson");
//            f_value_vector_2.push_back("David");
//            f_value_vector_2.push_back("Finance");
//            f_value_vector_2.push_back("2016");

//            vector<string> f_value_vector2_2;
//            f_value_vector2_2.push_back("Davidson");
//            f_value_vector2_2.push_back("Mary Alice");
//            f_value_vector2_2.push_back("complaints");
//            f_value_vector2_2.push_back("2012");

//            Table<string,int> employee("employee", f_vector_2);
//            employee.insert(f_value_vector_2);
//            employee.insert(f_value_vector2_2);

//            cout << "table_name = " << student.table_name << endl;

//            for(int p = 0; p < student.number_of_fields; ++p){
//                cout << "field = " << student.fields_name_vector[p] << endl;
//            }

//            for(int p = 0; p < student.field_values_vector.size(); ++p){
//                cout << "field value = " << student.field_values_vector[p] << endl;
//            }

//            cout << endl << "**************************" << endl;
//            for(int p = 0; p < student.store.size(); ++p){
//                cout << student.store[p] << endl;
//            }
//            cout << endl << "**************************" << endl;
//            for(int p = 0; p < employee.store.size(); ++p){
//                cout << employee.store[p] << endl;
//            }

//            Table_Log<string,int> tL;
//            tL.insert("student", student);
//            tL.insert("employee", employee);

//            cout << "tl.num of tables = " << tL.num_of_tables << endl;
//            for(int p = 0; p < tL.table_names.size(); ++p){
//                cout << "table name = " << tL.table_names[p] << endl;
//            }

//            for(int p = 0; p < tL.tables.size() ; ++p){
//                for(int j = 0; j < tL.tables[p].store.size(); ++j){
//                    cout << "tL.tables[p] = " << tL.tables[p].store[j] << endl;
//                }
//            }

//            vector<string> jkl;
//            //jkl.push_back("last");
//            jkl.push_back("first");
//            jkl.push_back("major");

//            tL.select("student", jkl);



//            vector<string> field_name;
//            field_name.push_back("major");
//            field_name.push_back("last");

//            vector<string> operate;
//            operate.push_back("=");
//            operate.push_back(">");

//            vector<string> value;
//            value.push_back("Math");
//            value.push_back("Davis");

//            vector<string> logical;
//            logical.push_back("and");


//        //    tL.select_specific("student",field_name,operate,value,logical);
    }

    string g = "_!batch_file.batch";

    SQL test(g);

    //test.interactive();


    cout<<"NN"<<endl;



//    Parse_Table *lm;
//    lm = test.parser_time->link;
//    cout << "lm " << lm->tabl_name << endl;


//    vector<Table<string,int> > lop;
//    for(int p = 0; p < num; ++p){
//        Parse_Table *pl;
//        pl = test.parser_time->link;
//        if(p != 0){
//            for(int j = 0; j < p; ++j){
//                pl = pl->link;
//            }
//        }
//        Table<string,int> here(pl->tabl_name, pl->fiel_types);
//        for(int k = 0; k < pl->fiel_insert.size(); ++k){
//            here.insert(pl->fiel_insert[k]);
//        }
//        lop.push_back(here);
//    }


//    for(int p = 0; p < num; ++p){
//        Parse_Table *pl;
//        pl = test.parser_time->link;
//        if(p != 0){
//            for(int j = 0; j < p; ++j){
//                pl = pl->link;
//            }
//        }
//        Table<string,int> here(pl->tabl_name, pl->fiel_types);
//        for(int k = 0; k < pl->fiel_insert.size(); ++k){
//            here.insert(pl->fiel_insert[k]);
//        }
//        lop.push_back(here);
//    }






//    cout << "LLOOL" << endl;
//    for(int p = 0; p < lop.size(); ++p){
//        cout << lop[p].store;
//    }







//    Table_Log<string,int> first;
//    //first.insert(test.parser_time->temp->name, test.parser_time->temp);





    //cout << here.store;



    //REMEMBER SIZE IS ONE LONGER THAN IS NECESSARY, eof() I think


//        long recno;
//        fstream f;


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




    return 0;
}
