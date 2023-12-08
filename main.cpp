#include <string>
#include <iostream>
#include <Windows.h>

int checkSum(const int sequence[13]);

void printSeparator();

int main()
{
    /*
     * ustawienie koloru terminala na bialy,a kolor znakow na czarny
     */
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    int sequence[13];
    /*
     * wprowadzenie sekwencji
     */
    std::string string_sequence;
    std::cout << "Provide sequence" << std::endl;
    std::cin >> string_sequence;
    int iterator = 0;
    for (char& c : string_sequence){
        int number = (int)c - 48;
        if(number > 9 || number < 0 || iterator > 12) {
            std::cout << "Incorrect sequence!" << std::endl;
            system("pause");
            return -1;
        }
        sequence[iterator] = number;
        iterator++;
    }
    /*
     * sprawdzenie cyfry kontrolnej
     */
    sequence[12] = checkSum(sequence);

    system("CLS");
    std::cout << std::endl << std::endl;
    /*
     * zdefiniowanie alfabetów
     */
    std::string codes_A[10] = {"0001101", "0011001", "0010011", "0111101", "0100011", "0110001", "0101111", "0111011", "0110111", "0001011"};
    std::string codes_B[10] = {"0100111", "0110011", "0011011", "0100001", "0011101", "0111001", "0000101", "0010001", "0001001", "0010111"};
    std::string codes_C[10] = {"1110010", "1100110", "1101100", "1000010", "1011100", "1001110", "1010000", "1000100", "1001000", "1110100"};
    char alphabet[10][6] = { {'A', 'A', 'A', 'A', 'A', 'A'},
                             {'A', 'A', 'B', 'A', 'B', 'B'},
                             {'A', 'A', 'B', 'B', 'A', 'B'},
                             {'A', 'A', 'B', 'B', 'B', 'A'},
                             {'A', 'B', 'A', 'A', 'B', 'B'},
                             {'A', 'B', 'B', 'A', 'A', 'B'},
                             {'A', 'B', 'B', 'B', 'A', 'A'},
                             {'A', 'B', 'A', 'B', 'A', 'B'},
                             {'A', 'B', 'A', 'B', 'B', 'A'},
                             {'A', 'B', 'B', 'A', 'B', 'A'} };

    int first_symbol = sequence[0];
    /*
     * wypisanie kodu
     */
    for (int size = 0; size < 20; size++) {
        for (int i = 0; i < 6; i++)
            std::cout << (char)255;

        printSeparator();
        /*
        * wypisanie pierwszych 7 znakow
        */
        for (int i = 0; i < 6; i++) {
            std::string word;
            if (alphabet[first_symbol][i] == 'A') {
                word = codes_A[(int)sequence[i + 1]];
            }
            else {
                word = codes_B[(int)sequence[i + 1]];
            }
            for (char& c : word) {
                if (c == '1')
                    std::cout << (char)219;
                else
                    std::cout << (char)255;
            }
        }
        printSeparator();
        /*
        * wypisanie 6 ostatnich znakow
        */
        for (int i = 7; i < 13; i++) {
            std::string word = codes_C[(int)sequence[i]];
            for (char& c : word) {
                if (c == '1')
                    std::cout << (char)219;
                else
                    std::cout << (char)255;
            }
        }

        printSeparator();
        for (int i = 0; i < 6; i++)
            std::cout << (char)255;
        std::cout << std::endl;
    }
    /*
     * wydluzenie kresek oddzielajacych
     */
    for (int j = 0; j < 5; j++) {

        for (int i = 0; i < 6; i++)
            std::cout << (char)255;

        printSeparator();

        for (int i = 0; i < 6 * 7; i++) {
            std::cout << " ";
        }

        printSeparator();

        for (int i = 7 * 7; i < 13 * 7; i++) {
            std::cout << " ";
        }

        printSeparator();

        for (int i = 0; i < 6; i++)
            std::cout << (char)255;

        std::cout << std::endl;
    }
    /*
     * wypisanie cyfr
     */
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 6; j++) {
            std::cout << " ";
        }
        if (i == 7)
            std::cout << "    ";
        std::cout << sequence[i];
    }

    for (int i = 0; i < 6; i++)
        std::cout << (char)255;

    std::cout << std::endl << std::endl;
    system("pause");
    return 0;
}

int checkSum(const int sequence[13]){
    int sum = 0;
    for(int i = 1; i <= 12; i += 2)
        sum += sequence[i];

    sum *= 3;

    for(int i = 0; i < 12; i += 2)
        sum += sequence[i];

    if(sequence[12] != 10 - sum % 10){
        std::cout << "Wrong checksum!" << std::endl;
        std::cout << "Correcting checksum to:" << 10 - sum % 10 << std::endl;
        system("pause");
    }
    return 10 - sum % 10;
}

void printSeparator(){
    std::cout << (char)255;
    std::cout << (char)219;
    std::cout << (char)255;
    std::cout << (char)219;
    std::cout << (char)255;
}