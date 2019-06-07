// Copyright (c) 2019, Matthew Chalifoux.

#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

template<typename T>
class BPlusTree{
public:
    struct LinkedList{
        BPlusTree<T> *head_ptr;
        BPlusTree<T> *move_ptr;
        LinkedList():head_ptr(NULL), move_ptr(NULL){}
        void insert(BPlusTree<T> *kl){
            if(head_ptr == NULL){
                head_ptr = kl;
                move_ptr = head_ptr;
                return;
            }
            else if(head_ptr != NULL){
                move_ptr = head_ptr;
                while(move_ptr->next != NULL){
                    move_ptr = move_ptr->next;
                }
                move_ptr->next = kl;
                move_ptr = head_ptr;
            }
        }
    };
    class Iterator{
        public:
            friend class BPlusTree;
            Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0):it(_it), key_ptr(_key_ptr){}
            T operator *(){
                assert(key_ptr<it->data_count);
                return it->data[key_ptr];
            }
            Iterator operator++(int un_used){
                key_ptr += 1;
                if(key_ptr == it->data_count){
                    key_ptr = 0;
                    it = it->next;
                }
            }
            Iterator operator++(){
                key_ptr += 1;
                if(key_ptr == it->data_count){
                    key_ptr = 0;
                    it = it->next;
                }
            }
            int get_key_ptr()const {return key_ptr;}
            friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
                int l = lhs.get_key_ptr();
                int r = rhs.get_key_ptr();
                if(lhs.it->get_data(l) == rhs.it->get_data(r)){
                    return true;
                }
                else if(lhs.it->get_data(l) != rhs.it->get_data(r)){
                    return false;
                }
            }
            friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
                int l = lhs.get_key_ptr();
                int r = rhs.get_key_ptr();
                if(lhs.it->get_data(l) != rhs.it->get_data(r)){
                    return true;
                }
                else if(lhs.it->get_data(l) == rhs.it->get_data(r)){
                    return false;
                }
            }
            friend bool operator <=(const Iterator& lhs, const Iterator& rhs){
                if(lhs.it->get_data(get_key_ptr()) <= rhs.it->get_data(get_key_ptr())){
                    return true;
                }
                else if(lhs.it->get_data(get_key_ptr()) > rhs.it->get_data(get_key_ptr())){
                    return false;
                }
            }
            friend bool operator <(const Iterator& lhs, const Iterator& rhs){
                if(lhs.it->get_data(get_key_ptr()) < rhs.it->get_data(get_key_ptr())){
                    return true;
                }
                else if(lhs.it->get_data(get_key_ptr()) >= rhs.it->get_data(get_key_ptr())){
                    return false;
                }
            }
            friend bool operator >(const Iterator& lhs, const Iterator& rhs){
                if(lhs.it->get_data(get_key_ptr()) > rhs.it->get_data(get_key_ptr())){
                    return true;
                }
                else if(lhs.it->get_data(get_key_ptr()) <= rhs.it->get_data(get_key_ptr())){
                    return false;
                }
            }
            friend bool operator >=(const Iterator& lhs, const Iterator& rhs){
                if(lhs.it->get_data(get_key_ptr()) >= rhs.it->get_data(get_key_ptr())){
                    return true;
                }
                else if(lhs.it->get_data(get_key_ptr()) < rhs.it->get_data(get_key_ptr())){
                    return false;
                }
            }
            void print_Iterator(){
                //cout << it->data[key_ptr];
                for(int i = 0; i < it->data_count; ++i){
                    cout << it->data[i] << "  ";
                }
            }
            bool is_null(){
                if(it == NULL){
                    return true;
                }
                else if(it != NULL){
                    return false;
                }
            }
        private:
            BPlusTree<T>* it;
            int key_ptr;
        };
public:
    Iterator upper_bound(T key);
    BPlusTree<T>* get_upper_node(T key, int& j);
    BPlusTree<T>* get_node(T key, int& j);
    Iterator lower_bound(T key);
    Iterator find(const T& entry);
    int size2(int& size) const;
    int size() const;
    bool empty()const;
    Iterator begin();
    Iterator end();
    BPlusTree(bool dups = false);
    BPlusTree(const BPlusTree<T>& rhs);
    BPlusTree<T>& operator =(const BPlusTree<T>& rhs);
    ~BPlusTree();
    //BPlusTree<T>* get_smallest();
    BPlusTree<T>* get_largest();
    bool contains(const T& entry) const;
    bool check_Dups(const T& item) const;
    void clear_tree();
    void make_twins(BPlusTree<T> *twin, BPlusTree<T> *twin2, int i, int num);
    void insert_item(const T item, BPlusTree<T> *ptr);
    void split_Node(int i);
    void copy_tree3(BPlusTree<T>* left,const BPlusTree<T>* right, LinkedList &test);
    void copy_tree_2(BPlusTree<T>* left,const BPlusTree<T>* right);
    void copy_tree(BPlusTree<T>* left,const BPlusTree<T>* right);
    void insert(const T& item);
    void erase(const T& target);
    void print_tree(int level = 0, ostream& outs = cout) const;
    void print_tree_sub();
    void print_tree_two(int level = 0, ostream& outs = cout) const;
    template<typename U>
    friend ostream& operator <<(ostream& outs, const BPlusTree<U>& print_me);
    BPlusTree<T>* get_smallest_node();
    unsigned int get_child_count(){return child_count;}
    unsigned int get_data_count(){return data_count;}
    T *get_data(int i){return &data[i];}
    BPlusTree<T> *get_next(){return next;}


private:

    bool is_leaf() const {return child_count==0;}
    bool dups_ok;
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;
    T data[MAXIMUM + 1];
    BPlusTree *subset[MAXIMUM + 2];
    BPlusTree *next;
    BPlusTree *previous;
    unsigned int child_count;
    unsigned int data_count;
    void fix_excess_first(int i);
    void fix_excess_root(int i);
    void fix_excess(int i);
    void enter_Data(T item);
    void loose_erase(const T& target);
    void shift_data(int i);
    void fix_shortage(int i);
    void remove_biggest(T& removed_entry);
    void case_one(int i);
    void case_two(int i);
    void case_three(int i);
    void case_four(int i);
    void fix_erase_root(int i);
};

template<typename T>
bool BPlusTree<T>::contains(const T& entry) const{
    BPlusTree<T> *ptr;
    ptr = subset[0]->get_smallest_node();
    while(ptr->next != NULL){
        for(int p = 0; p < ptr->data_count; ++p){
            if(entry == ptr->data[p]){
                return true;
            }
        }
        ptr = ptr->next;
    }
    return false;
}
template<typename T>
int BPlusTree<T>::size2(int& size) const{
    size += 1;
    if(0 == child_count){
        return size;
    }
    else if(0 != child_count){
        for(int p = 0; p < child_count; ++p){
            if(subset[p]->child_count != 0){
                subset[p]->size2(size);
                return size;
            }
        }
    }
}
template <typename T>
int BPlusTree<T>::size() const{
    //this function counts the number of keys in the btree
    int size = child_count;
    if(0 == child_count){
        return size = 1;
    }
    else if(0 != child_count){
        for(int p = 0; p < child_count; ++p){
            if(subset[p]->child_count != 0){
                subset[p]->size2(size);
            }
        }
        return size;
    }



    return size;
}
template <typename T>
bool BPlusTree<T>::empty() const{
    return (data_count ==0);
}

template<typename T>
BPlusTree<T>* BPlusTree<T>::get_upper_node(T key, int& j){
    BPlusTree<T> *ptr, *two, *nothing;
    nothing = NULL;
    ptr = get_smallest_node();
    for(int p = 0; p < ptr->data_count; ++p){
        if(key < ptr->data[p]){
            j = p;
            return ptr;
        }
    }
    two = get_smallest_node();
    while(two != NULL){
        for(int p = 0; p < two->next->data_count; ++p){
            if(key < two->next->data[p]){
                j = p;
                return two->next;
            }
        }
        two = two->next;
    }
}
template<typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(T key){
    int j = 0;
    BPlusTree<T> *op;
    op = get_upper_node(key,j);
    Iterator jj(op,j);
    return jj;
}
template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(T key){
    int j = 0;
    BPlusTree<T> *op;
    op = get_node(key,j);
    Iterator jj(op,j);
    return jj;
}
template<typename T>
BPlusTree<T>* BPlusTree<T>::get_node(T key, int& j){
    BPlusTree<T> *ptr, *two, *nothing;
    nothing = NULL;
    ptr = get_smallest_node();
    for(int p = 0; p < ptr->data_count; ++p){
        if(key == ptr->data[p]){
            j = p;
            return ptr;
        }
    }
    two = ptr;
    while(two != NULL){
        for(int p = 0; p < two->next->data_count; ++p){
            if(key == two->next->data[p]){
                j = p;
                return two->next;
            }
        }
        two = two->next;
    }
}
template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin(){
    return Iterator(get_smallest_node());
}
template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end(){
    return Iterator(NULL);
}
template<typename T>
BPlusTree<T>* BPlusTree<T>::get_smallest_node(){


    if(subset[0]->child_count > 0){
        subset[0]->get_smallest_node();
    }
    else if(0 == subset[0]->child_count){
        BPlusTree<T> *hj;
        hj = subset[0];
        return hj;
    }
}
template<typename T>
BPlusTree<T>* BPlusTree<T>::get_largest(){

    if(subset[child_count - 1]->child_count > 0){
        subset[child_count - 1]->get_largest();
    }
    else if(0 == subset[child_count - 1]->child_count){
        BPlusTree<T> *hj;
        hj = subset[child_count - 1];
        return hj;
    }

}

template<typename T>
void BPlusTree<T>::shift_data(int i){

    // if target is in first spot in array
    // delete first data item,shift all items leftward
    // subtract one from data_count
    if(0 == i){
        T sub[data_count - 1];
        int l = 0;
        for(int p = 1; p < data_count ; ++p){
            sub[l] = data[p];
            ++l;
        }
        for(int p = 0; p < data_count - 1; ++p){
            data[p] = sub[p];
            //cout << "data[" << p << "] = " << data[p] << endl;
        }
        data_count -= 1;
        return;
    }

    // if target is the last item in the array
    //delete last item
    //subtract one from data_count
    if(i == data_count - 1){
        data[i] = T();
        data_count -= 1;
        return;
    }

    // if target is in the middle array
    //copy the items before i
    //copy the items after i
    //combine the items before i and after i so that the item you wanted
    //is no longer there
    //reduce data_count by one
    T here[i], here2[data_count - (i + 1)];
    for(int j = 0; j < i; ++j){
        here[j] = data[j];
    }
    int p = 0;
    for(int j = i + 1; j < data_count ; ++j){
        here2[p] = data[j];
        ++p;
    }
    for(int j = 0; j < i; ++j){
        data[j] = here[j];
    }
    p = 0;
    for(int j = i; j < data_count - 1; ++j){
        data[j] = here2[p];
        ++p;
    }
    data_count -= 1;
}
template<typename T>
void BPlusTree<T>::case_three(int i){
    //cout << "CaSe 3" << endl;
    //Part A case 3
    //cout << "Part A case 3" << endl;
    //Transfer data[i-1] down to the end of subset[i-1]->data.
    //Shift data items to the left one space to fill the gap
    //Subtract one from data_count and add one to subset[i-1]->data_count
    T here;
    here = data[i - 1];
    subset[i - 1]->data[subset[i - 1]->data_count] = here;
    //cout << "here = " << here << endl;

    for(int p = i - 1; p < data_count - 1; ++p){
        data[p] = data[p + 1];
    }

    subset[i - 1]->data_count += 1;
    data_count -= 1;

    //Part B case 3
    //Transfer all items and children from subset[i] to the end of subet[i-1]
    //Update the values of subset[i-1]->data_count and subset[i-1]->child_count
    //Set subset[i]->data_count and subset[i]->child_count to zero
    int u = subset[i - 1]->data_count;
    for(int p = 0; p < subset[i]->data_count; ++p){
        subset[i - 1]->data[u] = subset[i]->data[p];
        ++u;
        subset[i - 1]->data_count += 1;
    }
    //cout << "PRI PRI" << endl;
    //subset[i-1]->print_tree_two();

    int m = subset[i - 1]->child_count;
    for(int p = 0; p < subset[i]->child_count; ++p){
        //subset[i-1]->subset[m]->clear_tree();
        subset[i - 1]->subset[m] = new BPlusTree<T>;
        copy_tree(subset[i - 1]->subset[m], subset[i]->subset[p]);
        subset[i - 1]->data[m] = subset[i]->data[p];
        ++m;
        subset[i - 1]->child_count += 1;
    }
    subset[i]->data_count = 0;
    subset[i]->child_count = 0;

    // Part C
    //Delete the node subset[i] and move all subsets to the right leftward
    //one position
    //Reduce child_count by one
//    subset[i]->clear_tree();
//    subset[i] = NULL;
    for(int p = i; p < child_count - 1; ++p){
        subset[p]->clear_tree();
        subset[p] = new BPlusTree<T>;
        copy_tree(subset[p], subset[p + 1]);
        subset[p+1]->clear_tree();
    }



    child_count -= 1;

//    cout << "KO KO" << endl;
//    print_tree_two();


}
template<typename T>
void BPlusTree<T>::case_four(int i){
//    cout << "case_four four" << endl;

//    cout << "TESTING" << endl;
//    for(int i = 0; i < child_count; ++i){
//        subset[i]->print_tree_two();
//    }

    //Part A -- move subset[i + 1]->data over one space to the right
    for(int p = subset[i + 1]->data_count; p > 0; --p){
        subset[i + 1]->data[p] = subset[i + 1]->data[p - 1];
    }
    subset[i+1]->data_count += 1;
    //Transfer data i down to the front of subset[i + 1]->data
    subset[i + 1]->data[0] = data[i];

//    cout << "MARK MARK" << endl;
//    print_tree_two();

    //Add one to subset[i + 1]->data_count
    //subset[i + 1]->data_count += 1;
    //cout << "PPP" << endl;
    //subset[i+1]->print_tree_two();
//    for(int p = 0; p < subset[i+1]->data_count; ++p){
//        cout << "subset[i+1]->data[" << p << "] = " << subset[i+1]->data[p] << endl;
//    }

    //Subtract one from data_count
    data_count -= 1;

    //Shift data left one space
    for(int p = i; p < data_count; ++p){
        data[p] = data[p + 1];
    }
//    cout << "BB" << endl;
//    print_tree_two();
//    for(int p = 0; p < data_count; ++p){
//        cout << "data[" << p << "] = " << data[p] << endl;
//    }

//    for(int p = 0; p < subset[i]->data_count; ++p){
//        cout << "subset[i]->data[" << p << "] = " << subset[i]->data[p] << endl;
//    }

    T item[subset[i]->data_count], item2[subset[i + 1]->data_count];

    for(int k = 0; k < subset[i]->data_count; ++k){
        item[k] = subset[i]->data[k];
        //cout << "item[" << k << "] = " << item[k] << endl;
    }
    for(int k = 0; k < subset[i + 1]->data_count; ++k){
        item2[k] = subset[i + 1]->data[k];
        //cout << "item2[" << k << "] = " << item2[k] << endl;
    }

    int gh = subset[i + 1]->data_count;
    subset[i + 1]->data_count = 0;

    int y = 0;
    for(int k = 0; k < subset[i]->data_count; ++k){
        subset[i + 1]->data[k] = item[k];
        subset[i + 1]->data_count += 1;
        ++y;
    }
    for(int k = 0; k < gh; ++k){
        subset[i + 1]->data[y] = item2[k];
        subset[i + 1]->data_count += 1;
        ++y;
    }

//    cout << "KPKPKPPPPP" << endl;
//    print_tree_two();

    //Part B
    //Move subset[i + 1]->data over right and add items from subset[i]
//    int t = subset[i]->data_count;
//    cout << "t = " << t << endl;
//    int j = subset[i + 1]->data_count;
//    cout << "j = " <<j << endl;
//    int p = j + t - 1;

//    if(subset[i]->data_count != 0){
//        for(int s = 0; s < j + 1; ++s){
//            subset[i + 1]->data[p] = subset[i + 1]->data[p - 1];
//            --p;
//        }
//        cout << "FF" << endl;
//        subset[i+1]->print_tree_two();
//        int h = t;
//        for(int s = 0; s < h; ++s){
//            subset[i + 1]->data[t - 1] = subset[i]->data[t - 1];
//            subset[i + 1]->data_count += 1;
//            --t;
//        }
//        cout << "FF2" << endl;
//        subset[i+1]->print_tree_two();
//        subset[i]->data_count = 0;
//        cout << "ff2" << endl;
//        subset[i]->print_tree_two();
//    }
//    cout << "AAA" << endl;
//    print_tree_two();
//    for(int p = 0; p < subset[i+1]->data_count; ++p){
//        cout << "subset[i+1]->data[" << p << "] = " << subset[i+1]->data[p] << endl;
//    }

    //Part C
    //Transfer all children from subset[i] to the front of subset[i + 1]
    int t = subset[i]->child_count;
    //cout << "tt = " << t << endl;
    int j = subset[i + 1]->child_count;
    //cout << "jj = " << j << endl;
    int p = j + t - 1;


    if(subset[i]->child_count != 0){
        //cout << "Doing" << endl;

        BPlusTree<T> *hj[t], *hj2[j];

        //cout << " OP l" << endl;
        for(int k = 0; k < t; ++k){
            hj[k] = new BPlusTree<T>;
            copy_tree(hj[k],subset[i]->subset[k]);
            //hj[k]->print_tree_two();
        }


        //cout << "op 2" << endl;
        for(int k = 0; k < j; ++k){
            hj2[k] = new BPlusTree<T>;
            copy_tree(hj2[k],subset[i + 1]->subset[k]);
            //hj2[k]->print_tree_two();
        }

        for(int k = 0; k < j; ++k){
            subset[i + 1]->subset[k]->clear_tree();
            subset[i + 1]->subset[k] = NULL;
        }
        subset[i + 1]->child_count = 0;

        for(int k = 0; k <= p; ++k){
            subset[i + 1]->subset[k] = new BPlusTree<T>;
            subset[i + 1]->child_count += 1;
        }
        for(int k = 0; k < t; ++k){
            copy_tree(subset[i+1]->subset[k],hj[k]);
        }
        int y = 0;
        for(int k = t; k <= p; ++k){
            copy_tree(subset[i + 1]->subset[k], hj2[y]);
            ++y;
        }
        for(int k = 0; k < t; ++k){
            hj[k]->clear_tree();
            delete hj[k];
        }
        y = 0;
        for(int k = t; k <=p; ++k){
            hj2[y]->clear_tree();
            delete hj2[y];
            ++y;
        }
    }




//    cout << "IIJJKKK" << endl;
//    print_tree_two();


    //cout << "child_count = " << child_count << endl;

    //Part D
    //Clear subset[i]  and move all children to the left one spot

    BPlusTree<T> *ptr[child_count - 1];

    int l = 0;
    for(int p = i + 1; p < child_count; ++p){
        ptr[l] = new BPlusTree<T>;
        copy_tree(ptr[l],subset[p]);
        ++l;
    }
//    for(int p = 0; p < l; ++p){
//        cout << "subset33  " << p << endl;
//        ptr[p]->print_tree_two();
//    }

    for(int p = i; p < child_count; ++p){
        subset[p]->clear_tree();
    }
    child_count -= 1;

    l = 0;
    for(int p = i; p < child_count; ++p){
        subset[p] = new BPlusTree<T>;
        copy_tree(subset[p],ptr[l]);
        ++l;
    }
//    cout << "NMNM" << endl;
//    print_tree_two();
    l = 0;
    for(int k = i + 1; k < child_count; ++k){
        ptr[l]->clear_tree();
        delete ptr[l];
        ++l;
    }




}
template<typename T>
void BPlusTree<T>::case_two(int i){



    //cout << "case_two@@" << endl;
    // Part A
    // get data[i], put it in last position of subset[i]->data
    // Move all data positions over to the left
    // Add one to subset[i]->data_count

    T item = data[i];

    subset[i]->data[subset[i]->data_count] = item;
    subset[i]->data_count += 1;
//    cout << "pp" << endl;
//    subset[i]->print_tree_two();

//    for(int p = i + 1 ; p < data_count - 1; ++p){
//        data[p] = data[p + 1];
//        cout << "data["<<p<<"] = " << data[p] << endl;
//    }

//    data_count -= 1;

//    cout << "GGGGG" << endl;
//    print_tree_two();


    //Part B
    // transfer the first item of subset[i+1]->data up to the last data space
    // Subtract one from subset[i+1]->data_count
    // Move all subset[i+1[->data items to the left one space

    T plp = subset[i + 1]->data[0];
    //cout << "plp = " << plp << endl;

    data[i] = plp;

    //data_count += 1;

    for(int p = 0; p < subset[i + 1]->data_count - 1; ++p){
        subset[i + 1]->data[p] = subset[i + 1]->data[p + 1];
    }

    subset[i + 1]->data_count -= 1;

//    cout << "WEWEWE" << endl;
//    print_tree_two();

    //Part C
    // If subset[i + 1] has children, transfer the first child of subset[i+1]
    // over to the last child of subset[i]
    // Add one to subset[i]->child_count and subtract one from
    // subset[i+1]->child_count
    // Shift all other children in subset[i+1[ to the left one position

    if(subset[i + 1]->child_count > 0){
        subset[i]->subset[subset[i]->child_count] = new BPlusTree<T>;
        copy_tree(subset[i]->subset[subset[i]->child_count], subset[i + 1]->subset[0]);

        for(int p = 0; p < subset[i + 1]->child_count - 1; ++p){
            subset[i+1]->subset[p] = new BPlusTree<T>;
            copy_tree(subset[i + 1]->subset[p], subset[i + 1]->subset[p + 1]);
        }

        subset[i]->child_count += 1;

        subset[i + 1]->child_count -= 1;
    }

//    cout << "WEWE 55 " << endl;
//    print_tree_two();



}
template<typename T>
void BPlusTree<T>::case_one(int i){
    //cout << "Case ONE" << endl;
    //move subset[i]->data over to make room for data[i-1]
    //then put data[i-1] in subset[i]->data[0]
    //the add one to subset[i]->data_count
    T here;
    here = data[i -1];

    //cout << "PP" << endl;
    //subset[i]->print_tree_two();

    T sub[subset[i]->data_count];
    for(int p = 0; p < subset[i]->data_count ; ++p){
        sub[p] = subset[i]->data[p];
    }
    subset[i]->data[0] = here;
    for(int p = 0; p < subset[i]->data_count; ++p){
        subset[i]->data[p + 1] = sub[p];
    }
    subset[i]->data_count += 1;

    // Transfer the final item of subset[i - 1]->data up to replace
    // data[i-1] and subtract one from subset[i-1]->data_count
    T op;
    op = subset[i-1]->data[subset[i-1]->data_count - 1];
    data[i-1] = op;
    subset[i-1]->data_count -= 1;

    // If subset[i -1] has children, transfer the final child of subset[i-1]
    // over to the front of subset[i]
    // add one to subset[i]->child_count
    // subtract one from subset[i]->child_count
    if(subset[i -1]->child_count > 0){

        subset[i]->subset[subset[i]->child_count] = new BPlusTree<T>;
        for(int p = subset[i]->child_count; p > 0; --p){
            subset[i]->subset[p]->clear_tree();
            subset[i]->subset[p] = new BPlusTree<T>;
            copy_tree(subset[i]->subset[p],subset[i]->subset[p - 1]);
        }
        subset[i]->subset[0]->clear_tree();
        subset[i]->subset[0] = new BPlusTree<T>;
        copy_tree(subset[i]->subset[0], subset[i -1]->subset[subset[i-1]->child_count - 1]);

        subset[i]->child_count += 1;
        subset[i - 1]->subset[subset[i - 1]->child_count - 1]->clear_tree();
        subset[i - 1]->child_count -= 1;
    }


    return;


}
template<typename T>
void BPlusTree<T>::fix_shortage(int i){
    //if shortage is in subset[0]
    if(0 == i){
        //if subset[i+1]->data_count > MINIMUM, go to case_two(i)
        if(subset[i + 1]->data_count > MINIMUM){
            case_two(i);
            return;
        }
        //if subset[i + 1]->data_count <= MINIMUM, go to case_four(i)
        //cout << "HI" << endl;
        case_four(i);
        return;
    }

    //if shortage is in last child
    if(i == child_count - 1){
        //if subset[i-1]->data_count > MINIMUM, go to case_one(i)
        if(subset[i - 1]->data_count > MINIMUM){
            case_one(i);
            return;
        }
        //if subset[i - 1]->data_count <= MINIMUM, go to case_three(i)
        case_three(i);
        return;
    }

    //if shortage is in the middle of the first and the last child,
    //check case_two and case_one first, then case_four and case_three
    if(subset[i + 1]->data_count > MINIMUM && subset[i - 1]->data_count > MINIMUM){
        if(subset[i + 1]->data_count >= subset[i - 1]->data_count){
            case_two(i);
            return;
        }
        else if(subset[i + 1]->data_count < subset[i - 1]->data_count){
            case_one(i);
            return;
        }
    }
    if(subset[i + 1]->data_count > MINIMUM){
        //cout << "CASE TWO &&***" << endl;
        case_two(i);
        return;
    }
    if(subset[i - 1]->data_count > MINIMUM){
        case_one(i);
        return;
    }

    if(subset[i + 1]->data_count == MINIMUM){
        //cout << "CASE FOUR" << endl;
        case_four(i);
        return;
    }
    if(subset[i - 1]->data_count == MINIMUM){
        case_three(i);
    }
}
template<typename T>
void BPlusTree<T>::remove_biggest(T& removed_entry){

    //if no children, take last data item, set it to removed_entry,
    //and subtract one from data_count
    if(0 == child_count){
        removed_entry = data[data_count - 1];
        data_count -= 1;
    }

    //if there are children, call remove_biggest on the last child
    if(0 != child_count){
        subset[child_count - 1]->remove_biggest(removed_entry);
        //cout << "OPOP" << endl;
        //subset[child_count - 1]->print_tree_two();
        //check that there is not a shortage in subset[child_count - 1]
        if(subset[child_count - 1]->data_count < MINIMUM){
            fix_shortage(child_count - 1);
            return;
        }
    }
}
template<typename T>
void BPlusTree<T>::fix_erase_root(int i){
    //Fixes the root of tree if unbalanced

    if(0 == data_count){

        //make copy of subset[0]
        BPlusTree<T> *here;
        here = new BPlusTree<T>;
        copy_tree(here, subset[0]);

        //clear tree
        clear_tree();

        //set data equal to here data
        for(int p = 0; p < here->data_count; ++p){

            data[p] = here->data[p];
            data_count += 1;
        }

        // set children equal to here children
        for(int p = 0; p < here->child_count; ++p){
            subset[p] = new BPlusTree<T>;
            copy_tree(subset[p],here->subset[p]);
            child_count += 1;
        }

        //clear here
        here->clear_tree();
        delete here;
        here = NULL;
    }
}
template<typename T>
void BPlusTree<T>::loose_erase(const T& target){
    // check if root has no children
    if(0 == child_count){
        // Check if target is in root
        for(int i = 0; i < data_count; ++i){
            // if target is IN root and has no children     B
            if(target == data[i]){
                shift_data(i);
                return;
            }
        }
    }

    // check if root has children
    if(0 != child_count){
        // Check if target is in root
        for(int i = 0; i < data_count; ++i){

            // target is in root and has children     D
            if(target == data[i]){
                //remove biggest number in subset[i] and replace data[i] with that number
                subset[i]->remove_biggest(data[i]);
                //check if subset[i] needs to be balanced
                //cout << "KLKL*&*" << endl;
                //subset[i]->print_tree_two();
                if(subset[i]->data_count < MINIMUM){
                    fix_shortage(i);
                }
                //cout << "KLKL 2" << endl;
                //subset[i]->print_tree_two();
                return;
            }
        }
        // target is not in root and has children     C

        // target is less than first data entry, call loose_erase for subset[0]
        if(target < data[0]){
            subset[0]->loose_erase(target);

            //check if subset[0] needs to be balanced
//            cout << "TATA" << endl;
//            print_tree_two();
            if(subset[0]->data_count < MINIMUM){
                fix_shortage(0);
            }
            return;
        }

        //target is greater than last data entry, call loose_erase for correct subset[child_count - 1]
        if(target >= data[data_count - 1]){
            int cc = child_count - 1;
            subset[child_count - 1]->loose_erase(target);
            //check if subset[cc] needs to be balanced
            if(subset[cc]->data_count < MINIMUM){
                fix_shortage(cc);
            }
            return;
        }

        //target is in the middle of first and last data items, call
        // loose_erase for data[j + 1]
        int j = 0;
        bool stop = false;
        do{
            if(!(target >= data[j] && target <= data[j + 1])){
                ++j;
            }
            else if(target >= data[j] && target <= data[j + 1]){
                subset[j + 1]->loose_erase(target);
                //check if subset[j + 1] needs to be balanced
                if(subset[j + 1]->data_count < MINIMUM){
                    fix_shortage(j + 1);
                }
                stop = true;
                return;
            }
        }while(stop == false);
    }
}
template<typename T>
void BPlusTree<T>::erase(const T& target){
    // check if root has no children
    if(0 == child_count){
        // Check if target is in root
        for(int i = 0; i < data_count; ++i){
            // if target is IN root and has no children     B
            if(target == data[i]){
                shift_data(i);
                return;
            }
        }
    }

    // check if root has children
    if(0 != child_count){
        // Check if target is in root
        for(int i = 0; i < data_count; ++i){

            // target is in root and has children     D
            if(target == data[i]){
                //remove biggest number in subset[i] and replace data[i] with that number
                subset[i]->remove_biggest(data[i]);
//                cout << "***" << endl;
//                subset[i]->print_tree_two();
//                cout << "2*****" << endl;
//                print_tree_two();
                //check if subset[i] needs to be balanced
                if(subset[i]->data_count < MINIMUM){
                    fix_shortage(i);
                }
                //check if root needs to be balanced
                fix_erase_root(0);
                return;
            }
        }
        // target is not in root and has children     C

        // target is less than first data entry, call loose_erase for subset[0]
        if(target < data[0]){
            subset[0]->loose_erase(target);
            //check if subset[0] needs to be balanced
            if(subset[0]->data_count < MINIMUM){
                fix_shortage(0);
            }
            //check is root needs to be balanced
            fix_erase_root(0);
            return;
        }

        //target is greater than last data entry, call loose_erase for correct subset[child_count - 1]
        if(target >= data[data_count - 1]){
            int cc = child_count - 1;
            subset[child_count - 1]->loose_erase(target);
            //check if subset[cc] needs to be balanced
            if(subset[cc]->data_count < MINIMUM){
                fix_shortage(cc);
            }
            //check is root needs to be balanced
            fix_erase_root(0);
            return;
        }

        //target is in the middle of first and last data items, call
        // loose_erase for data[j + 1]
        int j = 0;
        bool stop = false;
        do{
            //cout << "HIII" << endl;
            if(!(target >= data[j] && target <= data[j + 1])){
                ++j;
            }
            else if(target >= data[j] && target <= data[j + 1]){
                //cout << "()()" << endl;
                //subset[j+1]->print_tree_two();
                subset[j + 1]->loose_erase(target);
//                cout << "()()2" << endl;
//                subset[j+1]->print_tree_two();
                //check if subset[j + 1] needs to be balanced
                if(subset[j + 1]->data_count < MINIMUM){
                    fix_shortage(j + 1);
                }
//                cout << "()()3" << endl;
//                subset[j+1]->print_tree_two();
                //check is root needs to be balanced
                fix_erase_root(0);
                stop = true;
                return;
            }
        }while(stop == false);
    }
}




//ALL FUCTIONS FOR INSERT AND EVERYTHING ELSE BELOW
template<typename T>
bool BPlusTree<T>::check_Dups(const T& item)const{
    // if no items in data array, there can not be duplicates
    if(0 == data_count){
        return false;
    }

    //if there are items in the data array
    // search the data array for a match, if found, return true
    for(int i = 0; i < data_count; ++i){
        if(item == data[i]){
            return true;
        }
        // if the last item in the data array does not match, return false
        if(i == data_count - 1){
            if(item != data[i]){
                return false;
            }
        }
    }
}
template<typename T>
void BPlusTree<T>::insert(const T& item){
    // if there are no children, insert here
    if(0 == child_count){
        //check if a duplicate
        if(dups_ok == false){
            if(check_Dups(item) == true){
                return;
            }
        }
        //enter data and see if the root needs fixing
        enter_Data(item);
        fix_excess_root(0);
        return;
    }

    //if there are children
    if(0 != child_count){
        // check for duplicates
        if(dups_ok == false){
            if(check_Dups(item) == true){
                return;
            }
        }
        //if item is less than first position in data array.
        //recursively call the insert_item function for the correct subset[0].
        //check if tree needs to be balanced
        if(item <= data[0]){
            insert_item(item,subset[0]);
            fix_excess(0);
            fix_excess_root(0);
            return;
        }

        //if item is bigger than the last child in the array
        //recursively call the insert_item function for subset[cc - 1].
        //check if tree needs to be balanced
        if(item >= data[data_count - 1]){
            int cc = child_count;
            insert_item(item,subset[cc - 1]);
            fix_excess(cc - 1);
            fix_excess_root(0);
            return;
        }

        //if item is inbetween first and last position in data array
        //recursively call the insert_item function for subset[i+1].
        //check if tree needs to be balanced
        int i = 0;
        bool stop = false;
        do{
            if(!(item >= data[i] && item <= data[i + 1])){
                ++i;
            }
            else if(item >= data[i] && item <= data[i + 1]){
                insert_item(item,subset[i + 1]);
                fix_excess(i + 1);
                //print_tree_two();
                fix_excess_root(0);
                stop = true;
            }

        }while(stop == false);
    }
}
template<typename T>
void BPlusTree<T>::insert_item(const T item, BPlusTree<T> *ptr){

    //if there are no children, insert here
    if(0 == ptr->child_count){
        // check for duplicates
        if(dups_ok == false){
            if(ptr->check_Dups(item) == true){
                return;
            }
        }
        //enter item
        ptr->enter_Data(item);
        return;
    }

    //if there are children
    if(0 != ptr->child_count){
        //check for duplicates
        if(dups_ok == false){
            if(ptr->check_Dups(item) == true){
                return;
            }
        }

        //if item is less than first position in data array.
        //recursively call the insert_item function for the correct subset[0].
        //check if tree needs to be balanced
        if(item <= ptr->data[0]){

            ptr->insert_item(item,ptr->subset[0]);
            ptr->fix_excess(0);
            return;
        }

        //if item is bigger than the last child in the array
        //recursively call the insert_item function for subset[cc - 1].
        //check if tree needs to be balanced
        if(item >= ptr->data[ptr->data_count - 1]){
            ptr->insert_item(item,ptr->subset[ptr->child_count - 1]);
            int cc = ptr->child_count;
            ptr->fix_excess(ptr->child_count - 1);
            return;
        }

        //if item is inbetween first and last position in data array
        //recursively call the insert_item function for subset[i+1].
        //check if tree needs to be balanced
        int i = 0;
        bool stop = false;
        do{
            if(!(item >= ptr->data[i] && item <= ptr->data[i + 1])){
                ++i;
            }
            else if(item >= ptr->data[i] && item <= ptr->data[i + 1]){
                 ptr->insert_item(item,ptr->subset[i + 1]);
                ptr->fix_excess(i + 1);
                stop = true;
            }

        }while(stop == false);
    }
}
template<typename T>
void BPlusTree<T>::split_Node(int i){
    if(subset[i]->subset[0] == NULL){
        int scc = subset[i]->child_count;

        //Make copy of subset[i]'s children, first half, then second half
        int y = subset[i]->child_count / 2;
        BPlusTree<T> *iop[subset[i]->child_count / 2], *iop2[subset[i]->child_count / 2];
        for(int p = 0; p < subset[i]->child_count / 2; ++p){
//            iop[p] = new BPlusTree<T>;
//            copy_tree(iop[p],subset[i]->subset[p]);
            iop[p] = subset[i]->subset[p];
        }
        int s = 0;
        for(int p = subset[i]->child_count / 2; p < subset[i]->child_count ; ++p){
//            iop2[s] = new BPlusTree<T>;
//            copy_tree(iop2[s],subset[i]->subset[p]);
            iop2[s] = subset[i]->subset[p];
            ++s;
        }

        //Take middle number of subset[i]->data_count and move into data array
        int num;
        num = subset[i]->data_count / 2;

        enter_Data(subset[i]->data[num]);

        //Set child_count to two
        child_count = 2;

        //Copy first half and second half of subset[i]_data
        T here[MINIMUM], here2[MINIMUM + 1];
        for(int j = 0; j < num; ++j){
            here[j] = subset[i]->data[j];
        }
        int p = 0;
        for(int j = num ; j < MAXIMUM + 1; ++j){
            here2[p] = subset[i]->data[j];
            //cout << "here2[" << p << "] = " << here2[p] << endl;
            ++p;
        }

        //Clear subset[i], create new, enter first half of old subset[i] data
//        subset[i]->clear_tree();
        subset[i] = new BPlusTree<T>;
        //subset[i]->data_count = 0;
        for(int p = 0; p < MINIMUM; ++p){
            subset[i]->enter_Data(here[p]);
        }
        //Create subset[i+1], enter second half of old subset[i] data
        subset[i + 1] = new BPlusTree<T>;
        //subset[i+1]->data_count = 0;
        for(int p = 0; p < MINIMUM + 1; ++p){
            subset[i + 1]->enter_Data(here2[p]);
            //cout << "subset[i+1]->data[" <<p << "] = " << subset[i + 1]->data[p] << endl;
        }

        //subset[i]->child_count = 0;
        //Copy first half of old subset[i] children
        for(int p = 0; p < scc / 2; ++p){
//            subset[i]->subset[p] = new BPlusTree<T>;
//            copy_tree(subset[i]->subset[p],iop[p]);
            subset[i]->child_count += 1;
            subset[i]->subset[p] = iop[p];
        }
        //NEW maybe
//        for(int p = 0; p < scc /2 - 1 ; ++p){
//            BPlusTree<T> *ptr, ptr2;
//            ptr = subset[i]->subset[p];
//            ptr2 = subset[i]->subset[p+1];
//        }
        //subset[i+1]->child_count = 0;
        //Copy second half of old subset[i] children
        for(int p = 0; p < scc / 2; ++p){
//            subset[i + 1]->subset[p] = new BPlusTree<T>;
//            copy_tree(subset[i + 1]->subset[p],iop2[p]);
            subset[i + 1]->child_count += 1;
            subset[i+1]->subset[p] = iop2[p];
        }
        subset[i]->next = subset[i+1];
//        BPlusTree<T> *lp, *pl;
//        lp = subset[i];
//        pl = subset[i+1];
//        connect(lp,pl);

//        subset[i]->next = subset[i+1];
//        subset[i+1]->previous = subset[i];


//        for(int p = 0; p < y; ++p){
//            iop[p]->clear_tree();
//            delete iop[p];
//            iop2[p]->clear_tree();
//            delete iop2[p];
//        }
    //    cout << "PPPP" << endl;
    //    print_tree();
        return;


    }


    int scc = subset[i]->child_count;

    //Make copy of subset[i]'s children, first half, then second half
    int y = subset[i]->child_count / 2;
    BPlusTree<T> *iop[subset[i]->child_count / 2], *iop2[subset[i]->child_count / 2];
    for(int p = 0; p < subset[i]->child_count / 2; ++p){
//        iop[p] = new BPlusTree<T>;
//        copy_tree(iop[p],subset[i]->subset[p]);
        iop[p] = subset[i]->subset[p];
    }
    int s = 0;
    for(int p = subset[i]->child_count / 2; p < subset[i]->child_count ; ++p){
//        iop2[s] = new BPlusTree<T>;
//        copy_tree(iop2[s],subset[i]->subset[p]);
        iop2[s] = subset[i]->subset[p];
        ++s;
    }

    //Take middle number of subset[i]->data_count and move into data array
    int num;
    num = subset[i]->data_count / 2;

    enter_Data(subset[i]->data[num]);

    //Set child_count to two
    child_count = 2;

    //Copy first half and second half of subset[i]_data
    T here[MINIMUM], here2[MINIMUM];
    for(int j = 0; j < num; ++j){
        here[j] = subset[i]->data[j];
        //cout << "here[" << j << "] = " << here[j] << endl;
    }
    int p = 0;
    for(int j = num + 1; j < MAXIMUM + 1; ++j){
        here2[p] = subset[i]->data[j];
        //cout << "here2[" << p << "] = " << here2[p] << endl;
        ++p;
    }

    //Clear subset[i], create new, enter first half of old subset[i] data
    //subset[i]->clear_tree();
    subset[i] = new BPlusTree<T>;
    for(int p = 0; p < MINIMUM; ++p){
        subset[i]->enter_Data(here[p]);
    }
    //Create subset[i+1], enter second half of old subset[i] data
    subset[i + 1] = new BPlusTree<T>;
    for(int p = 0; p < MINIMUM; ++p){
        subset[i + 1]->enter_Data(here2[p]);
        //cout << "subset[i+1]->data[" <<p << "] = " << subset[i + 1]->data[p] << endl;
    }

    //Copy first half of old subset[i] children
    for(int p = 0; p < scc / 2; ++p){
//        subset[i]->subset[p] = new BPlusTree<T>;
//        copy_tree(subset[i]->subset[p],iop[p]);
        subset[i]->child_count += 1;
        subset[i]->subset[p] = iop[p];
    }

    //Copy second half of old subset[i] children
    for(int p = 0; p < scc / 2; ++p){
//        subset[i + 1]->subset[p] = new BPlusTree<T>;
//        copy_tree(subset[i + 1]->subset[p],iop2[p]);
        subset[i + 1]->child_count += 1;
        subset[i + 1]->subset[p] = iop2[p];
    }

//    for(int p = 0; p < y; ++p){
//        iop[p]->clear_tree();
//        delete iop[p];
//        iop2[p]->clear_tree();
//        delete iop2[p];
//    }
//    cout << "PPPP" << endl;
//    print_tree();
}
template<typename T>
void BPlusTree<T>:: fix_excess_root(int i){

    if(0 == i){
        //If data_count of root is over MAXIMUM
        if(MAXIMUM + 1 == data_count){
            //If child count is also one over the MAXIMUM
            if( MAXIMUM + 2 == child_count){
                //Make a copy of the whole tree
                BPlusTree<T> *here;
                here = new BPlusTree<T>;
                here->child_count = child_count;
                for(int i = 0; i < data_count; ++i){
                    here->enter_Data(data[i]);
                }
                int l = 0;
                for(int p = 0; p < here->child_count; ++p){
                    //here->subset[p] = new BPlusTree<T>;
                    here->subset[p] = subset[p];
                }
                //here->subset[p] = subset[p]
                //Clear the tree, then make one child that is a copy of
                //previous tree. Set child_count to one
                //clear_tree();
                data_count = 0;
                subset[0] = here;
                //subset[0] = here;
                child_count = 1;
                //here->clear_tree();
                //delete here;
                //Recursive call to fix_excess_root, will go to 1 == child_count
//                cout << "inside" << endl;
//                subset[0]->print_tree_two();
//                cout << subset[0]->subset[0]->data[0] << "  " << endl;
//                cout << subset[0]->subset[0]->next->data[0] << "  " << endl;
//                cout << subset[0]->subset[0]->next->next->data[0] << "  " << endl;
//                cout << subset[0]->subset[0]->next->next->next->data[0] << "  " << endl;
                fix_excess_root(0);

            }

            //If root needs to be fixed and has no children
            if(subset[i] == NULL ){
                if(MAXIMUM + 1 == data_count){
                    //Make a copy of the whole tree
                    BPlusTree<T> *here;
                    here = new BPlusTree<T>;
                    here->child_count = child_count;
                    for(int i = 0; i < data_count; ++i){
                        here->enter_Data(data[i]);
                    }
                    int l = 0;
                    for(int p = 0; p < here->child_count; ++p){
                        //here->subset[p] = new BPlusTree<T>;
                        // copy_tree(here->subset[p],subset[p]);
                        here->subset[p] = subset[p];
                    }
                    //NEW maybe delete
//                    for(int p = 0; p < here->child_count; ++p){
//                        BPlusTree<T> *pl, *lp;
//                        if(0 == here->subset[p]->child_count){
//                            pl = here->subset;
//                        }
//                        else if(0 != here->subset[p]->child_count){
//                            pl = here->get_largest
//                        }
//                    }
                    //Clear the tree, then make one child that is a copy of
                    //previous tree. Set child_count to one
                    //clear_tree();
                    //subset[0] = new BPlusTree<T>;
                    //copy_tree(subset[0],here);
                    subset[0] = here;
                    child_count = 1;
                    data_count = 0;
                    //here->clear_tree();
                    //delete here;
                    //Recursive call to fix_excess_root, will go to 1 == child_count
//                    cout << "Inside 2" << endl;
//                    subset[0]->print_tree_two();
                    fix_excess_root(0);

                    return;
                }
            }
        }
        if(1 == child_count){
            split_Node(i);
            return;
        }
    }
}
template<typename T>
void BPlusTree<T>::fix_excess(int i){
    //do nothing if sunset[i]->data_count is not over MAXIMUM
    if(subset[i]->data_count != MAXIMUM + 1){
        return;
    }

    //if subset[i}_data_count is over MAXIMUM
    //int num is the index that seperates the data array
    //T item is the item that holds the subset[i]->data item
    //that will be transfered to data array
    int num;
    num = (subset[i]->data_count) / 2;
    T item;
    item = subset[i]->data[num];
    enter_Data(item);


    if(0 == i && 0 == subset[i]->child_count){

        subset[child_count] = new BPlusTree<T>;
        BPlusTree<T> *hold;
        hold = subset[child_count - 1]->next;

        for(int p = child_count; p > i + 1; --p){
            subset[p]->data_count = 0;
            for(int j = subset[p - 1]->data_count - 1; j >= 0; --j){
                subset[p]->enter_Data(subset[p-1]->data[j]);
            }
        }
        T gub2[num + 1];
        int l = 0;
        for(int j = num; j <= num * 2 ; ++j){
            gub2[l] = subset[i]->data[j];
            ++l;
        }
        subset[i+1]->data_count = 0;
        for(int j = 0; j < l; ++j){
            subset[i+1]->enter_Data(gub2[j]);

        }
        subset[i]->data_count = num;

        subset[child_count - 1]->next = subset[child_count];
        subset[child_count]->next = hold;
        child_count += 1;


        return;


    }



    //if subset that needs to be fixed is subset[0], the first child ******
    if(0 == i){

        subset[child_count] = new BPlusTree<T>;

        for(int p = child_count; p > i + 1; --p){
            subset[p]->data_count = 0;
            subset[p]->child_count = 0;
            for(int j = subset[p - 1]->data_count - 1; j >= 0; --j){
                subset[p]->enter_Data(subset[p-1]->data[j]);
            }
            for(int j = subset[p-1]->child_count - 1; j >= 0; --j){
                subset[p]->subset[j] = subset[p-1]->subset[j];
                subset[p]->child_count += 1;
            }
        }

        T gub2[num];
        int u = subset[i]->child_count / 2;
        int y = subset[i]->child_count / 2 - 1;
        int l = 0;
        for(int j = num + 1; j <= num * 2 ; ++j){
            gub2[l] = subset[i]->data[j];
            ++l;
        }
        subset[i+1]->data_count = 0;
        for(int j = 0; j < l; ++j){
            subset[i+1]->enter_Data(gub2[j]);

        }
        subset[i]->data_count = num;
        subset[i+1]->child_count = 0;
        for(int j = subset[i]->child_count - 1; j >= subset[i]->child_count / 2; --j){
            subset[i+1]->subset[y] = subset[i]->subset[j];
            subset[i+1]->child_count += 1;
            --y;
        }
        for(int j = subset[i]->child_count / 2; j < subset[i]->child_count; ++j){
            subset[i]->subset[j] = NULL;
        }
        subset[i]->child_count = u;



        child_count += 1;
        return;
    }



    if(i == child_count - 1 && 0 == subset[i]->child_count){

        subset[child_count] = new BPlusTree<T>;
        BPlusTree<T> *hold;
        hold = subset[child_count - 1]->next;

        T gub2[num + 1];
        int l = 0;
        for(int j = num; j <= num * 2 ; ++j){
            gub2[l] = subset[child_count - 1]->data[j];
            ++l;
        }
        subset[child_count]->data_count = 0;
        for(int j = 0; j < l; ++j){
            subset[i+1]->enter_Data(gub2[j]);

        }

        subset[child_count - 1]->data_count = num;

        subset[child_count - 1]->next = subset[child_count];
        subset[child_count]->next = hold;
        child_count += 1;

        return;

    }


    if(i == child_count - 1)
    {

        subset[child_count] = new BPlusTree<T>;
        int y = subset[child_count - 1]->child_count;
        int uu = subset[child_count - 1]->child_count / 2;
        int u = subset[child_count - 1]->child_count / 2 - 1;

        T gub2[num];
        int l = 0;
        for(int j = num+1; j <= num * 2 ; ++j){
            gub2[l] = subset[child_count - 1]->data[j];
            ++l;
        }
        subset[child_count]->data_count = 0;
        for(int j = 0; j < l; ++j){
            subset[i+1]->enter_Data(gub2[j]);
        }
        subset[i+1]->child_count = 0;
        for(int j = subset[i]->child_count - 1; j >= subset[i]->child_count / 2; --j){
            subset[i+1]->subset[u] = subset[i]->subset[j];
            subset[i+1]->child_count += 1;
            --u;
        }

        for(int j = subset[i]->child_count / 2; j < subset[i]->child_count; ++j){
            subset[i]->subset[j] = NULL;
        }

        subset[child_count - 1]->data_count = num;
        subset[child_count - 1]->child_count =  uu;

        child_count += 1;
        return;

    }


    if(0 != i && i != child_count - 1 && 0 == subset[i]->child_count){
        // if subset[i] is in between first and last child *********

        subset[child_count] = new BPlusTree<T>;
        BPlusTree<T> *hold;
        hold = subset[child_count - 1]->next;

        for(int p = child_count; p > i + 1; --p){
            subset[p]->data_count = 0;
            for(int j = subset[p - 1]->data_count - 1; j >= 0; --j){
                subset[p]->enter_Data(subset[p-1]->data[j]);
            }
        }
        T gub2[num+1];
        int u = subset[i]->child_count / 2;
        int y = subset[i]->child_count / 2 - 1;
        int l = 0;
        for(int j = num; j <= num * 2 ; ++j){
            gub2[l] = subset[i]->data[j];
            ++l;
        }
        subset[i+1]->data_count = 0;
        for(int j = 0; j < l; ++j){
            subset[i+1]->enter_Data(gub2[j]);

        }
        subset[i]->data_count = num;

        subset[child_count - 1]->next = subset[child_count];
        subset[child_count]->next = hold;

        child_count += 1;

        return;
    }


    if(0 != i && i != child_count - 1 && 0 != subset[i]->child_count){

        subset[child_count] = new BPlusTree<T>;

        for(int p = child_count; p > i + 1; --p){
            subset[p]->data_count = 0;
            subset[p]->child_count = 0;
            for(int j = subset[p - 1]->data_count - 1; j >= 0; --j){
                subset[p]->enter_Data(subset[p-1]->data[j]);
            }
            for(int j = subset[p-1]->child_count - 1; j >= 0; --j){
                subset[p]->subset[j] = subset[p-1]->subset[j];
                subset[p]->child_count += 1;
            }
        }
        T gub2[num];
        int u = subset[i]->child_count / 2;
        int y = subset[i]->child_count / 2 - 1;
        int l = 0;
        for(int j = num + 1; j <= num * 2 ; ++j){
            gub2[l] = subset[i]->data[j];
            ++l;
        }
        subset[i+1]->data_count = 0;
        for(int j = 0; j < l; ++j){
            subset[i+1]->enter_Data(gub2[j]);

        }
        subset[i]->data_count = num;
        subset[i+1]->child_count = 0;
        for(int j = subset[i]->child_count - 1; j >= subset[i]->child_count / 2; --j){
            subset[i+1]->subset[y] = subset[i]->subset[j];
            subset[i+1]->child_count += 1;
            --y;
        }
        for(int j = subset[i]->child_count / 2; j < subset[i]->child_count; ++j){
            subset[i]->subset[j] = NULL;
        }
        subset[i]->child_count = u;



        child_count += 1;


    }

}
template<typename T>
void BPlusTree<T>::enter_Data(T item){
    // if no data in array, enter here,  add one to data_count
    if(0 == data_count){

        data[0] = item;
        data_count += 1;
        return;
    }

    //If there is data in the array
    if(0 != data_count){
        //if item is less that first position in data array enter here
        if(item <= data[0]){
            T sub[data_count + 1];
            sub[0] = item;
            for(int i = 1; i < data_count + 1; ++i){
                sub[i] = data[i - 1];
            }
            for(int i = 0; i < data_count; ++i){
                data[i] = T();
            }
            data_count += 1;
            for(int i = 0; i < data_count; ++i){
                data[i] = sub[i];
                //cout << "data[" << i << "] = " << data[i] << endl;
            }
            return;
        }

        //if item is greater than last position in data array, add data here
        if(item >= data[data_count - 1]){
            data_count += 1;
            data[data_count - 1] = item;
            return;
        }

        //if item is inbetween first and last position in the data array
        int i = 0;
        bool stop = false;
        do{
            if(!(item >= data[i] && item <= data[i + 1])){
                ++i;
            }
            else if(item >= data[i] && item <= data[i + 1]){

                T sub[data_count + 1];
                for(int p = 0; p <= i; ++p){
                    sub[p] = data[p];
                }
                sub[i + 1] = item;
                data_count += 1;
                for(int j = i + 2; j < data_count; ++j){
                    sub[j] = data[j - 1];
                }
                for(int l = 0; l < data_count; ++l){
                    data[l] = T();
                }
                for(int l = 0; l < data_count; ++l){
                    data[l] = sub[l];
                }

                stop = true;
            }
        } while (stop == false);
    }
}
template<typename T>
void BPlusTree<T>::copy_tree(BPlusTree<T>* left,const BPlusTree<T>* right){

    left->child_count = right->child_count;
    for(int i = 0; i < right->data_count; ++i){
        left->enter_Data(right->data[i]);
    }
    //Copy children
    if(0 != right->child_count){
        for(int i = 0; i < right->child_count; ++i){
            left->subset[i] = new BPlusTree<T>;
            copy_tree(left->subset[i],right->subset[i]);
        }
    }

}
template<typename T>
void BPlusTree<T>::copy_tree_2(BPlusTree<T>* left, const BPlusTree<T> * right){
    //Set child_count, copy data
    left->child_count = right->child_count;
    for(int i = 0; i < right->data_count; ++i){
        left->enter_Data(right->data[i]);
    }

    if(0 != right->child_count){
        //cout << "RCH = " << right->child_count << endl;
        for(int i = right->child_count - 1; i >= 0; --i){
            left->subset[i] = new BPlusTree<T>;
            copy_tree_2(left->subset[i],right->subset[i]);
            if(0 == right->subset[i]->child_count && i != right->child_count - 1){
                left->subset[i]->next = left->subset[i+1];
                //cout << "left->subset["<<i<<"]= "<< left->subset[i]->next->data[0] << endl;
            }
//            if(i != right->child_count - 1){
//                BPlusTree<T> *front, *back;
//                if(0 == subset[i]->child_count){
//                    front = subset[i];
//                }
//                else if(0 != subset[i]->child_count){
//                    front = subset[i]->get_largest();
//                }
//                if(0 == subset[i+1]->child_count){
//                    back = subset[i+1];
//                }
//                else if(0 != subset[i+1]->child_count){
//                    back = subset[i+1]->get_smallest_node();
//                }
//                front->next = back;
//            }
        }
        return;
    }
}
template<typename T>
void BPlusTree<T>::copy_tree3(BPlusTree<T>* left,const BPlusTree<T>* right, LinkedList &test){

    left->child_count = right->child_count;
    for(int i = 0; i < right->data_count; ++i){
        left->enter_Data(right->data[i]);
    }
    //Copy children
    if(0 != right->child_count){
        for(int i = 0; i < right->child_count; ++i){
            left->subset[i] = new BPlusTree<T>;
            copy_tree3(left->subset[i],right->subset[i], test);
            if(0 == left->subset[i]->child_count){
                test.insert(left->subset[i]);
            }
        }
    }
}
template<typename T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& rhs):data_count(0), child_count(0),next(NULL){

    LinkedList  test;

    child_count = rhs.child_count;
    for(int i = 0; i < rhs.data_count; ++i){
        enter_Data(rhs.data[i]);
    }
    if(0 != rhs.child_count){
        for(int i = 0; i < rhs.child_count; ++i){
            subset[i] = new BPlusTree<T>;
            copy_tree3(subset[i],rhs.subset[i], test);
        }
    }

    test.head_ptr = NULL;
    test.move_ptr = NULL;

//    cout << "HERE IT COMES" << endl;
//    while(test.head_ptr != NULL){
//        for(int p = 0; p < test.head_ptr->data_count; ++p){
//            cout << test.head_ptr->data[p] << " * ";
//        }

//        test.head_ptr = test.head_ptr->next;
//    }
}
template<typename T>
BPlusTree<T>& BPlusTree<T>::operator =(const BPlusTree<T>& rhs){

    LinkedList  test;

    child_count = rhs.child_count;
    for(int i = 0; i < rhs.data_count; ++i){
        enter_Data(rhs.data[i]);
    }
    if(0 != rhs.child_count){
        for(int i = 0; i < rhs.child_count; ++i){
            subset[i] = new BPlusTree<T>;
            copy_tree3(subset[i],rhs.subset[i], test);
        }
    }
    test.head_ptr = NULL;
    test.move_ptr = NULL;
}
template<typename T>
BPlusTree<T>::BPlusTree(bool dups){
    //Constructor
    data_count = 0;
    child_count = 0;
    next = NULL;
    for(int i = 0; i < MAXIMUM + 2; ++i){
        subset[i] = NULL;
    }
    dups_ok = dups;
}
template<typename T>
BPlusTree<T>::~BPlusTree(){
    if(0 == child_count){
        return;
    }
    //Deconstructor
    cout << "~BPlusTree" << endl;
    clear_tree();
}
template<typename T>
void BPlusTree<T>::print_tree_two(int level, ostream& outs) const{
    //Print Tree from book
    const int EXTRA_INDENTATION = 4;
    size_t i;
    outs << setw(level) << "";

    for(i = 0;i < data_count; ++i){
        outs << data[i] << " " ;
    }
    outs << endl;

    for(i = 0; i < child_count; ++i){
        subset[i]->print_tree_two(level + EXTRA_INDENTATION);
    }
}
template<typename T>
void BPlusTree<T>::print_tree(int level, ostream& outs) const{

    // Print Tree
    int last_child = child_count - 1;
    if(child_count > 0){
        subset[last_child]->print_tree(level + 1);
    }
    int j = last_child - 1;
    for(int i = data_count - 1; i >= 0; --i){
        outs << setw(level*8) << data[i];
        if(child_count > 2){
            if(subset[j]->data_count - 1 >= i){
                outs << setw((level + 1)*6) << subset[j]->data[i];
            }
        }
        outs << endl;
        if(0 == i && child_count > 0){
            cout << endl;
            subset[0]->print_tree(level + 1);
        }
    }
    cout << endl;
}
template<typename T>
ostream& operator <<(ostream& outs, const BPlusTree<T>& print_me) {
    //print_me.print_tree();
//    outs << endl;
//    outs << "****************************************************" << endl;
//    outs << endl;
    print_me.print_tree_two();
    return outs;
}
template<typename T>
void BPlusTree<T>::clear_tree(){
    //Clear Tree
    for(int i = 0; i < data_count; ++i){
        data[i] = T();
    }
    data_count = 0;
    for(int i = 0; i < child_count; ++i){
        subset[i]->clear_tree();
        delete  subset[i];
        subset[i] = NULL;
    }
    next = NULL;
    child_count = 0;
}
#endif // BPLUSTREE_H

