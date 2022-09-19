#include "shuntingYard.h"

///přidělí váhu operátoru
int isOperator(char op) {
    if (op == '+' || op == '-') return 2;
    if (op == '*' || op == '/') return 3;
    if (op == '^') return 4;
    else return 0;
}

///celá funkce psaná mnou dle algoritmu na wiki https:///en.wikipedia.org/wiki/Shunting_yard_algorithm, žádné "inspirace"
string yard(string str) {
    string converted = "";
    stack<int> operators;
    int i = 0;
    int digit = 0;
    int prec = 0;
    int parent = 0;

    while ( i < str.length() ) {
        char e = str[i];
        if( isdigit(str[i]) || str[i] == ' ' ) {
            ///pokud je element[i] číslice nebo mezera, vlož k výsledku
            converted.push_back(str[i]);
        }
        else if ( str[i] == '(' ) {
            ///pokud je element[i] otevírající závorka, je povolena následující podmínka a i++ přeskočí jednu mezeru
            operators.push(str[i]);
            i++;
            parent++;
        }
        else if ( parent > 0 && str[i] != ')' ) {
            ///dokud se nenajde uzavírající závorka k současné otevřené, čísla se ukládají do závorky a operátory do zásobníku
            operators.push(str[i]);
        }
        else if ( str[i] == ')' ) {
            ///po nalezení uzavírající závorky se přidají operátory
            while ( operators.top() != '(' ) {
                converted.push_back(operators.top());
                converted.push_back(' ');
                operators.pop();
            }
            ///pokračování v původním cyklu přeskakující "parent" podmínku
            operators.pop(); parent--;
        }
        else {
        prec = isOperator(str[i]);
        ///šetří chybu sahání do neexistující paměti v případě prvního operátoru následující funkce
        if ( operators.empty() ) {
            operators.push(str[i]);
        ///porovnává nadřazenost, rovnost či podřazenost operátoru v zásobníku s novým
        }
        else if ( prec <= isOperator(operators.top()) ) {
            if ( operators.top() != '^' ) {///podmínka kvůli stylu zápisu mocnin
            converted.push_back(operators.top());
            operators.pop();
            operators.push(str[i]);
            }
            else operators.push(str[i]);
        }
        else operators.push(str[i]);
    }i++;
}
    
    ///vyprázdnit zásobník operací
    while ( !operators.empty() ) {
        converted.push_back(' ');
        converted.push_back(operators.top());
        operators.pop();
    }

    converted = regex_replace(converted, regex("  "), " ");
    converted = regex_replace(converted, regex("  "), " ");
    ///Jednořádková regex funkce převzata zde - https://stackoverflow.com/questions/4643512/replace-substring-with-another-substring-c - maže duplicitní mezery
    ///
    ///není to hezké, ale zajišťuje správné fungování závorek

    return converted;
}