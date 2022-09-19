#include <iostream>

using namespace std;

template<class T>
class BOX {
private:
    T * instance;

public:
    BOX(T * i);
    T * GetInstance();
};

template<class T>
BOX<T>::BOX(T * i){
    this->instance = i;
}

template<class T>
T * BOX<T>::GetInstance(){
    return this->instance;
}

class A {
private:
    int value;

public:
    A(int v);
    int GetValue();
};

A::A(int v){
    this->value = v;
}

int A::GetValue(){
    return this->value;
}

int main() {
    A * a = new A(50);
    BOX<A> * ta = new BOX<A>(a);

    cout << ta->GetInstance()->GetValue();

    delete ta;
    delete a;

    return 0;
}