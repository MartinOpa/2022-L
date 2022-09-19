#include "main.h"

int main(int argc, char** argv) {
    /// fungující testy 
    ///
    /// input je velmi háklivý na mezery a závorky, i přes snahu
    /// se mi nepodařilo doladit na méně striktní pravidla vstupu, proto raději nabízím alespoň
    /// 15 testovacích výrazů (google kalulačka pro ně dává stejné výsledky jako program)
    /// 
    /// pro spuštění je vytvořen klasický makefile, stačí spustit přes ./alg1 i, kde i je index testovacího stringu
    

    /// input
    ///
    /// #6 nelze vložit záporné číslo, ale takto lze počítat 328^(-1)
    const string original[] = 
    {
        "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3",
        "( ( 2 ^ 3 ) + ( 3 ^ 8 ) ) / 3",
        "( 2 ^ 3 ) + ( 3 ^ 8 )",
        "( ( 3 + 8 * 21 - 16 ) ^ 3 ) - 12",
        "( 53 ^ 3 ) - 13 * 29",
        "( 13 ^ 2 ) - 7 * ( ( 29 - 13 ) ^ 3 )",
        "( 328 ^ ( 1 - 2 ) )",
        "( ( ( ( ( 3 * 2 ) + ( 1 - 9 ) ) ^ 2 ) + ( 32 / 12 ) + ( 38 - ( 12 / 3 ) ) ^ 3 ) * 2 )",
        "38593479 * ( 4 ^ ( 0 - 9 ) ) + ( 12 ^ 2 ^ 4 ) - ( 3 ^ ( 2 * 4 - 11 ) ) - ( 12 ^ 21 )",
        "( 2 ^ 2 ^ 2 ^ 2 ^ ( 2 - 5 ) ) - ( 3 ^ 15 )",
        "3 * ( 2 ^ 9 ) / 18 - 3",
        "( 2 * ( ( 2 / 7 ) - ( 9 / 2 ) ) ) ^ ( 0 - 3 )",
        "10 / 10 / 10 / 13 / 17 * ( ( 42 ^ 3 ) / 10 )",
        "129443628 / ( ( ( 7 ^ 4 ) + 31 ) / 3 )",
        "( ( 10 ^ ( 0 - 3 ) ) / ( 3 ^ ( ( 1 + 2 ) * 3 ) ) ) * ( 10 ^ 6 )"
    };

    string func = original[atoi(argv[1])];
    ///výběr konstanty přes argument při spuštění

    string converted = yard(func);

    cout << "zadaný výraz: " << func << "\n";
    cout << "konvertovaný výraz: " << converted << "\n";

    float result = evaluate(converted);
    printf("výsledek: %f\n", result);

    return 0;
}