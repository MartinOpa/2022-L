#include <iostream>

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

class Tree
{
private:
    string key;
    string value;
    Tree *left;
    Tree *right;
public:
    Tree(string k, string v);
    ~Tree();
    string GetKey();
    string GetValue();
    Tree* GetLeft();
    Tree* GetRight();
    Tree* CreateLeft(string k, string v);
    Tree* CreateRight(string k, string v);
};

Tree::Tree(string k, string v)
{
    this->key = k;
    this->value = v;
    this->left = nullptr;
    this->right = nullptr;
}

Tree::~Tree()
{
    if (this->left != nullptr || this->right != nullptr)
    {
        delete this->left;
        delete this->right;
        this->left = nullptr;
        this->right = nullptr;
    }
}

Tree* Tree::GetLeft()
{
    return this->left;
}

Tree* Tree::GetRight()
{
    return this->right;
}

Tree* Tree::CreateLeft(string k, string v)
{
    this->left = new Tree(k, v);
    return this->left;
}

Tree* Tree::CreateRight(string k, string v)
{
    this->right = new Tree(k, v);
    return this->right;
}

string Tree::GetKey()
{
    return this->key;
}

string Tree::GetValue()
{
    return this->value;
}


int main()
{
    Tree *first = new Tree("Organismus", "Zvíře");
    first->CreateLeft("Zvíře", "Šelmy");
    first->CreateRight("Zvíře", "Plazi");
    Tree *firstLeft = first->GetLeft();
    Tree *firstRight = first->GetRight();
    firstLeft->CreateLeft("Šelmy", "Kočkovité");
    firstLeft->CreateRight("Šelmy", "Psovité");
    firstRight->CreateLeft("Plazi", "Krokodýli");
    firstRight->CreateRight("Plazi", "Šupinatí");
    Tree *secondLL = firstLeft->GetLeft();
    Tree *secondLR = firstLeft->GetRight();
    Tree *secondRL = firstRight->GetLeft();
    Tree *secondRR = firstRight->GetRight();
    secondLL->CreateLeft("Kočkovité", "Puma");
    secondLL->CreateRight("Kočkovité", "Rys");
    secondLR->CreateLeft("Psovité", "Hyena");
    secondLR->CreateRight("Psovité", "Liška");
    secondRL->CreateLeft("Krokodýli", "Aligátor");
    secondRL->CreateRight("Krokodýli", "Krokodýl");
    secondRR->CreateLeft("Šupinatí", "Ještěři");
    secondRR->CreateRight("Šupinatí", "Hadi");
    Tree *secondLLL = secondLL->GetLeft();
    Tree *secondLLR = secondLL->GetRight();
    Tree *secondLRL = secondLR->GetLeft();
    Tree *secondLRR = secondLR->GetRight();
    Tree *secondRLL = secondRL->GetLeft();
    Tree *secondRLR = secondRL->GetRight();
    Tree *secondRRL = secondRR->GetLeft();
    Tree *secondRRR = secondRR->GetRight();

    cout << "\t\t\t\t   " << first->GetKey() << ", " << first->GetValue() << "\n\n";

    cout << "\t\t\t"  << firstLeft->GetKey() << ", " << firstLeft->GetValue() << "\t\t";
    cout << firstRight->GetKey() << ", " << firstRight->GetValue() << "\n\n";

    cout << secondLL->GetKey() << ", " << secondLL->GetValue() << "\t";
    cout << secondLR->GetKey() << ", " << secondLR->GetValue() << "\t\t";
    cout << secondRL->GetKey() << ", " << secondRL->GetValue() << "\t";
    cout << secondRR->GetKey() << ", " << secondRR->GetValue() << "\n\n";

    cout << secondLLL->GetKey() << ", " << secondLLL->GetValue() << "\t\t";
    cout << secondLRL->GetKey() << ", " << secondLRL->GetValue() << "\t\t";
    cout << secondRLL->GetKey() << ", " << secondRLL->GetValue() << "\t";
    cout << secondRRL->GetKey() << ", " << secondRRL->GetValue() << "\n";
    
    cout << secondLLR->GetKey() << ", " << secondLLR->GetValue() << "\t\t";
    cout << secondLRR->GetKey() << ", " << secondLRR->GetValue() << "\t\t";
    cout << secondRLR->GetKey() << ", " << secondRLR->GetValue() << "\t";
    cout << secondRRR->GetKey() << ", " << secondRRR->GetValue() << endl;

    return 0;
}