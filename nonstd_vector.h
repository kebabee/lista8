/*
Szablon klasy cpplab::vector z typem danych podanym jako argument szablonu. Klasa wspiera dynamiczne dodawanie i usuwanie elementów oraz zmianę długości wektora.
Domyślny konstruktor nie alokowuje żadnej pamięci. Zaimplementowana podstawowa funkcjonalności tj. operatory do pobrania i modyfikacji poszczególnych składowych wektora.
Dodatkowo klasa ma zdefiniowany typ value_type.

Operator mnożenia skalarnego pozwala pczyć iloczyny skalarne wektorów cpplab::vector oraz std::vector w dowolnej konfiguracji argumentów i typu składowych wektorów.
Koncept operatora, sprawdza czy przekazany do szablonu operatora * typ spełnia minimalne wymagania, aby iloczyn skalarny dał się wykonać.
W przypadku różnej lub zerowej liczby składowych argumentów operatora mamy zwrócony wyjątek z opisem błędu.

Zaimplementowana wielką piątka tj. konstruktor kopiujący, kopiujący operator = z argumentami typu const l-value reference, destruktor,
konstruktor przenoszący oraz przenoszący operator= z argumentami typu r-value reference.

Metoda emplace_back() mza za zadanie przyjmowanie argumentów mogących stworzyć obiekty typu T, gdzie T to typ elementów przechowywanych przez dany wektor. 
Wykorzystuje parameter packi i perfect forwarding, aby z przekazanych argumentów bez zbędnej kopii stworzyć w wektorze nowy, dodany na koniec obiekt typu T.
*/

#include<iostream>
#include<vector>
#include<concepts>
#include<string>

namespace cpplab 
{
    template<typename T>
    class vector 
    {
        private:
            T* _data = nullptr;
            size_t _size;
            size_t _capacity;
        
        public:
            typedef T value_type;

            // konstruktor
            vector() 
            {
                _data = new T[1];
                _size = 0;
                _capacity = 1;
                std::cout << "Constructor (empty)\n";
            }

            // konstruktor z pierwszym elementem wektora
            vector(T firstElem) 
            {
                _data = new T[2];
                _size = 1;
                _capacity = 2;
                _data[0] = firstElem;
                std::cout << "Constructor (w/ element)\n";
            }

            // konstruktor kopiujący
            vector(const vector& v) 
            {
                _size = v._size;
                _capacity = v._capacity;
                _data = new T[_capacity];
                for (int i = 0; i < _capacity; i++)
                {
                    _data[i] = v._data[i];
                }
                std::cout << "Copy constructor\n";
            }

            // konstruktor przenoszący
            vector(vector&& v) 
            {
                _size = v._size;
                _capacity = v._capacity;
                _data = v._data;
                v._data = nullptr;
                v._size = 0;
                v._capacity = 1;
                std::cout << "Move constructor\n";
            }

            // kopiujący operator przypisania
            vector& operator=(const vector& v)
            {
                if (this != &v) 
                {
                    delete[] _data;
                    _size = v._size;
                    _capacity = v._capacity;
                    _data = new T[_capacity];
                    for (int i = 0; i < _capacity; i++)
                    {
                        _data[i] = v._data[i];
                    }
                }
                std::cout << "Copy assignment\n";
                return *this;
            }

            // przenoszący operator przypisania
            vector& operator=(vector&& v) 
            {
                if (this != &v) 
                {
                    delete[] _data;
                    _size = v._size;
                    _capacity = v._capacity;
                    _data = v._data;
                    v._data = nullptr;
                    v._size = 0;
                    v._capacity = 1;
                }
                std::cout << "Move assignment\n";
                return *this;
            }

            // destruktor
            ~vector() 
            {
                delete[] _data;
                std::cout << "Destructor\n";
            }

            // nowy element na końcu
            void pushBack(T element)
            {
                if (_size == _capacity) 
                {
                    T* newData = new T[2*_capacity];
                    for (int i = 0; i < _capacity; i++)
                    {
                        newData[i] = _data[i];
                    }
                    delete[] _data;
                    _data = newData;
                    _capacity *= 2;
                }
                _data[_size] = element;
                _size++;
            }

            // wydruk zawartości wektora
            void printVector()
            {
                std::cout << "[ ";
                for (int i = 0; i<_size; i++) 
                {
                    std::cout << _data[i] << " ";
                }
                std::cout << "]" << std::endl;
            }

            // usunięcie elementu z końca
            void popBack()
            {
                if (_size == 0) 
                {
                    throw std::logic_error("Brak elementów do usunięcia.");
                }
                _size--;
            }

            // odczyt i edycja elementu o indeksie
            T& operator[](int index)
            {
                if ( (index < 0) || (index >= _size) ) {
                    throw std::logic_error("Indeks poza zakresem.");
                }
                return _data[index];
            }

            // zwrot rozmiaru
            int size()
            {
                return _size;
            }
    };

    // Zadanie 1
    template<typename T>
    concept Numeric = std::is_arithmetic_v<T>;

    template<typename T>
    concept NumericVector = requires(typename T::value_type x, T v) 
    {
        { x + x } -> Numeric;
        { v.size() } -> std::convertible_to<size_t>;
        { v[0] } -> std::convertible_to<typename T::value_type>;
    };

    template<NumericVector T1, NumericVector T2>
    double operator*(T1& first, T2& second) 
    {
        if ((first.size() != second.size()) || second.size() == 0) 
        {
            throw std::logic_error("Niezgodne wymiary.");
        }
        double dot = 0;
        for (int i = 0; i < first.size(); i++)
        {
            dot += first[i]*second[i];
        }
        return dot;
    }

    class someType
    {
        public:
            int a;
            someType() {
                a = 1;
            }
            someType(int x) {
                a = x;
            }
    };
    
}
