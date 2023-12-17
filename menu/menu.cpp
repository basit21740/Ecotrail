#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main() {
    al_init(); // Initialize Allegro
    al_install_keyboard(); // Initialize keyboard routines
    al_init_font_addon(); // Initialize the font addon
    al_init_ttf_addon(); // Initialize the ttf (True Type Font) addon

    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT); // Create display
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue(); // Create event queue
    ALLEGRO_FONT *font = al_load_ttf_font("your_font.ttf", 36, 0); // Load your font

    if (!font) {
        al_show_native_message_box(display, "Error", "Error", "Could not load 'your_font.ttf'.", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    bool running = true;
    bool redraw = true;

    ALLEGRO_EVENT event;

    while (running) {
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            al_clear_to_color(al_map_rgb(0, 150, 0)); // Set background color
            al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, ALLEGRO_ALIGN_CENTRE, "Play");
            al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Options");
            al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 3 * SCREEN_HEIGHT / 4, ALLEGRO_ALIGN_CENTRE, "Quit");

            al_flip_display(); // Flip the backbuffer to the display
            redraw = false;
        }
    }

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
