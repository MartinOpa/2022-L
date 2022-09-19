#include <iostream>

using namespace std;

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
    string CanWithdraw(double a);

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

class AnimalAccount : public PartnerAccount
{
private:
    string species;
public:
    AnimalAccount(string s, int n, Client *o, Client *p);
    AnimalAccount(string s, int n, Client *o, Client *p, double ir);

    string GetSpecies();
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
    AnimalAccount* CreateAAccount(string s, int n, Client *o, Client *p);
    AnimalAccount* CreateAAccount(string s, int n, Client *o, Client *p, double ir);

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

AnimalAccount* Bank::CreateAAccount(string s, int n, Client *o, Client *p)
{
    return new AnimalAccount(s, n, o, p);
}

AnimalAccount* Bank::CreateAAccount(string s, int n, Client *o, Client *p, double ir)
{
    return new AnimalAccount(s, n, o, p, ir);
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

string Account::CanWithdraw(double a)
{
    if ( a > this->balance ) return "No";

    return "Yes";
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

AnimalAccount::AnimalAccount(string s, int n, Client *o, Client *p) : PartnerAccount(n, o, p)
{
    this->species = s;
}

AnimalAccount::AnimalAccount(string s, int n, Client *o, Client *p, double ir) : PartnerAccount(n, o, p, ir)
{
    this->species = s;
}

string AnimalAccount::GetSpecies()
{
    return this->species;
}

int main()
{
    AnimalAccount *aa1;
    Bank *b = new Bank(1, 2);

    Client *Shaggy = b->CreateClient(0, "Shaggy");
    Client *Scooby = b->CreateClient(1, "Scooby-Doo");
    
    aa1 = b->CreateAAccount("Great Dane", 1, Shaggy, Scooby, 0.8);

    cout << "\nBalance: " << aa1->GetBalance() << endl;

    aa1->Deposit(3500);

    cout << "Balance after deposit: " << aa1->GetBalance() << endl;

    cout << "CanWithdraw 3700?: " << aa1->CanWithdraw(3700) << endl;
    cout << "CanWithdraw 3200?: " << aa1->CanWithdraw(3200) << endl;

    aa1->Withdraw(3700);

    cout << "Balance Withdraw(3700): " << aa1->GetBalance() << endl;

    aa1->Withdraw(3200);

    cout << "Balance Withdraw(3200): " << aa1->GetBalance() << endl;
    
    cout << "GetInterestRate: " << aa1->GetInterestRate() << endl;

    aa1->AddInterest(0.3);

    cout << "GetInterestRate after AddInterest: " << aa1->GetInterestRate() << "\n\n";

    cout << "Animal account 1 owner: " << aa1->GetOwner()->GetName() << endl;
    cout << "Animal account 1 partner: " << aa1->GetPartner()->GetName() << endl;
    cout << "Animal account 1 partner species: " << aa1->GetSpecies() << endl;

    delete b;

    return 0;
}