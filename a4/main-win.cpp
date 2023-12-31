// #define ALLEGRO_NO_MAGIC_MAIN
// #include <allegro.h>

// https://www.allegro.cc/manual/4/

/**
CC=i686-w64-mingw32-g++
CC=g++
$CC main-win.cpp -o main-win --static `pkg-config --libs --cflags --static allegro`

$CC main-win.cpp -o main-win -lalleg -L _deps/allegro4-build/lib
*/
#define ALLEGRO_STATICLINK
#include <allegro.h>
void init();
void deinit();
int main(int argc, char **argv)
{
    init();

    FONT *font = load_font("font_10.pcx", NULL, NULL);

    while (!key[KEY_ESC])
    { /*Enquanto a tecla ESC não for pressionada, irá executar o código especificado */
        /* Código a ser executado */
        textprintf_ex(screen, font, 0, 0, makecol(255, 100, 200), -1, "Hello world");
    }
    deinit();
    return 0;
}
END_OF_MAIN() /* Macro necessária para o funcionamento da Allegro
Sempre deve ser utilizada no final da função main*/

void init()
{
    allegro_init();                /* Inicializa a Allegro */
    int depth = desktop_color_depth(); /* Retorna a profundidade de cores usadas no
    Desktop */
    if (depth == 0)
        depth = 32;
    set_color_depth(depth); /* Define a profundidade de cor que será usada */
    /* Seleciona o modo gráfico a ser exibido
    Neste caso, será em janela (poderia ser FullScreen, por exemplo), com
    tamanho 640 x 480 */
    int res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    if (res != 0)
    {
        allegro_message("%s", allegro_error); /* Exibe mensagem em caso de erro */
        exit(-1);
    }
    install_timer();    /* Instala o handler de tempo da Allegro */
    install_keyboard(); /* Instala o handler de teclado da Allegro */
    install_mouse();    /* Instala o handler de mouse da Allegro */
    /* Outras possíveis inicializações */
}
void deinit()
{
    clear_keybuf(); /* Limpa o buffer do teclado */
    /* Outras possíveis desinicializações */
}