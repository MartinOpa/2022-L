#include <iostream>

#define N 1000

using namespace std;

/*
• Implementujte třídu KeyValue dle přednášky a vytvořte zřetězenou lineární strukturu mnoha (např. tisíce)
objektů a pracujte s ní (vypište např. všechny klíče od prvního do posledního objektu).
• Vytvořte podobnou třídu jako KeyValue, ale s hodnotou i klíčem typu (třídy)
string a se dvěma sousedícími (next) objekty. Výsledkem bude tzv. strom.
• Implementuje strukturu (rozhodovací strom) na identifikaci zvířat nebo rostlin.
Klíčem uzlu stromu je rozhodovací kritérium, hodnotou uzlu je název zvířete nebo rostliny, resp. druhu apod.
Naplňte klíč alespoň deseti objekty a vypište celou strukturu na obrazovku.
*/

class KeyValue
{
private:
    int key;
    double value;
    KeyValue *next;
public:
    KeyValue(int k, double v);
    ~KeyValue();
    int GetKey();
    double GetValue();
    KeyValue* GetNext();
    KeyValue* CreateNext(int k, double v);
};

class KeyValues
{
private:
    KeyValue** keyValues;
    int count;
public:
    KeyValues(int n);
    ~KeyValues();
    KeyValue* CreateObject(int k, double v);
    KeyValue* SearchObject(int key);
    int Count();
};

KeyValue::KeyValue(int k, double v)
{
    this->key = k;
    this->value = v;
    this->next = nullptr;
}

KeyValue::~KeyValue()
{
    if (this->next != nullptr)
    {
        delete this->next;
        this->next = nullptr;
    }
}

KeyValue* KeyValue::GetNext()
{
    return this->next;
}

KeyValue* KeyValue::CreateNext(int k, double v)
{
    this->next = new KeyValue(k, v);
    return this->next;
}

int KeyValue::GetKey()
{
    return this->key;
}

double KeyValue::GetValue()
{
    return this->value;
}

KeyValues::KeyValues(int n)
{
    this->keyValues = new KeyValue*[n];
    this->count = 0;
}

KeyValues::~KeyValues()
{
    for (int i = 0; i < this->count; i++)
    {
        delete this->keyValues[i];
    }

    delete[] this->keyValues;
}

int KeyValues::Count()
{
    return this->count;
}

KeyValue* KeyValues::CreateObject(int k, double v)
{
    KeyValue *newObject = new KeyValue(k, v);

    this->keyValues[this->count] = newObject;
    this->count += 1;

    return newObject;
}

KeyValue* KeyValues::SearchObject(int k)
{
    for (int i = 0; i < this->count; i++)
    {
        if (this->keyValues[i]->GetKey() == k)
        {
            return this->keyValues[i];
        }
    }

    return nullptr;
}

int main()
{
    KeyValues* myKeyValues = new KeyValues(N);
    double init = 1.23456;

    KeyValue* myKeyValue = myKeyValues->CreateObject(0, init);

    for (int i = 0; i < N; i++)
    {
        double randVal = ( (rand()%10 + 1) / 1.2345 );
        myKeyValues->CreateObject(i+1, randVal);
    }
    
    cout << "člen 1 = " << myKeyValues->SearchObject(0)->GetValue() << endl;
    cout << "člen 2 = " << myKeyValues->SearchObject(1)->GetValue() << endl;
    cout << "člen 3 = " << myKeyValues->SearchObject(2)->GetValue() << endl;

    for (int i = 0; i < 7; i++)
    {
        int mem = rand()%1000; 
        cout << "člen " << mem << " = " << myKeyValues->SearchObject(mem)->GetValue() << endl;
    }
    
    delete myKeyValues;

    return 0;
}