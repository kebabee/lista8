#include "nonstd_vector.h"

int main () 
{
    try 
    {
        // Zadanie 1
        cpplab::vector<double> intVector1(1.1);
        intVector1.pushBack(2.2);
        intVector1.pushBack(3.3);
        intVector1.printVector();
        std::cout << "\n";

        // kopiowanie
        cpplab::vector<double> intVector2(intVector1);
        intVector1.pushBack(4.4);
        cpplab::vector<double> intVector3;
        intVector3 = intVector1;
        intVector1.printVector();
        intVector2.printVector();
        intVector3.printVector();
        std::cout << "\n";

        // przenoszenie
        intVector3 = std::move(intVector2);
        cpplab::vector<double> intVector4 = std::move(intVector1);
        cpplab::vector<double> intVector5 = cpplab::vector<double>(1.1);
        intVector1.printVector();
        intVector2.printVector();
        intVector3.printVector();
        intVector4.printVector();
        intVector5.printVector();
        std::cout << "\n";

        // pix
        cpplab::vector<cpplab::pixel> pixelVector;
        pixelVector.emplaceBack(1, 2, 3);
        pixelVector.emplaceBack(4, 5, 6);
        pixelVector[0].printPixel();
        pixelVector[1].printPixel();
        std::cout << "\n";


        cpplab::vector<int> v1(2);
        v1.pushBack(2);
        cpplab::vector<double> v2(1.0);
        v2.pushBack(5.0);
        std::vector<float> v3 = {8.0f, 4.0f};
        cpplab::vector<std::string> v4("aaa");
        cpplab::vector<cpplab::someType> v5;
        v5.pushBack(cpplab::someType(1));
        std::string a = "ssssss";

        std::cout << "(2, 2) * (2, 2) = " << v1*v1 << "\n";
        std::cout << "(2, 2) * (1.0, 5.0) = " << v1*v2 << "\n";
        std::cout << "(1.0, 5.0) * (8.0f, 4.0f) = " << v2*v3 << "\n";
        // std::cout << v4*v4 << "\n"; // <- no operator "*" matches these operands
        // std::cout << v5*v5 << "\n"; // <- no operator "*" matches these operands

    } 
    catch (std::logic_error& e)
    {
        std::cout << e.what() << "\n";
    }
    catch (...)
    {
        std::cout << "Nieznany błąd." << "\n";
    }

    return 0;
}
