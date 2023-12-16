#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <cstdlib>
#include <ctime>
#include <allegro5/allegro_font.h>

const int SCREEN_W = 640;       // screen width
const int SCREEN_H = 480;       // screen height
const int WIDTH = 800;
const int HEIGHT = 600;

#define SLATEGREY   al_map_rgb(112, 128, 144)

ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_BITMAP *snakeHeadImage = nullptr;
ALLEGRO_BITMAP *oilImage= nullptr;
ALLEGRO_BITMAP *treeImage= nullptr;
ALLEGRO_BITMAP *grassImage = nullptr;
ALLEGRO_FONT *font = nullptr;

ALLEGRO_EVENT_QUEUE *event_queue = nullptr;  // Add event queue object

//Declare
bool movingUp = false;
bool movingDown = false;
bool movingLeft = false;
bool movingRight = false;
int score = 0;  // Variable to keep track of the score

void showError(const char *message) {
    al_show_native_message_box(display, "Error", "Error", message, nullptr, ALLEGRO_MESSAGEBOX_ERROR);
}


void renderGame(int dx, int dy, int treeX, int treeY, int oilX, int oilY) {
    al_clear_to_color(al_map_rgb(0, 0, 0));  // Clear to black (or any desired background color)

    // Draw the grass background
    al_draw_bitmap(grassImage, 0, 0, 0);

    // Draw other images on top of the grass background
    al_draw_bitmap(snakeHeadImage, dx, dy, 0);
    al_draw_bitmap(oilImage, oilX, oilY, 0);
    al_draw_bitmap(treeImage, treeX, treeY, 0);

    // Draw the score on the screen
    al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 10, 0, "Score: %d", score);

    al_flip_display();
}



void handleInput(ALLEGRO_EVENT &ev) {
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        // Update direction based on the key pressed
        switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                movingUp = true;
                movingDown = false;
                movingLeft = false;
                movingRight = false;
                break;
            case ALLEGRO_KEY_DOWN:
                movingUp = false;
                movingDown = true;
                movingLeft = false;
                movingRight = false;
                break;
            case ALLEGRO_KEY_LEFT:
                movingUp = false;
                movingDown = false;
                movingLeft = true;
                movingRight = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                movingUp = false;
                movingDown = false;
                movingLeft = false;
                movingRight = true;
                break;
            case ALLEGRO_KEY_ESCAPE:
                // Escape key code
                break;
        }
    }
}

void renderGame(int dx, int dy, int treeX, int treeY, int oilX, int oilY);



int main(int argc, char *argv[]) {
    // Initialize Allegro
    if (!al_init()) {
        showError("Failed to initialize Allegro!");
        return -1;
    }

    // Initialize display
    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        showError("Failed to initialize display!");
        return -1;
    }
    al_set_window_title(display, "Allegro Example - Displaying Images");

    // Initialize keyboard routines
    if (!al_install_keyboard()) {
        al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!", nullptr,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // need to add image processor
    if (!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!", nullptr,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    // set up event queue
    event_queue = al_create_event_queue();
    if (!event_queue) {
        al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!", nullptr,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -1;
    }

    // need to register events for our event queue
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());


    // Need to add font addon initialization
    if (!al_init_font_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_font_addon!", nullptr,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }


    // Load the grass image
    grassImage = al_load_bitmap("grass.png");
    if (!grassImage) {
        showError("Failed to load grass.png!");
        // Handle the error and return if necessary
    }

  // Seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr)));


    // Load the bitmaps
    //Snake
    snakeHeadImage = al_load_bitmap("snakehead.png");
    if (!snakeHeadImage) {
        showError("Failed to load snakehead.png!");
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return -1;
    }

   treeImage = al_load_bitmap("tree.png");
    if (!snakeHeadImage) {
        showError("Failed to load tree.png!");
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return -1;
    }


    oilImage = al_load_bitmap("oil.png");
    if (!snakeHeadImage) {
        showError("Failed to load oil.png!");
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return -1;
    }

    // Create a bitmap and load the image
    ALLEGRO_BITMAP *ball = nullptr;
    ball = al_load_bitmap("snakehead.png");

    // Display the snake head image
    al_draw_bitmap(snakeHeadImage, 0, 0, 0);

    // Write display to screen
    al_flip_display();

       // Need to create a font for text drawing
    font = al_create_builtin_font();


   // Game loop
    int dx = 100;
    int dy = 100;
    int treeX = rand() % (SCREEN_W - al_get_bitmap_width(treeImage));
    int treeY = rand() % (SCREEN_H - al_get_bitmap_height(treeImage));
    int oilX = rand() % (SCREEN_W - al_get_bitmap_width(oilImage));
    int oilY = rand() % (SCREEN_H - al_get_bitmap_height(oilImage));

      // Need to create a font for text drawing
    ALLEGRO_FONT *font = al_create_builtin_font();


    al_clear_to_color(SLATEGREY);
    al_draw_bitmap(snakeHeadImage, dx, dy, 0);
    al_draw_bitmap(oilImage, oilX, oilY, 0);
    al_draw_bitmap(treeImage, treeX, treeY, 0);
    al_flip_display();

    // Draw the score on the screen
    al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 10, 0, "Score: %d", score);


    bool doexit = false;
    while (!doexit) {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) {
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                doexit = true;
            } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
                handleInput(ev);
            }
        }

        // Move the image
        if (movingUp) {
            dy -= 8;
        } else if (movingDown) {
            dy += 8;
        } else if (movingLeft) {
            dx -= 8;
        } else if (movingRight) {
            dx += 8;
        }

        // Check for boundary conditions
        if (dx < 0 || dx > SCREEN_W - al_get_bitmap_width(snakeHeadImage) ||
            dy < 0 || dy > SCREEN_H - al_get_bitmap_height(snakeHeadImage)) {
            // Image hit the boundary, trigger game over
            al_show_native_message_box(display, "Game Over", "Game Over", "You hit the boundary!", nullptr,
                                       ALLEGRO_MESSAGEBOX_ERROR);
            doexit = true;
        }

        // Check for collision with oil
        if (dx < oilX + al_get_bitmap_width(oilImage) &&
            dx + al_get_bitmap_width(snakeHeadImage) > oilX &&
            dy < oilY + al_get_bitmap_height(oilImage) &&
            dy + al_get_bitmap_height(snakeHeadImage) > oilY) {
            // Collision with oil, decrease score and reset oil position
            score--;
            oilX = rand() % (SCREEN_W - al_get_bitmap_width(oilImage));
            oilY = rand() % (SCREEN_H - al_get_bitmap_height(oilImage));
        }

        // Check for collision with tree
        if (dx < treeX + al_get_bitmap_width(treeImage) &&
            dx + al_get_bitmap_width(snakeHeadImage) > treeX &&
            dy < treeY + al_get_bitmap_height(treeImage) &&
            dy + al_get_bitmap_height(snakeHeadImage) > treeY) {
            // Collision with tree, increase score and reset tree position
            score++;
            treeX = rand() % (SCREEN_W - al_get_bitmap_width(treeImage));
            treeY = rand() % (SCREEN_H - al_get_bitmap_height(treeImage));
        }

        al_rest(0.07);
        renderGame(dx, dy, treeX, treeY, oilX, oilY);

        if (score==-1){
                  al_show_native_message_box(display, "Game Over", "Game Over", "Your score is too low!", nullptr,
                                       ALLEGRO_MESSAGEBOX_ERROR);
                                       score = 0;
                                        doexit = true;
        }

    }

    // Release the bitmap data and exit with no errors
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
      al_destroy_font(font);

    return 0;
}

void initializeGame() {
    // Initialize game state
}

void updateGame() {
    // Update game state
}
