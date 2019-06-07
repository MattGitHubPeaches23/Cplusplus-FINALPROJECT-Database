// Copyright (c) 2019, Matthew Chalifoux.

#ifndef PARSER_H
#define PARSER_H
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
#include "parse_table.h"
#include <iomanip>
#include <cstring>
#include <iostream>
using namespace std;
class Parser{
public:

    Parser(vector<string> get, vector<string> typ);
    vector<string> str;
    vector<string> type;
    int _table[m_r][M_C];
    Parse_Table *link;
    Temp_Table *temp;
    int temp_num;
    int lnum;
    int tnum;

    bool field_names_check_dup2(vector<string>& field_names, Parse_Table *strr);
    bool select_parse2(int &q, int &state);
    bool select_parse(int& q,int& state);
    bool parse_time();
    bool check_start(string ck);
    bool create_parse(int& q, int& state);
    bool insert_parse(int& q, int& state);
    bool get_fields(int& q, int& state, vector<string>& field_names);
    bool not_dup_name(string name);
    bool field_names_check_dup(vector<string>& field_names, string strr);
    bool get_insert_fields(int& q, int& state, vector<string>& field_inserts);
    bool no_dup_inserts(Parse_Table *ptr,vector<string>& field_inserts);
    bool parse_again(vector<string> get, vector<string> typ);

    void mark_all_fail_column(int table[][M_C]);
    void make_table(int _table[][M_C]);
    bool is_success(int _table[][M_C], int state);
    void init_table(int _table[][M_C]);
    void mark_cell(int row, int _table[][M_C], int column, int state);
};
bool Parser::not_dup_name(string name){
    Parse_Table *ptr;
    ptr = link;
    if(0 == ptr->num_fields){return true;}
    if(0 != ptr->num_fields){
        while(ptr != NULL){
            //cout << "GOT IN" << endl;
            if(ptr->tabl_name == name){ return false;}
            ptr = ptr->link;
        }
    }
    return true;
}
bool Parser::field_names_check_dup(vector<string>& field_names, string strr){
    for(int p = 0; p < field_names.size(); ++p){
        if(field_names[p] == strr){cout<<"*(89"<<endl;return false;}
    }
    return true;
}
bool Parser::field_names_check_dup2(vector<string>& hold, Parse_Table *ptr23){

    bool see = false;
    int cnt = 0;
    for(int p = 0; p < hold.size(); ++p){
        for(int k = 0; k < ptr23->fiel_types.size(); ++k){
            if(hold[p] == ptr23->fiel_types[k]){
                cnt += 1;
            }
        }
    }
    if(cnt != hold.size()){return false;}


    return true;
}

bool Parser::get_fields(int &q, int &state, vector<string> &field_names){

//    cout << "q = " << q << endl;
//    cout << "state = " << state << endl;
//    cout << "str[q] = " << str[q] << endl;

    if(!(field_names_check_dup(field_names, str[q]))){cout<<"LILI"<<endl;return false;}
    field_names.push_back(str[q]);
    cout <<"FILD NAMES" << endl;
    for(int p = 0 ; p < field_names.size(); ++p){
        cout << field_names[p] << endl;
    }

    q += 1;
    cout << "TYP{Q} = " << type[q] << endl;
    cout << "str{Q = " << str[q] << endl;
    if((str[q] == "make" || str[q] == "insert" || str[q] == "select") || q == str.size() - 1){
        if(!(is_success(_table,state))){cout<<"MNM"<<endl;return false;}
        //cout << "HELLO TTTOTOTOTO" << endl;
        return true;}
    if(!(str[q] == ",")){cout<<"SDA"<<endl;return false;}
    q += 1;
    return get_fields(q,state,field_names);

}
bool Parser::get_insert_fields(int& q, int& state, vector<string>& field_inserts){

//    cout << "q = " << q << endl;
//    cout << "state = " << state << endl;
//    cout << "str[q] = " << str[q] << endl;


    //cout << "LALALA" << endl;
    if(type[q] == "ALPHA" || type[q] == "NUMBER"){
        if(!(field_names_check_dup(field_inserts, str[q]))){cout<<"ERER"<<endl;return false;}
        //cout << "ASSSSDDD" << endl;
        field_inserts.push_back(str[q]);

        for(int p = 0; p < field_inserts.size(); ++p){
            cout << field_inserts[p] << endl;
        }

        q += 1;
        if((str[q] == "make" || str[q] == "insert" || str[q] == "select") || q == str.size() - 1){
            if(!(is_success(_table,state))){cout<<"ERE"<<endl;return false;}
            //cout << "HELLO TTTOTOTOTO" << endl;
            return true;}
        if(!(str[q] == ",")){cout<<"@23"<<endl;return false;}
        q += 1;
        return get_insert_fields(q,state,field_inserts);
    }


    else if(type[q] == "QUOTATION"){
        //cout << "in quote" << endl;
        int w = q;
        string connect = "\"";
        q+=1;
        while(type[q] != "QUOTATION"){
            //if(type[q] != "ALPHA" && type[q] != "SPACE"){cout<<"007"<<endl;return false;}
            //cout << "connecet = " << connect << endl;
            connect = connect + str[q];
            //cout << "connecet2 = " << connect << endl;
            q+=1;
        }
        //cout << "connecet3 = " << connect << endl;
        connect = connect + str[q];
        if(!(field_names_check_dup(field_inserts, connect))){cout<<"ERER"<<endl;return false;}
        //cout << "ERRTB NN" << endl;
        field_inserts.push_back(connect);

        q += 1;
        if(str[q] == "UNKNOWN" || q == str.size() - 1){
            if(!(is_success(_table,state))){cout<<"ERE"<<endl;return false;}
            //cout << "HELLO TTTOTOTOTO" << endl;
            return true;}
        if(!(str[q] == ",")){cout<<"@23"<<endl;return false;}
        q += 1;
        return get_insert_fields(q,state,field_inserts);


    }



}
bool Parser::create_parse(int &q, int &state){

    string table_name = str[q];
    if(!(not_dup_name(str[q]))){return false;}
    cout << "RTRTRTYYY TYTY TYT " << endl;
    vector<string> field_names;
    state = 3;
    q += 1;
    if(!(str[q] == "fields")){return false;}
    q += 1;
    state = 4;
    if(!(get_fields(q,state, field_names))){cout << "FALSE"<<endl;return false;}

    //test
    cout << "testing gg" << endl;
    for(int p = 0; p < field_names.size(); ++p){
        cout << "field name[p] = " << field_names[p] << endl;
    }

    Parse_Table *ptr;
    ptr = link;

    //cout << "ptr.numfields = " << ptr->num_fields << endl;
    if(0 == ptr->num_fields){
        ptr->add_to_link(table_name,field_names);
        return true;
    }
    if(0 != ptr->num_fields){
        if(ptr->link == NULL){
            ptr->link = new Parse_Table;
            lnum+=1;
            ptr = ptr->link;
            ptr->add_to_link(table_name,field_names);
            return true;
        }
        while(ptr->link != NULL){
            //cout << "GOT INT" << endl;
            ptr = ptr->link;
        }
        ptr->link = new Parse_Table;
        lnum+=1;
        ptr = ptr->link;
        ptr->add_to_link(table_name,field_names);

//        Table<string,string> hope(ptr->tabl_name,ptr->fiel_types);
//        for(int p = 0; p < ptr->fiel_insert.size(); ++p){
//            hope.insert(ptr->fiel_insert[p]);
//        }


        return true;
    }
}
bool Parser::no_dup_inserts(Parse_Table *ptr, vector<string>& field_inserts){

    for(int p = 0; p < ptr->fiel_insert.size(); ++p){
        int cnt = 0;
        for(int k = 0; k < ptr->fiel_insert[p].size(); ++k){
            if(ptr->fiel_insert[p][k] == field_inserts[k]){
                cnt += 1;
            }
        }
        if(cnt == ptr->fiel_insert[p].size()){return false;}
    }
    return true;
}
bool Parser::insert_parse(int &q, int &state){
    cout << "ININSERT " << endl;
    if(not_dup_name(str[q])){cout << "KLKLKL"<<endl;return false;}

    string tname = str[q];
    vector<string> field_inserts;
    state = 8;
    q += 1;
    if(!(str[q] == "values")){cout<<"$T%"<<endl;return false;}
    q += 1;
    state = 9;
    if(!(get_insert_fields(q,state, field_inserts))){cout << "5555FALSE"<<endl;return false;}

    //test
    //cout << "testing WWY" << endl;
    for(int p = 0; p < field_inserts.size(); ++p){
       // cout << "field inserts[p] = " << field_inserts[p] << endl;
    }

    Parse_Table *ptr;
    ptr = link;

    while(ptr->tabl_name != tname){ptr = ptr->link;}
    //cout << "((*(((eere" << ptr->tabl_name << " * " << tname << endl;

    //cout << "ptr.numfields = " << ptr->num_fields << endl;
    if(!(field_inserts.size() == ptr->num_fields)){cout<<"OOP"<<endl;return false;}
    if(!(no_dup_inserts(ptr, field_inserts))){cout << "RRYYRRY^%"<<endl;return false;}
    ptr->fiel_insert.push_back(field_inserts);

    return true;
}
bool Parser::select_parse(int &q, int &state){
    cout << "INTOttt" << endl;
    if(!(str[q] == "from")){cout<<"IO"<<endl;return false;}
    q += 1;
    if(not_dup_name(str[q])){cout << "KLKLKL7878"<<endl;return false;}


    Parse_Table *ptr;
    ptr = link;
    bool over = false;
    do{
        if(ptr->tabl_name != str[q]){
            ptr = ptr->link;
        }
        else if(ptr->tabl_name == str[q]){
            cout << ptr->tabl_name << endl;
            for(int p = 0; p < ptr->num_fields; ++p){
                cout << setw(15) << ptr->fiel_types[p] << "  ";
            }
            cout << endl << endl;
            for(int p = 0; p < ptr->fiel_insert.size(); ++p){
                for(int k = 0; k < ptr->fiel_insert[p].size(); ++k){
                    cout << setw(15) << ptr->fiel_insert[p][k] << "  ";
                }
                cout << endl;
            }
            cout << endl << endl;
            cout << "HIHI" << endl;
            over = true;
        }
    }while(over == false);
    cout << "QQQ = " << q << endl;
    return true;
}
bool Parser::select_parse2(int &q, int &state){

    vector<string> hold;
    cout << "STR[q] = " << str[q] << endl;
    bool turn = false;
    while(str[q] != "from"){
        hold.push_back(str[q]);
        if(str[q+1] == ","){q+=2;}
        else{q+=1;}
    };
    cout << "str[q]2 = " << str[q] << endl;

    if(!(str[q] == "from")){cout<<"Here"<<endl;return false;}
    q+=1;
    string name = str[q];
    if(not_dup_name(name)){return false;}

    Parse_Table *ptr23;
    ptr23 = link;

    while(ptr23->tabl_name != name){ptr23 = ptr23->link;}

    if(!(field_names_check_dup2(hold,ptr23))){cout<<"ERER"<<endl;return false;}

    for(int p = 0; p < hold.size(); ++p){
        cout << "hold[p] = " << hold[p] << endl;
    }

    vector<vector<string> > polk;
    vector<string> catch_field_types;

    Parse_Table *ptr;
    ptr = link;
    bool over = false;
    int index[hold.size()];
    cout << "Talk " << endl;
    do{
        if(ptr->tabl_name != name){
            ptr = ptr->link;
        }
        else if(ptr->tabl_name == name){

            cout << ptr->tabl_name << endl;
            for(int p = 0; p < hold.size(); ++p){
                for(int k = 0; k < ptr->fiel_types.size(); ++k){
                    if(hold[p] == ptr->fiel_types[k]){
                        cout << setw(15) << ptr->fiel_types[k];
                        catch_field_types.push_back(ptr->fiel_types[k]);
                        index[p] = k;
                    }

                }
            }
            //cout << "find?" << endl;
            cout << endl << endl;
            for(int k = 0; k < ptr->fiel_insert.size(); ++k){
                vector<string>  catch_field_values;
                for(int p = 0; p < hold.size(); ++p){                    
                    cout << setw(15) << ptr->fiel_insert[k][index[p]];
                    catch_field_values.push_back(ptr->fiel_insert[k][index[p]]);
                }
                polk.push_back(catch_field_values);
                cout << endl;
            }
            cout << endl;
            cout << endl << endl;
            cout << "HIHI" << endl;
            over = true;
        }
    }while(over == false);
    cout << "here" << endl;



    for(int p = 0; p < polk.size(); ++ p){
        for(int k = 0; k < polk[p].size(); ++k){
            cout << setw(15) <<  polk[p][k] << "  ";
        }
        cout << endl;
    }

    Temp_Table *lp;
    lp = temp;

    if(lp->used == false){
        cout << "hello there678" << endl;
        lp->name = name;
        lp->used = true;
        cout << "TET" << endl;
        for(int p = 0; p < catch_field_types.size(); ++p){
            cout << "ere" << endl;
            lp->field_types.push_back(catch_field_types[p]);
        }
        for(int p = 0; p < polk.size(); ++p){
            cout << "TT2" << endl;
            lp->field_values.push_back(polk[p]);
        }
        cout << "TT" << endl;
    }
    else if(lp->used == true){
        cout << "should be" << endl;
        if(lp->temp == NULL){
            cout << "should be22" << endl;
            lp->temp = new Temp_Table;
            tnum+=1;
            lp = lp->temp;
            lp->name = name;
            lp->used = true;
            for(int p = 0; p < catch_field_types.size(); ++p){
                lp->field_types.push_back(catch_field_types[p]);
            }
            for(int p = 0; p < polk.size(); ++p){
                lp->field_values.push_back(polk[p]);
            }
        }
        else if(lp->temp != NULL){
            while(lp->temp != NULL){
                lp = lp->temp;
            }
            lp->temp = new Temp_Table;
            tnum +=1;
            lp = lp->temp;
            lp->name = name;
            lp->used = true;
            for(int p = 0; p < catch_field_types.size(); ++p){
                lp->field_types.push_back(catch_field_types[p]);
            }
            for(int p = 0; p < polk.size(); ++p){
                lp->field_values.push_back(polk[p]);
            }
        }
    }



    cout << "hereola" << endl;
    cout << lp->name << endl;

    for(int p = 0;  p < lp->field_types.size(); ++p){
        cout << setw(15) << lp->field_types[p];
    }
   cout << endl << endl;
    for(int p = 0;  p < lp->field_values.size(); ++p){
        for(int k = 0; k < lp->field_values[p].size(); ++k){
            cout << setw(15) << lp->field_values[p][k];
        }
        cout << endl;
    }
    cout << endl;




    return true;
}

bool Parser::parse_time(){
    cout << "DO i get in" << endl;
    int state = 0;
    int q = 0;
    while(q != str.size() - 2){
        state = 0;
        //check first input
        cout << "do i get in" << endl;
        if(!(check_start(str[q]))){cout<<"BYBY"<<endl;return false;}
        //check next input
        if(str[q] == "create" || str[q] == "make"){
            q += 1;
            if(!(str[q] == "table")){return false;}
            q += 1;
            state = 2;
            if(!(create_parse(q,state))){cout<<"DS"<<endl;return false;}
        }
        else if(str[q] == "insert"){
            cout << "IN INSERT " << endl;
            q += 1;
            if(!(str[q] == "into")){cout<<"EGF"<<endl;return false;}
            q += 1;
            state = 7;
            if(!(insert_parse(q,state))){cout<<"^&^&0"<<endl;return false;}
        }
        else if(str[q] == "select"){
            cout << "IN SELECT" << endl;
            for(int p = 0; p < str.size(); ++p){
//                cout << str[p] << endl;
//                cout << type[p] << endl;
//                cout << "***************" << endl;
            }
            q+=1;
            if(str[q] == "*"){
                q+=1;
                state = 15;
                if(!(select_parse(q,state))){cout<<"^ttt&0"<<endl;return false;}
                q+=1;
            }
            else if(type[q] != "ALPHA"){cout<<"EREee"<<endl;return false;}
            else {
                state = 15;
                if(!(select_parse2(q,state))){cout<<"ER3"<<endl;return false;}
                q+=1;
            }


            cout << "I;m back " << endl;
            cout << "q = " << q << endl;
            cout << "str size = " << str.size() << endl;
        }
        if(q == str.size() - 1){
            return true;
        }
    }

    return true;
}



Parser::Parser(vector<string> get, vector<string> typ){
    cout << "ININ " << endl;
    for(int p = 0; p < get.size() ; ++p){
//        cout << get[p] << endl;
//        cout << typ[p] << endl;
       // cout << "************" << endl;
    }
    temp_num = 0;
    temp = new Temp_Table;
    tnum = 1;
    bool turn = false;
    for(int p = 0; p < get.size(); ++p){
        string k = get[p];
        string m = typ[p];//took out "*" from stokenizer line 246 --->> changed back to star
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
            str.push_back(k);
            type.push_back(m);
        }
    }
    //test
    //size includes eof() marker I think, size is one bigger than necessary LOOK
    cout << "TRACKING Ttrackinggg" << endl;
    for(int p = 0; p < str.size() ; ++p){
//        cout << str[p] << endl;
//        cout << type[p] << endl;
    //    cout << "************" << endl;
        if(str[p] == "select" && p != str.size() - 1){
            if(str[p+1] == "*"){
                type[p+1] = "FIELDS";
            }
        }
    }
    init_table(_table);
    make_table(_table);
    link = new Parse_Table;
    lnum = 1;
    if(!(parse_time())){cout << "PARSE FAILED" << endl;}
    else{
        cout << "PARSE SUCCESSFUL" << endl;
        Parse_Table *ptr;
        ptr = link;
        while(ptr != NULL){
            cout << ptr->tabl_name << endl;
            for(int p = 0; p < ptr->num_fields; ++p){
                cout << setw(15) << ptr->fiel_types[p] << "  ";
            }
            cout << endl << endl;
            for(int p = 0; p < ptr->fiel_insert.size(); ++p){
                for(int k = 0; k < ptr->fiel_insert[p].size(); ++k){
                    cout << setw(15) << ptr->fiel_insert[p][k] << "  ";
                }
                cout << endl;
            }
            cout << endl << endl;
            ptr = ptr->link;
        }
    }
    return;
}
bool Parser::parse_again(vector<string> get, vector<string> typ){


    //test
    cout << "DDFFDF" << endl;
    for(int p = 0; p < get.size() ; ++p){
//        cout << get[p] << endl;
//        cout << typ[p] << endl;
//        cout << "************" << endl;

//        if(get[p] == "select" && p != get.size() - 1){
//            if(get[p+1] == "*"){
//                typ[p+1] = "FIELDS";
//            }
//        }
    }

    while (!str.empty())
    {
        str.pop_back();
    }
    while (!type.empty())
    {
        type.pop_back();
    }
    for(int p = 0; p < get.size(); ++p){
        str.push_back(get[p]);
        type.push_back(typ[p]);
    }


    cout << "JKLJKL $$" << endl;
     for(int p = 0; p < str.size(); ++p){
//        cout << str[p] << endl;
//        cout << type[p] << endl;
    }
    if(!(parse_time())){cout << "PARSE FAILED" << endl;}
    else{
        cout << "PARSE SUCCESSFUL" << endl;
        Parse_Table *ptr;
        ptr = link;
        while(ptr != NULL){
            cout << ptr->tabl_name << endl;
            for(int p = 0; p < ptr->num_fields; ++p){
                cout << setw(15) << ptr->fiel_types[p] << "  ";
            }
            cout << endl << endl;
            for(int p = 0; p < ptr->fiel_insert.size(); ++p){
                for(int k = 0; k < ptr->fiel_insert[p].size(); ++k){
                    cout << setw(15) << ptr->fiel_insert[p][k] << "  ";
                }
                cout << endl;
            }
            cout << endl << endl;
            ptr = ptr->link;
        }
    }
    return true;
}

void Parser::init_table(int _table[][M_C]){
    for(int i = 0; i < m_r; ++i){
        for(int j = 0; j < M_C; ++j){
            _table[i][j] = -1;
        }
    }
}
void Parser::mark_all_fail_column(int _table[][M_C]){
    for(int i = 0; i < m_r; ++i){
        _table[i][0] = 0;
    }
}
bool Parser::is_success(int _table[][M_C], int state){
    if(_table[state][0] == 1){
        return true;
    }
    else{
        return false;
    }
}
void Parser::mark_cell(int row, int _table[][M_C], int column, int state){
    _table[row][column] = state;
}
void Parser::make_table(int _table[][M_C]){
    init_table(_table);
    mark_all_fail_column(_table);
    mark_cell(4,_table,0,1);
    mark_cell(5,_table,0,1);
    mark_cell(9,_table,0,1);
    mark_cell(10,_table,0,1);
    mark_cell(13,_table,0,1);
    mark_cell(16,_table,0,1);
    mark_cell(0,_table,1,1);
    mark_cell(0,_table,7,6);
    mark_cell(0,_table,15,14);
    mark_cell(1,_table,2,2);
    mark_cell(2,_table,3,3);
    mark_cell(3,_table,4,4);
    mark_cell(4,_table,5,5);
    mark_cell(4,_table,14,4);
    mark_cell(5,_table,6,4);
    mark_cell(5,_table,14,5);
    mark_cell(6,_table,8,7);
    mark_cell(7,_table,9,8);
    mark_cell(8,_table,10,9);
    mark_cell(9,_table,11,10);
    mark_cell(9,_table,12,11);
    mark_cell(10,_table,6,9);
    mark_cell(10,_table,14,10);
    mark_cell(11,_table,11,12);
    mark_cell(12,_table,12,13);
    mark_cell(12,_table,13,11);
    mark_cell(13,_table,6,9);
    mark_cell(13,_table,14,13);
    mark_cell(14,_table,16,15);
    mark_cell(15,_table,17,16);
    mark_cell(16,_table,18,17);

    //test table
    for(int p = 0; p < m_r; ++p){
//        for(int k = 0; k < M_C; ++k){
//            cout << _table[p][k] << "   ";
//        }
//        cout << endl << endl;
    }
}

bool Parser::check_start(string ck){

    if(ck == "create" || ck == "make"){
        //cout << "check_start true" << endl;
        return true;
    }
    else if(ck == "insert"){
        //cout << "check_start true" << endl;
        return true;
    }
    else if(ck == "select"){
        //cout << "check_start true" << endl;
        return true;
    }
    else{
        //cout << "check_start false" << endl;
        return false;
    }
}

#endif // PARSER_H
