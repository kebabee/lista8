#include "nonstd_unique_ptr.h"

int main() 
{
    try
    {
        cpplab::unique_ptr<int> ptr1(new int(1));
        cpplab::unique_ptr<int> ptr2(new int(1));
        cpplab::unique_ptr<int> ptr3(std::move(ptr1));
        cpplab::unique_ptr<int> ptr4 = std::move(ptr2);
        cpplab::unique_ptr<int> ptr5(ptr2);
        cpplab::unique_ptr<int> ptr6 = ptr2;

        ptr3.reset(new int(2));

        if (!ptr1) std::cout << "ptr1 jest pusty\n";
        if (!ptr2) std::cout << "ptr2 jest pusty\n";
        if (ptr3) std::cout << "ptr3 nie jest pusty\n";
        if (ptr4) std::cout << "ptr4 nie jest pusty\n";
        if (!ptr5) std::cout << "ptr5 jest pusty\n";
        if (!ptr6) std::cout << "ptr6 jest pusty\n";

        std::cout << "Czy równe? " << (ptr3 == ptr4) << "\n";
        std::cout << "*ptr3 = " << *ptr3 << ", *ptr4 = " << *ptr4 << "\n";

        ptr3.swap(ptr4);
        std::cout << "Po swap: *ptr3 = " << *ptr3 << ", *ptr4 = " << *ptr4 << "\n";

        std::cout << "Adres ptr3: "<< ptr3.get() << "\n";

        ptr3.release();
        if (!ptr3) std::cout << "ptr3 jest pusty\n";

        // testy dla tablicy
        cpplab::unique_ptr<double[]> arrayPtr(new double[5]);
        cpplab::unique_ptr<double[]> arrayPtr2 = std::move(arrayPtr);

        for (int i = 0; i < 5; i++) arrayPtr2[i] = 10.0*i;

        std::cout << "\nZawartość tablicy: ";
        for (int i = 0; i < 5; ++i) std::cout << arrayPtr2[i] << " ";
        std::cout << "\n";

        std::cout << "Adres arrayPtr: " << arrayPtr2.get() << "\n";
        std::cout << *arrayPtr2 << "\n";

        arrayPtr2.reset(new double[2]);
        arrayPtr2.release();

        cpplab::non0_ptr<int> ptr(new int(42));
        cpplab::non0_ptr<int> ptrr(nullptr);
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << e.what() << '\n';
    }

    return 0;
}
