#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

//allegro vars
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;

const float FPS = 1;

int draw() {                                                                                                            
    return 0;
}

int main (int argc, char *argv[])
{
    // initialize allegro screen
    al_init();

    display = al_create_display(1080, 640);

    timer = al_create_timer(1.0/FPS);
    al_start_timer(timer);

    event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    
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
        }
    }

    return 0;
}