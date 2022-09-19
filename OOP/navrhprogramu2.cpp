#include <iostream>
#include <vector>

using namespace std;

/*
• Implementujte dědičné hierarchie zákazníků a produktů podle přednášky. Jak pro zákazníky,
tak pro produkty navrhněte data a chování, které potomci rozšiřují.
• Navrhněte a implementujte třídy pro objednávku a položku objednávky.
• Napište program, ve kterém vytvoříte několik různých objednávek (s různými typy zákazníků a produktů).
• Vypište obsah vytvořených objednávek na obrazovku.
*/

class AbstractProduct
{
private:
    static int objectsCount;
    string name;
    int price;
    int code;
public:
    static int GetObjectsCount();
    AbstractProduct(int p, string n);
    ~AbstractProduct();
    //AbstractProduct();
    //virtual ~AbstractProduct()

    //virtual int GetCode();
    //virtual int GetPrice();
    //virtual string GetName();
    int GetCode();
    int GetPrice();
    string GetName();
};

/*
class MobilePhone : public AbstractProduct
{
private:
public:
    MobilePhone(int p, string n);
    ~MobilePhone();
int GetCode();
    int GetPrice();
    string GetName();
}
*/

class Catalog
{
private:
    AbstractProduct** products;
    int productsCount;
public:
    Catalog(int i);
    ~Catalog();

    AbstractProduct* GetAbstractProduct(int c);

    AbstractProduct* CreateAbstractProduct(int c, int p, string n);
};

class AbstractCustomer
{
private:
    static int objectsCount;
    int code;
    string name;
public:
    static int GetObjectsCount();

    AbstractCustomer(string n);
    ~AbstractCustomer();
    //AbstractCustomer();
    //virtual ~AbstractCustomer();

    int GetCode();
    string GetName();
    //virtual int GetCode();
    //virtual string GetName();
};

/*
class RegisteredUser : public AbstractCustomer
{
private:

public:
    RegisteredUser(string n, int id, ...);
    ~RegisteredUser();

    int GetCode();
    int GetName();
}
*/


class Order
{
private:
    AbstractCustomer* customer;
    //vector<AbstractProduct*> items;
    string name;
    vector<string> item;
    int totalPrice;
    int itemCount;
public:
    Order(int total, AbstractCustomer *c);
    ~Order();

    void OrderItems(AbstractProduct *i);
    int GetTotalPrice();
    //vector<string> GetItems();
    //int OrderPrice(vector<AbstractProduct*> items);
};

int AbstractProduct::objectsCount = 0;

AbstractProduct::AbstractProduct(int p, string n)
{
    this->price = p;
    this->name = n;
    this->code = objectsCount;
    AbstractProduct::objectsCount += 1;
}

/*
AbstractProduct::AbstractProduct()
{
    cout << "abstract product" << endl;
}
*/

AbstractProduct::~AbstractProduct()
{
    AbstractProduct::objectsCount -= 1;
}

int AbstractProduct::GetObjectsCount()
{
    return AbstractProduct::objectsCount;
}

string AbstractProduct::GetName()
{
    return this->name;
}

int AbstractProduct::GetPrice()
{
    return this->price;
}

int AbstractProduct::GetCode()
{
    return this->code;
}

int AbstractCustomer::objectsCount = 0;

/*
AbstractCustomer::AbstractCustomer()
{
    cout << "abstract customer" << endl;
}
*/

AbstractCustomer::AbstractCustomer(string n)
{
    this->name = n;
    this->code = objectsCount;
    AbstractCustomer::objectsCount += 1;
}

AbstractCustomer::~AbstractCustomer()
{
    AbstractCustomer::objectsCount -= 1;
}

int AbstractCustomer::GetObjectsCount()
{
    return AbstractCustomer::objectsCount;
}

string AbstractCustomer::GetName()
{
    return this->name;
}

int AbstractCustomer::GetCode()
{
    return this->code;
}

Catalog::Catalog(int c)
{
    this->productsCount = c;
    this->products = new AbstractProduct*[c];
}

Catalog::~Catalog()
{
    delete this->products;
    this->products = nullptr;
}

AbstractProduct* Catalog::CreateAbstractProduct(int c, int p, string n)
{
    AbstractProduct *newAbstractProduct = new AbstractProduct(p, n);

    this->products[c] = newAbstractProduct;

    return newAbstractProduct;
}

AbstractProduct* Catalog::GetAbstractProduct(int c)
{
    for (int i = 0; i < this->productsCount; i++)
    {
        if (this->products[i]->GetCode() == c)
        {
            return this->products[i];
        }
    }

    return nullptr;
}

Order::Order(int total, AbstractCustomer *c)
{
    this->name = c->GetName();
    this->totalPrice = 0;
    this->itemCount = 0;
}

Order::~Order()
{
    this->itemCount -= 1;
}

void Order::OrderItems(AbstractProduct *i)
{
    this->totalPrice += i->GetPrice();
    //this->item[this->itemCount] = i->GetName();
    itemCount += 1;
}

int Order::GetTotalPrice()
{
    return this->totalPrice;
}

/*
int Order::OrderPrice(vector<AbstractProduct*> items)
{
    int total = 0;
    for (int i = 0; i < items.size(); i++)
    {
        total += items[i]->GetPrice();
    }
    return total;
}*/

int main()
{
    AbstractProduct *p1;
    AbstractProduct *p2;
    AbstractProduct *p3;

    Catalog *c = new Catalog(3);

    AbstractCustomer *c1 = new AbstractCustomer("John");

    p1 = c->CreateAbstractProduct(0, 3000, "iphone");
    p2 = c->CreateAbstractProduct(1, 2600, "samsung");
    p3 = c->CreateAbstractProduct(2, 1000, "huawei");

    Order *o = new Order(5, c1);

    cout << p1->GetCode() << ", " << p1->GetName() << ", " << p1->GetPrice() << endl;
    cout << p2->GetCode() << ", " << p2->GetName() << ", " << p2->GetPrice() << endl;
    cout << p3->GetCode() << ", " << p3->GetName() << ", " << p3->GetPrice() << endl;

    o->OrderItems(p1);
    o->OrderItems(p1);
    o->OrderItems(p1);
    o->OrderItems(p3);
    o->OrderItems(p2);
    o->OrderItems(p3);

    cout << c1->GetName() << " má objednávku za: " << o->GetTotalPrice() << endl;

    delete o;
    delete c1;
    delete c;

    return 0;
}