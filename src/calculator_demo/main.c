
#include <stdio.h>
#include <stdlib.h>
/* Used internally in nuklear.h */
#include <math.h>

#define NK_IMPLEMENTATION
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include <nuklear.h>

#include "main.h"

void usage();
int process_cmdline_args(const int, char *const *);
void log_message(const char*, const short);

enum difficulty{EASY, HARD};

int main(const int argc, char *const *argv)
{
    int exit_code = 0;

    exit_code = process_cmdline_args(argc, argv);

    /* Triggered 'help' message */
    if (exit_code == 1) return EXIT_SUCCESS;
    else if (exit_code == -1) {
        log_message("Processing command-line arguments failed. Exiting!", -1);
        return EXIT_FAILURE;
    }

    /* Init gui state */
    enum difficulty op = EASY;
    float value = 0.6f;
    struct nk_context ctx;
    /* TODO: Font needs to be loaded */
    struct nk_user_font font;

    /* Init gui */
    /* NOTE: Use 'nk_init_fixed' with a fixed-size memory block for better memory control */
    nk_init_default(&ctx, &font);

    /* Start GUI */
    if (nk_begin(&ctx, "Show", nk_rect(50, 50, 220, 220), NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE)) {
        /* Fixed widget with 1 pixel width */
        nk_layout_row_static(&ctx, 30, 80, 1);
        if ( nk_button_label(&ctx, "button") ) {
            /* Handle button events */
        }
        /* Fixed widget window with ratio width */
        nk_layout_row_dynamic(&ctx, 30, 2);
        if (nk_option_label(&ctx, "easy", op == EASY)) op = EASY;
        if (nk_option_label(&ctx, "hard", op == HARD)) op = HARD;

        /* Custom widget with 1 pixel width */
        nk_layout_row_begin(&ctx, NK_STATIC, 30, 2);
        {
            nk_layout_row_push(&ctx, 50);
            nk_label(&ctx, "Volume:", NK_TEXT_LEFT);
            nk_layout_row_push(&ctx, 110);
            nk_slider_float(&ctx, 0, &value, 1.0f, 0.1f);
        }
        nk_layout_row_end(&ctx);
    }

    /* Free memory used by nuklear context */
    nk_clear(&ctx);

    /* Stop GUI */
    nk_end(&ctx);

    return EXIT_SUCCESS;
}