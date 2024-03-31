/*
Napisz program zliczający liczbę wystąpień danego słowa w pliku tekstowym. Program powinien wypisać dane
w trzech kolumnach: w pierwszej kolejną liczbę naturalną (= numer słowa), w drugiej - liczbę wystąpień danego
słowa, w trzeciej – dane słowo, w kolejności od słowa o największej liczbie wystąpień do słowa o najmniejszej
liczbie wystąpień. W przypadku słów o identycznej liczbie wystąpień słowa można wyświetlić w kolejności
dowolnej. Jako plik wejściowy (źródło słów) zastosuj tekst pobrany z serwisu Wolne Lektury wyznaczony na
podstawie ostatniej cyfry indeksu:
    a) 0 lub 1: Jan Chryzostom Pasek, „Pamiętniki”
    b) 2 lub 3: Stefan Żeromski, „Przedwiośnie”
    c) 4 lub 5: Bolesław Prus, „Faraon” (trzy tomy)
    d) 6 lub 7: Bolesław Prus, „Lalka” (oba tomy)
    e) 8 lub 9: Karol Darwin, „O powstawaniu gatunków drogą doboru naturalnego”
W oparciu o powyższe dane sprawdź, czy słowa z danej lektury spełniają prawo Zipfa
(https://en.wikipedia.org/wiki/Zipf%27s_law)
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>

std::string filter(const std::string& text) {
    std::string filteredText = "";
    for (char a : text) {
        if (!ispunct(a) && !isdigit(a)) { // pomija znaki interpunkcyjne i cyfry
            filteredText += std::tolower(a); // dodaje znaki zmienione na małe
        }
    }

    return filteredText;
}

std::string readFile(std::string& filename) {
    std::ifstream file(filename); // strumień do odczytu

    std::stringstream buffer; // bufor do przechowania odczytanych danych
    buffer << file.rdbuf(); // odczytywanie pliku i zapis do bufora
    file.close(); // zamykanie strumienia

    return buffer.str(); // return zawartości bufora jako string
}

std::vector<std::pair<int, std::string>> countWordAppearances(const std::string& text) {
    std::map<std::string, int> wordMap; // map<klucz - wyraz, wartość - liczba wystąpień>
    std::istringstream iss(text); // strumień wejściowy
    std::string word;

    while (iss >> word) { // domyślnie białe znaki jako separator
        wordMap[word]++;
    }

    std::vector<std::pair<int, std::string>> sortedWords; //pomocniczy wektor do sortowania według ilości wystąpień
    for (const auto& pair : wordMap) {
        sortedWords.emplace_back(pair.second, pair.first);
    }
    std::sort(sortedWords.rbegin(), sortedWords.rend());

    return sortedWords;
}

int main() {
    std::string filename = "";
    int index = 0;
    int counter = 1;

    std::cout << "Podaj indeks (od 0 do 9): ";
    std::cin >> index;

    if (index == 0 || index == 1) {
        std::cout << "\nJan Chryzostom Pasek 'Pamiętniki'\n\n";
        filename = "pamietniki.txt";
    } else if (index == 2 || index == 3) {
        std::cout << "\nStefan Żeromski 'Przedwiośnie'\n\n";
        filename = "przedwiosnie.txt";
    } else if (index == 4 || index == 5) {
        std::cout << "\nBolesław Prus 'Faraon'\n\n";
        filename = "faraon.txt";
    } else if (index == 6 || index == 7) {
        std::cout << "\nBolesław Prus 'Lalka'\n\n";
        filename = "lalka.txt";
    } else if (index == 8 || index == 9) {
        std::cout << "\nKarol Darwin 'O powstawaniu garunków drogą doboru naturalnego'\n\n";
        filename = "darwin-o-powstawaniu-gatunkow.txt";
    } else {
        std::cout << "\nBłędny indeks\n";
        return 0;
    }

    std::vector<std::pair<int, std::string>> wordMap = countWordAppearances(filter(readFile(filename)));

    //liczba porządkowa - liczba wystąpień - stała z prawa Zipfa (1) - wyraz
    std::cout << "n.\t\tliczba\t\tZipf\t\twyraz\n\n";

    for (auto& pair : wordMap) {
    //wyrazy pojawiające się tylko raz lub dwa razy stanowią około 2/3 tekstu, wykluczyłem je przy wypisywaniu dla poprawy czytelności
        if (pair.first > 2) {
            // (1) sprawdzam prawo Zipfa w formie: ranga * częstotliwość = const
            double zipf = counter * (pair.first / static_cast<double>(wordMap.begin()->first));
            std::cout << counter << "\t\t" << pair.first << "\t\t" << zipf << "\t\t" << pair.second << std::endl;
            counter++;
        }
    }

    return 0;
}
