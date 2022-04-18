#include <bits/stdc++.h>
using namespace std;

class record
{
public:
    int capacity;
    int primary_key;

    record(int capacity, int primary_key)
    {
        this->capacity = capacity;
        this->primary_key = primary_key;
    }
};

class page
{
public:
    vector<record *> data;
    int page_id;
    int num_rec;
    int empty_space;
    int free_space;
    page *prev;
    page *next;

    page(int capacity, int k)
    {
        page_id = k;
        num_rec = 0;
        empty_space = capacity - 16;
        free_space = 0;
        prev = nullptr;
        next = nullptr;
    }
};

class heap
{
public:
    page *head;
    int page_capacity;
    int page_id;
    int num_page;

    heap(int capacity)
    {
        head = nullptr;
        page_capacity = capacity;
        page_id = 0;
        num_page = 0;
    }

    void insert(int size, int prim_key)
    {
        // Inserting first record
        if (head == nullptr)
        {
            page *first_page = new page(page_capacity, page_id);
            page_id++;
            num_page++;
            head = first_page;

            record *first_record = new record(size, prim_key);

            head->data.push_back(first_record);
            head->free_space += size;
            head->empty_space -= size + 4;
            head->num_rec = 1;
            return;
        }

        // Checking for first page who can accomodate this record
        page *curr = head;
        while (curr != nullptr && curr->empty_space < size + 4)
        {
            curr = curr->next;
        }

        // When new page is required
        if (curr == nullptr)
        {
            // Getting the pointer to last page
            curr = head;
            while (curr->next != nullptr)
            {
                curr = curr->next;
            }

            page *last_page = new page(page_capacity, page_id);
            page_id++;
            num_page++;

            record *rec = new record(size, prim_key);

            last_page->data.push_back(rec);
            last_page->free_space += size;
            last_page->empty_space -= size + 4;
            last_page->num_rec = 1;

            last_page->prev = curr;
            curr->next = last_page;
        }
        else // Case when record can be inserted in existing page
        {
            record *rec = new record(size, prim_key);

            curr->data.push_back(rec);
            curr->free_space += size;
            curr->empty_space -= size + 4;
            curr->num_rec++;
        }
    }

    void status()
    {
        cout << num_page << " ";

        page *curr = head;
        while (curr != nullptr)
        {
            cout << curr->num_rec << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    void find(int val)
    {
        page *curr = head;
        while (curr != nullptr)
        {
            for (int i = 0; i < curr->num_rec; i++)
            {
                if (curr->data[i]->primary_key == val)
                {
                    cout << curr->page_id << " " << i << endl;
                    return;
                }
            }
            curr = curr->next;
        }
        // If val not found
        cout << -1 << " " << -1 << endl;
    }
};

int main()
{
    int cap;
    cin >> cap;
    heap file(cap);

    int t;
    cin >> t;
    while (t != 4)
    {
        if (t == 1)
        {
            int size, prim_key;
            cin >> size >> prim_key;
            file.insert(size, prim_key);
        }
        else if (t == 2)
        {
            file.status();
        }
        else if (t == 3)
        {
            int val;
            cin >> val;
            file.find(val);
        }
        else
        {
            return 0;
        }
        cin >> t;
    }
    return 0;
}