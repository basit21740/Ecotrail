// Include necessary libraries
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// Define constants
#define WIDTH 800
#define HEIGHT 600
#define FPS 60
#define MAX_LENGTH 100

// Define structures
struct Point {
    int x;
    int y;
};

struct Snake {
    int length;
    int direction;
    struct Point body[MAX_LENGTH];
};

struct Item {
    char name[50];
    int effect; // Positive or negative effect on the snake
    struct Point position;
};

// Function prototypes
void initializeGame();
void renderGame();
void handleInput();
void updateGame();
void readItemsFromFile(char* Assets);

// Other variables
int gameOver = 0;
struct Snake snake;
struct Item items[MAX_LENGTH];
int numItems = 0;

int main() {
    // Initialize Allegro
    if (!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro!\n");
        return -1;
    }

    // Initialize add-ons
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // Create display
    ALLEGRO_DISPLAY *display = al_create_display(WIDTH, HEIGHT);
    if (!display) {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }

    // Create event queue
    ALLEGRO_EVENT_QUEUE *eventQueue = al_create_event_queue();
    if (!eventQueue) {
        fprintf(stderr, "Failed to create event queue!\n");
        al_destroy_display(display);
        return -1;
    }

    // Register event sources
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());

    // Set up game
    initializeGame();
    // readItemsFromFile("items.txt"); // Commented out to simplify

    // Game loop
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    al_start_timer(timer);

    while (!gameOver) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventQueue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            handleInput();
            updateGame();
            renderGame();
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            gameOver = 1;
        }
    }

    // Cleanup and exit
    al_destroy_timer(timer);
    al_destroy_event_queue(eventQueue);
    al_destroy_display(display);
    return 0;
}

// Function definitions

void initializeGame() {
    // Set initial snake state
    snake.length = 1;
    snake.direction = ALLEGRO_KEY_RIGHT;
    snake.body[0].x = WIDTH / 2;
    snake.body[0].y = HEIGHT / 2;

    // Set up initial items
    numItems = 0;

    // Additional initialization logic as needed
}

void renderGame() {
    // Clear the screen to a background color
    al_clear_to_color(al_map_rgb(0, 0, 0)); // Black background

    // Render the snake
    for (int i = 0; i < snake.length; ++i) {
        al_draw_filled_rectangle(
            snake.body[i].x * WIDTH / MAX_LENGTH,
            snake.body[i].y * HEIGHT / MAX_LENGTH,
            (snake.body[i].x + 1) * WIDTH / MAX_LENGTH,
            (snake.body[i].y + 1) * HEIGHT / MAX_LENGTH,
            al_map_rgb(0, 255, 0) // Snake color is green
        );
    }

    // Render the items
    for (int i = 0; i < numItems; ++i) {
        al_draw_filled_circle(
            items[i].position.x * WIDTH / MAX_LENGTH,
            items[i].position.y * HEIGHT / MAX_LENGTH,
            10, // Adjust the size of the items
            al_map_rgb(255, 0, 0) // Item color is red
        );
    }

    // Flip the display to show the updated frame
    al_flip_display();
}

void handleInput() {
    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);

    if (al_key_down(&keyState, ALLEGRO_KEY_UP) && snake.direction != ALLEGRO_KEY_DOWN) {
        snake.direction = ALLEGRO_KEY_UP;
    } else if (al_key_down(&keyState, ALLEGRO_KEY_DOWN) && snake.direction != ALLEGRO_KEY_UP) {
        snake.direction = ALLEGRO_KEY_DOWN;
    } else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT) && snake.direction != ALLEGRO_KEY_RIGHT) {
        snake.direction = ALLEGRO_KEY_LEFT;
    } else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT) && snake.direction != ALLEGRO_KEY_LEFT) {
        snake.direction = ALLEGRO_KEY_RIGHT;
    }
}

void updateGame() {
    // Update snake position based on direction
    for (int i = snake.length - 1; i > 0; --i) {
        snake.body[i] = snake.body[i - 1];
    }

    switch (snake.direction) {
        case ALLEGRO_KEY_UP:
            snake.body[0].y--;
            break;
        case ALLEGRO_KEY_DOWN:
            snake.body[0].y++;
            break;
        case ALLEGRO_KEY_LEFT:
            snake.body[0].x--;
            break;
        case ALLEGRO_KEY_RIGHT:
            snake.body[0].x++;
            break;
    }
}

void readItemsFromFile(char*Assets) {
    // Will read from file here
}
