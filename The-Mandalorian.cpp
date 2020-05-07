#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>

using namespace std;

// allegro vars
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;

// allegro bitmaps
ALLEGRO_BITMAP* testcharacter = NULL;

int heroX = 0;
int heroY = 0;

const float FPS = 1;

int draw() {    
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(testcharacter, heroX, heroY, 0);
    al_flip_display();
    return 0;
}

int main (int argc, char *argv[])
{
    // initialize allegro screen
    al_init();
    al_init_image_addon();
    al_install_mouse();

    al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
    display = al_create_display(1080, 640);
    al_set_window_title(display, "The Mandalorian");

    // load images
    testcharacter = al_load_bitmap("testcharacter.png");

    timer = al_create_timer(1.0/FPS);
    al_start_timer(timer);

    event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    bool running = true;

    while (running) {
        ALLEGRO_EVENT event;
        ALLEGRO_TIMEOUT timeout;

        al_init_timeout(&timeout, 1.0/FPS);

        al_wait_for_event_until(event_queue, &event, &timeout);

        switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            running = false;
            break;
        case ALLEGRO_EVENT_TIMER:
            draw();
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            if (event.mouse.button == 1) {
                heroX = event.mouse.x;
                heroY = event.mouse.y;
            }
            break;
        }
    }

    return 0;
}