#include "UI.hpp"

int main(){
    UI ui(800, 600);
    RGB_color color("#FF0000");
    position pos(0, 0);
    // using easyx to load an image named "test.jpg"
    ui.draw_image("../assets/image.jpg", {0,100}, {200, 200});
    ui.update();
    system("pause");
    return 0;
}