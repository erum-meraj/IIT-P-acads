#include <iostream>
using namespace std;

class heap
{
public:
    int arr[100];
    int size = 0;
    heap()
    {
        arr[0] = -1;
    }

    void insert(int val)
    {
        size = size + 1;
        arr[size] = val;
        int i = size;
        while (i > 0)
        {
            if (arr[i / 2] < arr[i] && i / 2 > 0)
            {
                swap(arr[i], arr[i / 2]);
                i = i / 2;
            }
            else
            {
                break;
            }
        }
    }

    void remove()
    {
        arr[1] = arr[size];
        size--;
        int i = 1;
        while (2 * i <= size)
        {
            display();
            if (arr[i] < arr[2 * i] && 2 * i <= size)
            {
                swap(arr[i], arr[2 * i]);
                i = 2 * i;
                cout << "i = " << i << endl;
                display();
            }
            else
            {
                break;
            }
        }
    }

    void display()
    {
        for (int i = 1; i < size + 1; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

void heapify(int arr[], int i)
{
    while (i > 0)
    {
        if (arr[i / 2] < arr[i] && i / 2 > 0)
        {
            swap(arr[i / 2], arr[i]);
            i /= 2;
        }
        else
        {
            return;
        }
    }
    while (i > 0)
    {
        if (arr[i / 2 + 1] < arr[i] && i / 2 + 1 > 0)
        {
            swap(arr[i / 2 + 1], arr[i]);
            i = i / 2 + 1;
        }
        else
        {
            return;
        }
    }
}

void fix(int arr[], int size)
{
    // int size =
    int i = size / 2 + 1;
    while (i > 0)
    {
        heapify(arr, i);
        i--;
    }
}

int main()
{
    // heap h;
    // h.insert(4);
    // h.insert(3);
    // h.insert(7);
    // h.insert(9);
    // h.insert(1);
    // h.display();
    // h.remove();
    // h.display();
    int arr[] = {-1, 5, 3, 2, 4, 6, 8, 7, 4, 3, 5, 7};
    fix(arr, 11);
    for (int i = 1; i < 11 + 1; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}