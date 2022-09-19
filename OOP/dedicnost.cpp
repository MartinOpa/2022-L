#include <iostream>

using namespace std;

/*
• Implementuje příklad z přednášky a vytvořte banku s mnoha klienty a účty.
Zaměřte se na pochopení principu zastupitelnosti a na to, jak fungují konstruktory v dědičnosti.
• Navrhněte a implementujte další jednoduché příklady dědičnosti s rozšířením společného
stavu a chování,jako například Auto, Osobní auto, Nákladní auto.
*/

class Client
{
private:
    static int objectsCount;
    int code;
    string name;
public:
    static int GetObjectsCount();

    Client(int c, string n);
    ~Client();

    int GetCode();
    string GetName();
};

class Account
{
private:
    int number;
    double balance;
    double interestRate;

    Client *owner;

public:
    Account(int n, Client *o);
    Account(int n, Client *o, double ir);

    int GetNumber();
    double GetBalance();
    double GetInterestRate();
    Client *GetOwner();
    bool CanWithdraw(double a);

    void Deposit(double a);
    bool Withdraw(double a);
    void AddInterest(double i);
};

class PartnerAccount : public Account
{
private:
    Client *partner;

public:
    PartnerAccount(int n, Client *o, Client *p);
    PartnerAccount(int n, Client *o, Client *p, double ir);

    Client *GetPartner();
};

class Bank
{
private:
    Client** clients;
    int clientsCount;

    Account** accounts;
    int accountsCount;

public:
    Bank(int c, int a);
    ~Bank();

    Client* GetClient(int c);
    Account* GetAccount(int n);

    Client* CreateClient(int c, string n);
    Account* CreateAccount(int n, Client *o);
    Account* CreateAccount(int n, Client *o, double ir);
    PartnerAccount* CreatePAccount(int n, Client *o, Client *p);
    PartnerAccount* CreatePAccount(int n, Client *o, Client *p, double ir);

    void AddInterest(double i);
};

Account::Account(int n, Client *o)
{
    this->number = n;
    this->owner = o;
    this->balance = 0;
    this->interestRate = 0;
}

Account::Account(int n, Client *o, double ir)
{
    this->number = n;
    this->owner = o;
    this->balance = 0;
    this->interestRate = ir;
}

PartnerAccount::PartnerAccount(int n, Client *o, Client *p) : Account(n, o)
{
    this->partner = p;
}

PartnerAccount::PartnerAccount(int n, Client *o, Client *p, double ir) : Account(n, o, ir)
{
    this->partner = p;
}

Client *Account::GetOwner()
{
    return this->owner;
}

Client *PartnerAccount::GetPartner()
{
    return this->partner;
}

int Client::objectsCount = 0;

Client::Client(int c, string n)
{
    this->code = c;
    this->name = n;
    Client::objectsCount += 1;
}

Client::~Client()
{
    Client::objectsCount -= 1;
}

int Client::GetObjectsCount()
{
    return Client::objectsCount;
}

string Client::GetName()
{
    return this->name;
}

int Client::GetCode()
{
    return this->code;
}

Bank::Bank(int c, int a)
{
    this->clientsCount = c;
    this->accountsCount = a;
    this->clients = new Client*[c];
}

Bank::~Bank()
{
    delete this->clients;
    this->clients = nullptr;
}

Client* Bank::CreateClient(int c, string n)
{
    Client *newClient = new Client(c, n);

    this->clients[c] = newClient;

    return newClient;
}

Account* Bank::CreateAccount(int n, Client *o)
{
    return new Account(n, o);
}

Account* Bank::CreateAccount(int n, Client *o, double ir)
{
    return new Account(n, o, ir);
}

PartnerAccount* Bank::CreatePAccount(int n, Client *o, Client *p)
{
    return new PartnerAccount(n, o, p);
}

Client* Bank::GetClient(int c)
{
    for (int i = 0; i < this->clientsCount; i++)
    {
        if (this->clients[i]->GetCode() == c)
        {
            return this->clients[i];
        }
    }

    return nullptr;
}

double Account::GetBalance()
{
    return this->balance;
}

double Account::GetInterestRate()
{
    return this->interestRate;
}

bool Account::CanWithdraw(double a)
{
    if ( a > this->balance ) return true;

    return false;
}

void Account::Deposit(double a)
{
    this->balance += a;
}

bool Account::Withdraw(double a)
{
    if ( this->balance > a )
    {
        this->balance -= a;
        return true;
    }
    
    return false;
}

void Account::AddInterest(double i)
{
    this->interestRate += i;
}

int main()
{
    Account *a1;
    Account *a2;
    Account *a3;
    Account *a4;
    Account *a5;
    Account *a6;
    Account *a7;
    Account *a8;
    Account *a9;
    Account *a10;
    
    PartnerAccount *pa1;
    PartnerAccount *pa2;
    PartnerAccount *pa3;
    PartnerAccount *pa4;
    PartnerAccount *pa5;
    
    Bank *b = new Bank(13, 15);

    Client *Smith = b->CreateClient(0, "Smith");
    Client *Jones = b->CreateClient(1, "Jones");
    Client *Carter = b->CreateClient(2, "Carter");
    Client *Williams = b->CreateClient(3, "Williams");
    Client *Claude = b->CreateClient(4, "Claude");
    Client *Thomas = b->CreateClient(5, "Thomas");
    Client *Obama = b->CreateClient(6, "Obama");
    Client *Banner = b->CreateClient(7, "Banner");
    Client *Rodgers = b->CreateClient(8, "Rodgers");
    Client *Taylor = b->CreateClient(9, "Taylor");
    Client *Hall = b->CreateClient(10, "Hall");
    Client *Organa = b->CreateClient(11, "Organa");
    Client *Cage = b->CreateClient(12, "Organa");

    a1 = b->CreateAccount(0, Smith);
    a2 = b->CreateAccount(1, Jones);
    a3 = b->CreateAccount(2, Williams);
    a4 = b->CreateAccount(3, Claude, 1.2);
    a5 = b->CreateAccount(4, Thomas);
    a6 = b->CreateAccount(5, Rodgers, 1.8);
    a7 = b->CreateAccount(6, Taylor);
    a8 = b->CreateAccount(7, Hall);
    a9 = b->CreateAccount(8, Organa, 0.5);
    a10 = b->CreateAccount(9, Cage);
    
    pa1 = b->CreatePAccount(10, Rodgers, Carter);
    pa2 = b->CreatePAccount(11, Cage, Obama);
    pa3 = b->CreatePAccount(12, Smith, Thomas);
    pa4 = b->CreatePAccount(13, Banner, Carter);
    pa5 = b->CreatePAccount(14, Hall, Organa);

    cout << "\nBalance: " << a1->GetBalance() << endl;

    a1->Deposit(3500);

    cout << "Balance after deposit: " << a1->GetBalance() << endl;

    cout << "CanWithdraw 3700?: " << a1->CanWithdraw(3700) << endl;
    cout << "CanWithdraw 3200?: " << a1->CanWithdraw(3200) << endl;

    a1->Withdraw(3700);

    cout << "Balance Withdraw(3700): " << a1->GetBalance() << endl;

    a1->Withdraw(3200);

    cout << "Balance Withdraw(3200): " << a1->GetBalance() << endl;
    
    cout << "GetInterestRate: " << a1->GetInterestRate() << endl;

    a1->AddInterest(0.3);

    cout << "GetInterestRate after AddInterest: " << a1->GetInterestRate() << "\n\n";

    cout << "GetInterestRate (account 9): " << a9->GetInterestRate() << endl;

    a9->AddInterest(0.3);

    cout << "GetInterestRate (account 9) after AddInterest: " << a9->GetInterestRate() << "\n\n";

    cout << "Account 4 owner: " << a4->GetOwner()->GetName() << endl;
    cout << "Account 10 owner: "<< a10->GetOwner()->GetName() << endl;
    cout << "Account 7 owner: "<< a7->GetOwner()->GetName() << endl;
    cout << "Partner Account 5 owner: " << pa5->GetOwner()->GetName() << ", partner: " << pa5->GetPartner()->GetName() << endl;
    cout << "Partner Account 2 owner: " << pa2->GetOwner()->GetName() << ", partner: " << pa2->GetPartner()->GetName() << endl;
    cout << "Partner Account 3 owner: " << pa3->GetOwner()->GetName() << ", partner: " << pa3->GetPartner()->GetName() << endl;
    cout << "Client 11: " << b->GetClient(11)->GetName() << endl;
    cout << "Client 3: " << b->GetClient(3)->GetName() << endl;
    cout << "Client 7: " << b->GetClient(7)->GetName() << endl;

    delete b;

    return 0;
}