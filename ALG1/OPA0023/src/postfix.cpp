#include "postfix.h"

///výběr operace
float calc(float num1, float num2, char op) {
    if( op == '+' ) return num1 + num2;
    if( op == '-' ) return num1 - num2;
    if( op == '*' ) return num1 * num2;
    if( op == '/' ) return num1 / num2;
    if( op == '^' ) return powf(num1, num2);
    else return 0;
}


///funkce z větší části převzata zde https://stackoverflow.com/questions/69167521/evaluate-multi-digit-expression
///
///použil jsem ji jako odrazový můstek ke skládání celého programu a také k pochopení stacku, 
///mírná úprava pro podporu mocnin a aby výsledek byl skutečně "float" (původní nedával výsledek jako float) 
///i přes tak silnou "inspiraci" rozumím co má dělat
float evaluate(string converted) {
    float result = 0;
    stack<float> expression;
    int i = 0;
    int digit = 0;

    while( i<converted.length() ) {
        char temp = converted[i];
        ///ošetření víceciferných vstupů
        if(isdigit(converted[i])) {
            digit = digit*10 + ( converted[i]-'0' );
        }
        ///po načtení cifer uloží číslo do zásobníku
        else if ( converted[i] == ' ' ) {
            expression.push(digit);
            digit = 0;
        }
        ///pokud není vstup ani číslo ani mezera, proveď operaci
        else {
            float num2 = expression.top();
            expression.pop();
            float num1 = expression.top();
            expression.pop();
            result = calc(num1, num2, temp);
            expression.push(result);
            i++;
        }i++;
    }
    return expression.top();
}