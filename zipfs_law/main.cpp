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
