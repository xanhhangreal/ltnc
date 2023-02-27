#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int generateSecretNumber(){
    return rand() % 100 + 1;
}
int getPlayerGuess(){
    int guess;
    cout << "Enter a guess(1..100) ";
    cin >> guess;
    if(!cin.good() || guess >= 100 || guess <= 0) exit(1);
    return guess;
}
void printAnswer(int &guess, int &secretNumber){
    if(guess == secretNumber) cout << "Congratulation! You're won. \n";
    else if(guess > secretNumber) cout << "Your number is too big. \n";
    else cout << "Your number is too small. \n";
}
int main(int argc, char* argv[]){
    srand(time(0));
    int secretNumber = generateSecretNumber();
    //cout << secretNumber << '\n';
    int guess;
    do {
        guess = getPlayerGuess();
        printAnswer(guess, secretNumber);
    } while(guess != secretNumber);
    cout << "DONE!";
    return 0;
}
