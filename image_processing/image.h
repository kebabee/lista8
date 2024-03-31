/*
Objaśnienie funkcji:
    1. void save_as(const std::string& filename);
        Zapisuje obrazek w pliku o podanej nazwie. To jest pierwsza funkcja składowa, którą należy
    2. void add_watermark();
        Dodaje do obrazka „znak wodny”, coś prostego, ale widocznego.
    3. void blurr();
        Zmiękcza obrazek poprzez zastąpienie wartości składowych kolorów ich średnią z tego piksela i sąsiedztwa Moore'a
    4. void extract_layer(ColorLayer color_layer);
        Zamienia obrazek na jedną z trzech warstw odpowiadających palecie RGB. Czyli zeruje dwie składowe koloru, a trzecią pozostawia bez zmian.
    5. void filter();
        „Magiczny filtr” polega na zastąpieniu wartości składowych kolorów piksela (x, y) wartościami bezwzględnymi różnic tych składowych w pozycji (x, y) i (x+1, y+1). 
    6. void flip_horizontally();
        Odwróć obrazek w poziomie
    7. void flip_vertically();
        Odwróć obrazek w pionie
    8. void inflate();
        Powiększ obrazek 2 razy. Tam, gdzie w oryginale jest piksel (x, y), tam w powiększeniu jest grupa 4 identycznych pikseli tworzących kwadrat o wierzchołku (2x, 2y).
    9. void negative();
        Zastąp obrazek jego negatywem.
    10. void rotate_clockwise_90();
        Obróć obrazek o 90 stopni w kierunku obrotu wskazówek zegara.
    11. void sepia();
        Zamień obrazek na odcienie szarości, a następnie nadaj mu odcień sepii.
    12. void shrink();
        Operacja odwrotna do inflate(), czyli zmniejszamy rozmiar obrazka o czynnik 2. Do piksela (x.y) wpisujemy średnią arytmetyczną, w każdym kanale kolorów liczoną osobno, 
        z wartości koloru w czterech sąsiednich pikselach oryginału.
    13. void to_grayscale();
        Zamień (kolorowy) obrazek na obrazek w kolorach szarości, do każdej składowej średnia arytmetyczna pierwotnych wartości koloru.
    14. int height() const;
        Po prostu zwraca wysokość obrazka.
    15. int width() const;
        Po prostu zwraca szerokość obrazka.
*/

#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include <vector>

struct RGB
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

enum class ColorLayer
{
    Red,
    Green,
    Blue
};

class Image
{
  public:
    void load(const std::string& filename);
    int height() const {
      return my_height;
    };
    int width() const {
      return my_width;
    };

    void save_as(const std::string& filename);
    void add_watermark();
    void blurr();
    void extract_layer(ColorLayer color_layer);
    void filter();
    void flip_horizontally();
    void flip_vertically();
    void inflate();
    void negative();
    void rotate_clockwise_90();
    void sepia();
    void shrink();
    void to_grayscale();

  private:
    std::vector<std::vector<RGB>> pixels;
    int my_width{0};
    int my_height{0};
    int color_depth{0};
    std::string magic;
    std::string filename;
};

#endif  // IMAGE_H
