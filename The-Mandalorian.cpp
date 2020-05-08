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
ALLEGRO_BITMAP* battleground = NULL;

int heroX = 0;
int heroY = 0;
int heroDestinationX = 0;
int heroDestinationY = 0;
int heromovespeed = 3;
int mapPos = 0;

char moving = 's';

const float FPS = 60;

int draw() {
    al_draw_bitmap(battleground, mapPos, 0, 0);
    al_draw_bitmap(testcharacter, heroX + mapPos, heroY, 0);
    al_flip_display();
    return 0;
}

int main (int argc, char *argv[])
{
    // initialize allegro screen
    al_init();
    al_init_image_addon();
    al_install_mouse();
    al_install_keyboard();

    al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
    display = al_create_display(1080, 720);
    al_set_window_title(display, "The Mandalorian");

    // load images
    testcharacter = al_load_bitmap("testcharacter.png");
    battleground = al_load_bitmap("battleground.png");

    timer = al_create_timer(1.0/FPS);
    al_start_timer(timer);

    event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());

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
            if (heroX <= heroDestinationX - heromovespeed || heroX >= heroDestinationX + heromovespeed) {
                if (heroX > heroDestinationX) {
                    heroX -= heromovespeed;
                }
                else {
                    heroX += heromovespeed;
                }
            }
            if (heroY <= heroDestinationY - heromovespeed || heroY >= heroDestinationY + heromovespeed) {
                if (heroY > heroDestinationY) {
                    heroY -= heromovespeed;
                }
                else {
                    heroY += heromovespeed;
                }
            }
            switch (moving) {
            case 'f':
                mapPos -= 2;
                break;
            case 'b':
                mapPos += 2;
                break;
            }
            draw();
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP: 
            if (event.mouse.button == 1) {
                    heroDestinationX = event.mouse.x;
                    heroDestinationY = event.mouse.y;
                    break;
            }
        case ALLEGRO_EVENT_KEY_DOWN:
            switch(event.keyboard.keycode){
            case ALLEGRO_KEY_RIGHT:
                moving = 'f';
                break;
            case ALLEGRO_KEY_LEFT:
                moving = 'b';
                break;
            }
            break;
        case ALLEGRO_EVENT_KEY_UP:
            moving = 's';
            break;
        }
    }

    return 0;
}