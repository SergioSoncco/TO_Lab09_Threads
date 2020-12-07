
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
/*
 * Node Declaration
 */
struct node
{
    int info;
    struct node *next;
}*start;

/*
 * Class Declaration
 */
class single_llist
{
    public:
        node* create_node(int);
        void insert_begin(int);
        void insert_pos(int,int);
        void insert_last(int);
        void delete_pos(int);
        bool search(int);
        bool update(int,int);
        void display();
        single_llist()
        {
            start = NULL;
        }
};

/*
 * Main :contains menu
 */
/*int main()
{
    single_llist sl;

}*/

/*
 * Creating Node
 */
node *single_llist::create_node(int value)
{
    struct node *temp, *s;
    temp = new(struct node);
    if (temp == NULL)
    {
        cout<<"Memory not allocated "<<endl;
        return 0;
    }
    else
    {
        temp->info = value;
        temp->next = NULL;
        return temp;
    }
}

/*
 * Inserting element in beginning
 */
void single_llist::insert_begin(int val)
{

    struct node *temp, *p;
    temp = create_node(val);
    if (start == NULL)
    {
        start = temp;
        start->next = NULL;
    }
    else
    {
        p = start;
        start = temp;
        start->next = p;
    }

}

/*
 * Inserting Node at last
 */
void single_llist::insert_last(int val)
{
    struct node *temp, *s;
    temp = create_node(val);
    s = start;
    while (s->next != NULL)
    {
        s = s->next;
    }
    temp->next = NULL;
    s->next = temp;
    cout<<"Element Inserted at last"<<endl;
}

/*
 * Insertion of node at a given position
 */
void single_llist::insert_pos(int val,int pos)
{
    int counter = 0;
    struct node *temp, *s, *ptr;
    temp = create_node(val);

    int i;
    s = start;
    while (s != NULL)
    {
        s = s->next;
        counter++;
    }
    if (pos == 1)
    {
        if (start == NULL)
        {
            start = temp;
            start->next = NULL;
        }
        else
        {
            ptr = start;
            start = temp;
            start->next = ptr;
        }
    }
    else if (pos > 1  && pos <= counter)
    {
        s = start;
        for (i = 1; i < pos; i++)
        {
            ptr = s;
            s = s->next;
        }
        ptr->next = temp;
        temp->next = s;
    }
    else
    {
        cout<<"Positon out of range"<<endl;
    }
}


/*
 * Delete element at a given position
 */
void single_llist::delete_pos(int pos)
{
    int i, counter = 0;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return;
    }

    struct node *s, *ptr;
    s = start;
    if (pos == 1)
    {
        start = s->next;
    }
    else
    {
        while (s != NULL)
        {
            s = s->next;
            counter++;
        }
        if (pos > 0 && pos <= counter)
        {
            s = start;
            for (i = 1;i < pos;i++)
            {
                ptr = s;
                s = s->next;
            }
            ptr->next = s->next;
        }
        else
        {
            cout<<"Position out of range"<<endl;
        }
        free(s);
        cout<<"Element Deleted"<<endl;
    }
}

/*
 * Update a given Node
 */
bool single_llist::update(int val,int pos)
{
    int  i;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return false;
    }
    struct node *s, *ptr;
    s = start;
    if (pos == 1)
    {
        start->info = val;
    }
    else
    {
        for (i = 0;i < pos - 1;i++)
        {
            if (s == NULL)
            {
                cout<<"There are less than "<<pos<<" elements";
                return false;
            }
            s = s->next;
        }
        s->info = val;

    }
    return true;
}

/*
 * Searching an element
 */
bool single_llist::search(int val)
{
    int  pos = 0;
    bool flag = false;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return false;
    }

    struct node *s;
    s = start;
    while (s != NULL)
    {
        pos++;
        if (s->info == val)
        {
            flag = true;
            cout<<"Element "<<val<<" is found at position "<<pos<<endl;
        }
        s = s->next;
    }
    if (!flag)
        cout<<"Element "<<val<<" not found in the list"<<endl;

    return flag;
}

/*
 * Display Elements of a link list
 */
void single_llist::display()
{
    struct node *temp;
    if (start == NULL)
    {
        cout<<"The List is Empty"<<endl;
        return;
    }
    temp = start;
    cout<<"Elements of list are: "<<endl;
    while (temp != NULL)
    {
        cout<<temp->info<<"->";
        temp = temp->next;
    }
    cout<<"NULL"<<endl;
}
