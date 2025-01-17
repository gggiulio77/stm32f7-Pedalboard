#include "gui/prototipos.h"
#include "main.h"

// parametros de desarrollador
#define DELAY_SIZE 50000

static int32_t salida = 0;

// parametros de usuario
static float32_t level = 0.5f, feedback = 0.0f;
static int32_t time = 20000;

// variables auxiliares
static volatile int32_t *line = (int32_t *)(AUDIO_DELAY_BUFFER);
static int32_t cont = 0, flag = 0;
//static int32_t line[DELAY_SIZE]={0}, cont = 0, flag = 0;

void delayInit() {
    delayParametros();
}

void delayParametros() {
}

int32_t delayEfecto(int32_t entrada) {
    if (cont == DELAY_SIZE) {
        flag = 1;
        cont = 0;
    }

    if (flag == 0) {
        line[cont] = entrada * (1.0f - feedback);
        salida = entrada * (1.0f - level);
        cont++;
    }

    if (flag == 1) {
        if (cont >= time) {
            line[cont] = entrada * (1.0f - feedback) + line[cont - time] * feedback;
            salida = entrada * (1.0f - level) + line[cont - time] * level;
        } else {
            line[cont] = entrada * (1.0f - feedback) + line[DELAY_SIZE + cont - time] * feedback;
            salida = entrada * (1.0f - level) + line[DELAY_SIZE + cont - time] * level;
        }

        cont++;
    }

    return (2 * salida);
}

void delayTime(GUIElement *e) {
    DialButtonState *db = (DialButtonState *)(e->userData);

    time = (int32_t)((DELAY_SIZE - 1) * (db->value));
}

void delayFeedback(GUIElement *e) {
    DialButtonState *db = (DialButtonState *)(e->userData);

    feedback = (db->value);
}

void delayLevel(GUIElement *e) {
    DialButtonState *db = (DialButtonState *)(e->userData);

    level = (db->value);
}
