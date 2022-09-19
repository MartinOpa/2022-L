#include <iostream>
#include <stack>
#include <string>
#include <math.h>
#include <regex>

using namespace std;

float calc(float o1,float o2,char c)
{
    if(c=='+') return o1+o2;
    if(c=='-') return o1-o2;
    if(c=='*') return o1*o2;
    if(c=='/') return o1/o2;
    if(c=='^') return powf(o1, o2);
    else return 0;
}

float evaluate(string converted)
{
    float result = 0;
    stack<float> expression;
    int digit = 0;
    int i=0;
    while(i<converted.length())
    {
        char e = converted[i];
        if(isdigit(converted[i])) {
            digit = digit*10 + (converted[i]-'0');
        } else if (converted[i] == ' ') {
            expression.push(digit);
            digit = 0; 
        } else {
            float o2=expression.top();
            expression.pop();
            float o1=expression.top();
            expression.pop();
            result = calc(o1,o2,e);
            expression.push(result);
            i++;

        }i++;
    }
    return expression.top();
}

int isOperator(char c) {
    if (c == '+' || c == '-') return 2;
    if (c == '*' || c == '/') return 3;
    if (c == '^') return 4;
    else return 0;
}

string sort(string str) {
//celá funkce psaná mnou dle algoritmu na wiki https://en.wikipedia.org/wiki/Shunting_yard_algorithm
    string converted = "";
    stack<int> operators;
    int i = 0;
    int digit = 0;
    int prec = 0;
    int parent = 0;

    while (i < str.length()) {
        char e = str[i];
        if(isdigit(str[i]) || str[i] == ' ') {
            //pokud je element[i] číslice nebo mezera, vlož k výsledku
            converted.push_back(str[i]);
        } else if (str[i] == '(') {
            //pokud je element[i] otevírající závorka, je povolena následující podmínka a i++ přeskočí jednu mezeru
            operators.push(str[i]);
            i++;
            parent++;
        } else if (parent > 0 && str[i] != ')') {
            //dokud se nenajde uzavírající závorka k současné otevřené, čísla se ukládají do závorky a operátory do zásobníku
            operators.push(str[i]);
        } else if (str[i] == ')') {
            //po nalezení uzavírající závorky se přidají operátory
            while (operators.top() != '(') {
                converted.push_back(operators.top());
                converted.push_back(' ');
                operators.pop();
            }
            //pokračování v původním cyklu přeskakující "parent" podmínku
            operators.pop(); parent--;
        } else {
        prec = isOperator(str[i]);
        //šetří chybu sahání do neexistující paměti v případě prvního operátoru následující funkce
        if (operators.empty()) {
            operators.push(str[i]);
        //porovnává nadřazenost, rovnost či podřazenost operátoru v zásobníku s novým
        } else if (prec <= isOperator(operators.top())) {
            if (operators.top() != '^') {
            converted.push_back(operators.top());
            operators.pop();
            operators.push(str[i]);
            } else operators.push(str[i]);
        } else operators.push(str[i]);
    }i++;
}
    
    //vyprázdnit zásobník operací
    while (!operators.empty()) {
        converted.push_back(' ');
        converted.push_back(operators.top());
        operators.pop();
    }

    converted = regex_replace(converted, regex("  "), " ");
    converted = regex_replace(converted, regex("  "), " ");
    //https://stackoverflow.com/questions/4643512/replace-substring-with-another-substring-c - maže duplicitní mezery
    //není to hezké, ale zajišťuje správné fungování závorek

    return converted;
}

int main()
{
    /* fungující testy - input je velmi háklivý na mezery a závorky, i přes snahu
    se mi nepodařilo doladit na méně striktní pravidla vstupu, proto raději nabízím alespoň
    10 testovacích výrazů (google kalulačka pro ně dává stejné výsledky jako program)

    Znovu nepozornost při čtení zadání, hádám pak, že závorky jsou tím pádem jako "bonusové body",
    které snad trochu zachrání nedostatky potřeby přesnosti vstupu
    */

    const string original0 = "3 * ( 2 ^ 9 ) / 18 - 3";
    const string original1 = "( ( 2 ^ 3 ) + ( 3 ^ 8 ) ) / 3";
    const string original2 = "( 2 ^ 3 ) + ( 3 ^ 8 )";
    const string original3 = "( ( 3 + 8 * 21 - 16 ) ^ 3 ) - 12";
    const string original4 = "( 53 ^ 3 ) - 13 * 29";
    const string original5 = "( 13 ^ 2 ) - 7 * ( ( 29 - 13 ) ^ 3 )";
    const string original6 = "( 328 ^ ( 1 - 2 ) )"; //nelze vložit záporné číslo, ale takto lze počítat 328^(-1)
    const string original7 = "( ( ( ( ( 3 * 2 ) + ( 1 - 9 ) ) ^ 2 ) + ( 32 / 12 ) + ( 38 - ( 12 / 3 ) ) ^ 3 ) * 2 )";
    const string original8 = "38593479 * ( 4 ^ ( 0 - 9 ) ) + ( 12 ^ 2 ^ 4 ) - ( 3 ^ ( 2 * 4 - 11 ) ) - ( 12 ^ 21 )";
    const string original9 = "( 2 ^ 2 ^ 2 ^ 2 ^ ( 2 - 5 ) ) - ( 3 ^ 15 )";//tady program z nějakého důvodu zaokrouhluje desetinné místo nahoru

    string original = original0;//výběr konstanty zde, aby se nemusel přepisovat i cout

    string converted = sort(original);

    cout << "zadaný výraz: " << original << "\n";
    cout << "konvertovaný výraz: " << converted << "\n";

    float result = evaluate(converted);
    printf("výsledek: %f\n", result);
    return 0;
}