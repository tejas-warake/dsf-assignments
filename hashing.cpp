#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
using namespace std;
typedef struct table
{
    int data, chain;
} tb;
class linear_prob
{
    int n, pos, v;

public:
    tb val[];
    linear_prob()
    {
        n = 0;
        pos = 0;
        cout << "Enter the number of student :";
        cin >> n;
        val[n];
    }
    void create_without_replacement();
    void search_without_replacement(int);
    void create_with_replacement();
    void search_with_replacement(int);
    void display();
};
void linear_prob::create_without_replacement()
{
    for (int i = 0; i < n; i++)
    {
        val[i].data = -1;
        val[i].chain = -1;
    }
    for (int i = 0; i < n; i++)
    {
        int prev, j;
        cout << "Enter student " << i + 1 << " Roll no. : ";
        cin >> v;
        pos = v % n;
        if (val[pos].data == -1) // for actual position is emptty
        {
            val[pos].data = v;
        }
        else // if actual position is not empty
        {
            prev = pos;
            while (val[pos].data != -1) // to finding next empty location
            {
                pos = (pos + 1) % n;
            }
            j = prev;
            while ((prev != val[j].data % n) && (val[j].chain != -1)) // for key's
                // first synonyms is not equal to there actual position then this loop
                //     helps to finding first synonyms that missing there actual location.
                {
                    j = (j + 1) % n;
                }
            prev = j;
            while (val[prev].chain != -1) // from first synonyms to last
                // synonyms chain for updating last chain value with new key positin
                {
                    prev = val[prev].chain;
                }
            val[pos].data = v;                           // insert key at empty location
            if (val[pos].data % n == val[prev].data % n) // key val mod is
                // equal to prev loction then link each other
                {
                    val[prev].chain = pos;
                }
        }
    }
}
void linear_prob::search_without_replacement(int key)
{
    int p, flag = 0;
    p = key % n;
    if (val[p].data == key) // direct found at first location
    {
        flag = 1;
    }
    else if (val[p].data % n == p)
    {
        while (val[p].chain != -1) // finding key in chain of actual
        {
            if (val[p].data == key)
            {
                flag = 1;
                break;
            }
            p = val[p].chain;
        }
        if (val[p].data == key) // for cheaking for last val of synonyms is
            // equal to key
            {
                flag = 1;
            }
    }
    else
    {
        while (p != (p - 1) % n) // find all loction from synonyms +1 to
                                 // synonyms when exact location accupied by non synonyms
        {
            p = (p + 1) % n;
            if (val[p].data == key)
            {
                flag = 1;
                break;
            }
        }
    }
    if (flag == 0)
    {
        cout << "\nRoll no. " << key << " does not found in hash table ";
    }
    else
    {
        cout << "\nRoll no. found at " << p << " location ";
    }
}
void linear_prob::create_with_replacement()
{
    for (int i = 0; i < n; i++)
    {
        val[i].data = -1;
        val[i].chain = -1;
    }
    for (int i = 0; i < n; i++)
    {
        int prev, temp, p;
        cout << "Enter student " << i + 1 << " Roll no. : ";
        cin >> v;
        pos = v % n;
        if (val[pos].data == -1) // for actual position is empty
        {
            val[pos].data = v;
        }
        else // if actual position is not emptty
        {
            prev = pos;
            while (val[pos].data != -1) // to fining next empty
            {
                pos = (pos + 1) % n;
            }
            if (val[prev].data % n == v % n) // synonyms of key present at
                                             // that location
            {
                while (val[prev].chain != -1) // from first synonyms to last
                                              // synonyms chain for updating last chain value with new key positin
                {
                    prev = val[prev].chain;
                }
                val[pos].data = v;
                val[prev].chain = pos;
            }
            else // synonyms of key is not present at that location
            {
                int x = val[prev].data % n;                                   // first synonyms of present location
                // that is not synonyms of actual key 
                while (val[x].chain != -1) // for disjoint abstracal and join
                    // (abstract - 1)
                    //     ->(abstract + 1)
                {
                    p = x; // for maintaining previous value of chain
                    x = val[x].chain;
                    if ((val[x].chain != -1) && (val[x].data == val[prev].data))
                    {
                        val[p].chain = val[x].chain;
                    }
                    else if ((val[x].chain == -1) && (val[x].data == val[prev].data))
                    {
                        val[p].chain = -1;
                    }
                }
                int y = val[prev].data % n;                                   // first synonyms of present location
                // that is not synonyms of actual key 
                while (val[y].chain != -1) // from first synonyms of absract to last
                    // and add abstract at last
                {
                    y = val[y].chain;
                }
                val[pos].data = val[prev].data; // adding replaced value at last of
                // there chaining(at next empty location)
                    
                val[y].chain = pos;
                val[prev].data = v; // replace and adding key at there home locatin
                val[prev].chain = -1;
            }
        }
    }
}
void linear_prob::search_with_replacement(int key)
{
    int flag = 0;
    int pos = key % n;
    if (val[pos].data == key) // when key at home location
    {
        cout << "Roll no. " << key << " found at location " << pos << endl;
        flag++;
    }
    else // when key at in chaining
    {
        while (val[pos].chain != -1)
        {
            pos = val[pos].chain;
            if (val[pos].data == key)
            {
                cout << "Roll no. " << key << " found at location" << pos << endl;
                flag++;
                break;
            }
        }
    }
    if (flag == 0) // when key is not found
    {
        cout << "\nRoll no. " << key << " does not found in hash table ";
    }
}
void linear_prob::display()
{
    cout << "\nFinal array of student Roll no. after linear probing\n";
    cout << left << setw(10) << "index" << left << setw(10) << "data"
         << left << setw(10) << "link\n";
    for (int i = 0; i < n; i++)
    {
        cout << left << setw(10) << i << left << setw(10) << val[i].data << left << setw(10) << val[i].chain << endl;
    }
}
int main()
{
    system("cls");
    int key, op;
    linear_prob hash;
    do
    {
        cout << "\n\n1) Create a hash table without replacement \n2) Search in hash table without replacement \n3) Create a hash table with replacement \n4) Search in hash table with replacement \n5)Display hash table \n6) Exit.";
        cout << "\nEnter Your Choice: ";
        cin >> op;
        switch (op)
        {
        case 1:
            hash.create_without_replacement();
            break;
        case 2:
            cout << "\nEnter the the Roll no.for seaech :";
            cin >> key;
            hash.search_without_replacement(key);
            break;
        case 3:
            hash.create_with_replacement();
            break;
        case 4:
            cout << "\nEnter the Roll no. for search :";
            cin >> key;
            hash.search_with_replacement(key);
            break;
        case 5:
            hash.display();
            break;
        case 6:
            cout << "\n\nYour are exit from program!!";
            break;
        }
    } while (op != 6);
    return 0;
}

