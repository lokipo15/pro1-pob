#include <QApplication>
#include "GameWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Tworzenie instancji aplikacji Qt
    // Tworzenie i wyświetlanie głównego okna gry
    GameWindow window;
    window.show();

    return app.exec(); // Uruchomienie głównej pętli aplikacji
}
