// Copyright (c) 2019, Matthew Chalifoux.

#ifndef MULTIMAP_H
#define MULTIMAP_H
#include <iostream>
#include "bplustree.h"
#include <vector>

template <typename K, typename V>
struct MPair{
    K key;
    vector<V> value_list;

    MPair();
    MPair(const K& k);
    MPair(const K& k, const V& v);
    MPair(const K& k, const vector<V>& vlist);
    template<typename R, typename U>
    friend ostream& operator <<(ostream& outs, const MPair<R, U>& print_me);
//    template<typename R, typename U>
//    friend ostream& operator <<(ostream& outs, const vector<U>& print_me){
//        outs<<print_me[0] <<endl;
//        return outs;
//    }

    template<typename R, typename U>
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs);
    template<typename R, typename U>
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs);
    template<typename R, typename U>
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs);
    template<typename R, typename U>
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs);
    template<typename R, typename U>
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs);
    template<typename R, typename U>
    friend bool operator != (const MPair<K, V>& lhs, const MPair<K, V>& rhs);
    template<typename R, typename U>
    friend bool operator >= (const MPair<K, V>& lhs, const MPair<K, V>& rhs);
};
template<typename K, typename V>
class MMap
{
public:

    typedef BPlusTree<MPair<K, V> > map_base;
        class Iterator{
        public:
            friend class MMap;
            Iterator()
            {
                typename map_base::Iterator bb=NULL;
                _it = bb;
//               typename map_base::Iterator temp;
//               //temp.it=NULL;
//               //temp.key_ptr=0;
//               _it=temp;

                }//{_it = map_base::Iterator();}
            Iterator(typename map_base::Iterator it){
                _it = it;
            }
            Iterator operator ++(int unused)
            {
                return _it++;
            }

            Iterator operator ++()
            {
                return ++_it;
            }

            MPair<K, V> operator *()
            {
                return *_it;
            }

            friend bool operator ==(const Iterator& lhs, const Iterator& rhs) {
                if(lhs._it == rhs._it){
                    return true;
                }
            }

            friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
               if(lhs._it != rhs._it){
                   return true;
               }
            }
            friend bool operator <(const Iterator& lhs, const Iterator& rhs){
                if(lhs._it < rhs._it){
                    return true;
                }
                else if(lhs._it >= rhs._it){
                    return false;
                }
            }
        private:
            typename map_base::Iterator _it;
        };

    MMap();
    Iterator begin(){
        return mmap.begin();
    }
    Iterator end(){
        return mmap.end();
    }
    Iterator lower_bound(K key){
        int j = 0;
        return mmap.lower_bound(key);
    }
    Iterator upper_bound(K key){
        int j = 0;
        return mmap.upper_bound(key);
    }

    vector<V> &  operator[](const K& key){

        BPlusTree<MPair<K,V> > *jkl;
        jkl = &mmap;
        bool on = false;
        if(0 == jkl->get_child_count()){
            for(int p = 0; p < jkl->get_data_count(); ++p){
                if(key == jkl->get_data(p)->key){
                    return jkl->get_data(p)->value_list;
                    on = true;
                }
            }
            //if key is not in multimap
            mmap.insert(key);
            BPlusTree<MPair<K,V> > *pkl;
            pkl = &mmap;
            if(0 == pkl->get_child_count()){
                for(int p = 0; p < pkl->get_data_count(); ++p){
                    if(key == pkl->get_data(p)->key){
                        return pkl->get_data(p)->value_list;
                        on = true;
                    }
                }
            }
            else if(0 != pkl->get_child_count()){
                BPlusTree<MPair<K,V> >  *ptr;
                ptr = pkl->get_smallest_node();
                while(ptr != NULL && on == false){
                    for(int p = 0; p < ptr->get_data_count(); ++p){
                        if(key == ptr->get_data(p)->key){
                            return ptr->get_data(p)->value_list;
                            on = true;
                        }
                    }
                    ptr = ptr->get_next();

                }
            }
        }


        if(0 != jkl->get_child_count()){
            BPlusTree<MPair<K,V> >  *ptr;
            ptr = jkl->get_smallest_node();
            while(ptr != NULL && on == false){
                for(int p = 0; p < ptr->get_data_count(); ++p){
                    if(key == ptr->get_data(p)->key){
                        return ptr->get_data(p)->value_list;
                        on = true;
                    }
                }
                ptr = ptr->get_next();

            }
            //if key is not in multimap
            mmap.insert(key);
            BPlusTree<MPair<K,V> > *pkl;
            pkl = &mmap;
            if(0 == pkl->get_child_count()){
                for(int p = 0; p < pkl->get_data_count(); ++p){
                    if(key == pkl->get_data(p)->key){
                        return pkl->get_data(p)->value_list;
                        on = true;
                    }
                }
            }
            else if(0 != pkl->get_child_count()){
                BPlusTree<MPair<K,V> >  *ptr;
                ptr = pkl->get_smallest_node();
                while(ptr != NULL && on == false){
                    for(int p = 0; p < ptr->get_data_count(); ++p){
                        if(key == ptr->get_data(p)->key){
                            return ptr->get_data(p)->value_list;
                            on = true;
                        }
                    }
                    ptr = ptr->get_next();

                }
            }
        }


    }
    vector<V> &get_vector(K key){
        BPlusTree<MPair<K,V> > *jkl;
        jkl = &mmap;
        bool on = false;
        if(0 == jkl->get_child_count()){
            for(int p = 0; p < jkl->get_data_count(); ++p){
                if(key == jkl->get_data(p)->key){
                    return jkl->get_data(p)->value_list;
                    on = true;
                }
            }
        }



        if(0 != jkl->get_child_count()){
            BPlusTree<MPair<K,V> >  *ptr;
            ptr = jkl->get_smallest_node();
            while(ptr != NULL && on == false){
                for(int p = 0; p < ptr->get_data_count(); ++p){
                    if(key == ptr->get_data(p)->key){
                        return ptr->get_data(p)->value_list;
                        on = true;
                    }
                }
                ptr = ptr->get_next();

            }
            if(on == true){
            }
        }


        if(on == false){
        }
    }

    MMap<K,V> *get_smallest_node();

    bool contains(const K& key) {

//        if(0 == mmap.get_child_count()){
//            for(int p = 0; p < get_data_count(); ++p){
//                if(key == get_data(p).key){
//                    return true;
//                }
//            }
//            return false;
//        }
//        if(0 != mmap.get_child_count){

//        }


        BPlusTree<MPair<K,V> > *jkl;
        jkl = &mmap;


        if(0 != jkl->get_child_count()){
            BPlusTree<MPair<K,V> >  *ptr;
            ptr = jkl->get_smallest_node();
            while(ptr != NULL){
                for(int p = 0; p < ptr->get_data_count(); ++p){
                    if(key == ptr->get_data(p)->key){
                        return true;
                    }
                }
                ptr = ptr->get_next();
            }
            return false;
        }
    }


    void insert(const K& k, const V& v);
    void erase(const K& key);
    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap <<endl;
        return outs;
    }
    K get_data1(int i){return mmap.get_data(i)->key;}
    MPair<K,V> get_data_1(int i){return mmap.get_data(i);}
    unsigned int get_child_count(){
        return mmap.get_child_count();
    }
    unsigned int get_data_count(){
        return mmap.get_data_count();
    }
    BPlusTree<MPair<K,V> > get_data(int i){return mmap.get_data(i);}
    int get_size(int p){ return mmap.get_size();}

private:
    BPlusTree<MPair<K, V> > mmap;


};

template<typename V>
ostream& operator<<(ostream& outs, const vector<V> print_me){
    for(int p = 0; p < print_me.size(); ++p){
        outs<<print_me[p] << " ";
    }
    return outs;
}
template<typename T, typename V>
void operator +=(vector<T>& left, const V& item){
    left.push_back(item);
}


MMap<string, long> get_word_indices(char* file_name){
    const bool debug = false;
    MMap<string, long> word_indices;
    FTokenizer ftk(file_name);
    Token t;
    long count = 0;

    ftk >> t;
    while (ftk.more()){
        //only the "words"
        if (t.type_string() == "ALPHA"){
            string s;
            s = t.token_str();
            word_indices[s] += count;
            count++;
            if (debug)
                cout<<"|"<<t.token_str()<<"|"<<endl;
        }
        ftk >> t;
    }
    return word_indices;
}




template<typename K, typename V>
MMap<K,V>::MMap(){
    mmap = NULL;
}
template<typename K, typename V>
MPair<K,V>::MPair(){
    key = K();
}

//template<typename K, typename V>
//MPair<K,V>::MPair(const K &k, const V &v){
//    key = k;
//    value_list.push_back(v);
//}
template<typename K, typename V>
MPair<K,V>::MPair(const K &k){
    key = k;
}
template<typename K, typename V>
MPair<K,V>::MPair(const K& k, const vector<V>& vlist){
    key = k;
    for(int p = 0; p < vlist.size(); ++p){
        value_list.push_back(vlist[p]);
    }
}
template<typename K, typename V>
MPair<K,V>::MPair(const K &k, const V &v){
    key = k;
    value_list.push_back(v);
}


template<typename K, typename V>
void MMap<K,V>::erase(const K& key){
    mmap.erase(key);
}

template<typename K, typename V>
void MMap<K,V>::insert(const K &k, const V &v){


    //VERSION FOR PUBLIC original
    MPair<K,V> sub(k,v);
    MPair<K,V> *nm;
    nm = &sub;

    BPlusTree<MPair<K,V> > *jkl;
    jkl = &mmap;
    bool on = false;
    if(0 == jkl->get_child_count()){
        for(int p = 0; p < jkl->get_data_count(); ++p){
            if(nm == jkl->get_data(p)){
                for(int k = 0; k < jkl->get_data(p)->value_list.size(); ++k){
                    if(jkl->get_data(p)->value_list[k] == nm->value_list[0]){
                        return;
                    }
                }
                jkl->get_data(p)->value_list.push_back(sub.value_list[0]);
                on = true;
                return;
            }
        }
    }



    if(0 != jkl->get_child_count()){
        BPlusTree<MPair<K,V> >  *ptr;
        ptr = jkl->get_smallest_node();
        while(ptr != NULL && on == false){
            for(int p = 0; p < ptr->get_data_count(); ++p){
                if(nm->key == ptr->get_data(p)->key){
                    for(int k = 0; k < ptr->get_data(p)->value_list.size(); ++k){
                        if(ptr->get_data(p)->value_list[k] == nm->value_list[0]){
                            return;
                        }
                    }
                    V ii = nm->value_list[0];
                    ptr->get_data(p)->value_list.push_back(ii);
                    on = true;
                }
            }
            ptr = ptr->get_next();

        }
        if(on == true){
            return;
        }
    }


    if(on == false){
        mmap.insert(sub);
    }


}

//template<typename K, typename V>
//void MMap<K,V>::insert(const K& k, const vector<V>& vlist){
//    MPair<K,V> sub(k,vlist);
//    mmap.insert(sub);
//}

template<typename R, typename U>
ostream& operator <<(ostream& outs, const MPair<R, U>& print_me){

    outs <<"{"<< print_me.key<<": ";
//    outs << print_me.value_list[0];
//    cout << "print_me.value_list.size() = " << print_me.value_list.size() << endl;

    for(int p = 0; p < print_me.value_list.size(); ++p){
        outs << print_me.value_list[p] << ": ";
    }
    return outs;
    //outs <<"{"<< print_me.key<<": ";
    //cout <<print_me.value_list <<"}";
}


template<typename R, typename U>
bool operator ==(const MPair<R, U>& lhs, const MPair<R, U>& rhs){
    if(lhs.key == rhs.key){
        return true;
    }
    else if(!(lhs.key == rhs.key)){
        return false;
    }

}
template<typename R, typename U>
bool operator < (const MPair<R, U>& lhs, const MPair<R, U>& rhs){
    if(lhs.key < rhs.key){
        return true;
    }
    else if(!(lhs.key < rhs.key)){
        return false;
    }
}
template<typename R, typename U>
bool operator > (const MPair<R, U>& lhs, const MPair<R, U>& rhs){
    if(lhs.key > rhs.key){
        return true;
    }
    else if(!(lhs.key > rhs.key)){
        return false;
    }
}
template<typename R, typename U>
bool operator <= (const MPair<R, U>& lhs, const MPair<R, U>& rhs){
    if(lhs.key <= rhs.key){
        return true;
    }
    else if(!(lhs.key <= rhs.key)){
        return false;
    }
}
template<typename R, typename U>
MPair<R, U> operator + (const MPair<R, U>& lhs, const MPair<R, U>& rhs){

}
template<typename R, typename U>
bool operator != (const MPair<R, U>& lhs, const MPair<R, U>& rhs){
    if(lhs.key != rhs.key){
        return true;
    }
    else if(!(lhs.key != rhs.key)){
        return false;
    }
}
template<typename R, typename U>
bool operator >= (const MPair<R, U>& lhs, const MPair<R, U>& rhs){
    if(lhs.key >= rhs.key){
        return true;
    }
    else if(!(lhs.key >= rhs.key)){
        return false;
    }
}

#endif // MULTIMAP_H
