
#include <stdio.h>
#include <stdlib.h>
/* Used internally in nuklear.h */
#include <math.h>

#define NK_IMPLEMENTATION
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_FONT_BAKING
#include <nuklear.h>

#include "main.h"

enum difficulty{EASY, HARD};

int main(const int argc, char *const *argv)
{
    /* Process command-line args */
    enum CmdlineCode exit_code = process_cmdline_args(argc, argv);

    /* Triggered 'help' message */
    if (exit_code == CMDLINE_HELP) return EXIT_SUCCESS;
    /* Processing failed */
    else if (exit_code == CMDLINE_ERROR) {
        log_message("Processing command-line arguments failed. Exiting!", APP_LOG_ERROR);
        return EXIT_FAILURE;
    }

    /* TODO: Create a font atlas and add a font */
    struct nk_font_atlas atlas;

    nk_font_atlas_init_default(&atlas);
    nk_font_atlas_begin(&atlas);
    nk_font *font = nk_font_atlas_add_from_file(&atlas, "Path/To/Your/TTF_Font.ttf", 13, 0);
    nk_font_atlas_bake(&atlas, &img_width, &img_height, NK_FONT_ATLAS_RGBA32);
    nk_font_atlas_end(&atlas, NULL, 0);

        struct nk_context ctx;
        nk_init_default(&ctx, &font->handle);
        while (1) {

        }

    /* Init gui state */
    enum difficulty op = EASY;
    float value = 0.6f;
    struct nk_context ctx;

    /* Init gui */
    /* NOTE: Use 'nk_init_fixed' with a fixed-size memory block for better memory control */
    nk_init_default(&ctx, &font);

    /* Set font */
    nk_style_set_font(&ctx, &font);

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

    /* Free memory used by the atlas and attached fonts */
    nk_font_atlas_clear(&atlas);

    /* Free memory used by nuklear context */
    nk_clear(&ctx);

    /* Stop GUI */
    nk_end(&ctx);

    return EXIT_SUCCESS;
}