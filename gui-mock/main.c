#include <math.h>
#include <stddef.h>
#include <stdio.h>

#include "raygui.h"
#include "raylib.h"

typedef struct oscillator1 {
    int wav;
    float pw;
} oscillator1_t;

typedef struct oscillator2 {
    int wav;
    float pw;
    int pitch, cent;
    float pitch_, cent_;
} oscillator2_t;

typedef struct modulator {
    int type;
    float depth;
} modulator_t;

typedef struct amplifier {
    float a, d, s, r;
    float gain;
} amplifier_t;

typedef struct filter {
    float a, d, s, r;
    float cut, res;
    int pass, db;
} filter_t;

typedef struct lfo {
    int wav;
    int dst;
    float spd;
    float amt;
    bool osc1, osc2;
} lfo_t;

typedef struct equalizer {
    float low;
    float mid;
    float hi;
} equalizer_t;

static float clampf(float value, float min, float max) {
    if (value > max) return max;
    if (value < min) return min;
    return value;
}

static void GuiOscillator1(int x, int y, oscillator1_t *osc1, oscillator2_t *osc2) {
    GuiGroupBox((Rectangle){x, y, 145, 45}, "Oscillator1");
    GuiToggleGroup(
        (Rectangle){x + 10, y + 10, 25, 10},
        "sin;saw;tri;sqr;nos",
        &osc1->wav
    );
    GuiSliderBar((Rectangle){x + 10, y + 25, 60, 10}, "", "p/w", &osc1->pw, 0.0f, 64.0f);
    if (GuiButton((Rectangle){x + 100, y + 25, 35, 10}, "sync")) osc1->pw = osc2->pw;
}

static void GuiOscillator2(int x, int y, oscillator2_t *osc2, oscillator1_t *osc1) {
    static char buf[1024];
    GuiGroupBox((Rectangle){x, y, 145, 75}, "Oscillator2");

    GuiToggleGroup(
        (Rectangle){x + 10, y + 10, 25, 10},
        "sin;saw;tri;sqr;nos",
        &osc2->wav
    );

    GuiSliderBar((Rectangle){x + 10, y + 25, 60, 10}, "", "p/w", &osc2->pw, 0.0f, 64.0f);
    if (GuiButton((Rectangle){x + 100, y + 25, 35, 10}, "sync")) osc2->pw = osc1->pw;

    GuiSliderBar(
        (Rectangle){x + 10, y + 40, 60, 10},
        "",
        "pitch",
        &osc2->pitch_,
        -12.0f,
        12.0f
    );

    if (GuiButton((Rectangle){x + 115, y + 40, 10, 10}, "")) osc2->pitch_ -= 1.0f;
    if (GuiButton((Rectangle){x + 125, y + 40, 10, 10}, "")) osc2->pitch_ += 1.0f;

    osc2->pitch_ = floorf(clampf(osc2->pitch_, -12.0f, 12.0f));
    osc2->pitch = osc2->pitch_;

    snprintf(buf, 1024, "%d", osc2->pitch);
    GuiLabel((Rectangle){x + 100, y + 40, 35, 10}, buf);

    GuiSliderBar(
        (Rectangle){x + 10, y + 55, 60, 10},
        "",
        "cent",
        &osc2->cent_,
        -64.0f,
        64.0f
    );

    if (GuiButton((Rectangle){x + 115, y + 55, 10, 10}, "")) osc2->cent_ -= 1.0f;
    if (GuiButton((Rectangle){x + 125, y + 55, 10, 10}, "")) osc2->cent_ += 1.0f;

    osc2->cent_ = floorf(clampf(osc2->cent_, -64.0f, 64.0f));
    osc2->cent = (int)osc2->cent_;

    snprintf(buf, 1024, "%d", osc2->cent);
    GuiLabel((Rectangle){x + 100, y + 55, 35, 10}, buf);
}

static void GuiModulator(int x, int y, modulator_t *mod) {
    GuiGroupBox((Rectangle){x, y, 145, 45}, "Modulator");
    GuiToggleGroup((Rectangle){x + 10, y + 10, 25, 10}, "fm;am", &mod->type);
    GuiSliderBar(
        (Rectangle){x + 10, y + 25, 60, 10},
        "",
        "depth",
        &mod->depth,
        0.0f,
        64.0f
    );
}

static void GuiLFO(int x, int y, lfo_t *lfo, const char *text) {
    GuiGroupBox((Rectangle){x, y, 145, 75}, text);
    GuiToggleGroup((Rectangle){x + 10, y + 10, 25, 10}, "sin;saw;tri;sqr;nos", &lfo->wav);
    GuiToggleGroup((Rectangle){x + 10, y + 25, 25, 10}, "osc;p/w;mod;amp;ftr", &lfo->dst);
    GuiSliderBar((Rectangle){x + 10, y + 40, 60, 10}, "", "spd", &lfo->spd, 0.0f, 64.0f);
    GuiSliderBar((Rectangle){x + 10, y + 55, 60, 10}, "", "amt", &lfo->amt, 0.0f, 64.0f);
    GuiCheckBox((Rectangle){x + 100, y + 40, 10, 10}, "osc1", &lfo->osc1);
    GuiCheckBox((Rectangle){x + 100, y + 55, 10, 10}, "osc2", &lfo->osc2);
}

static void GuiLFO1(int x, int y, lfo_t *lfo) {
    GuiLFO(x, y, lfo, "LFO1");
}

static void GuiLFO2(int x, int y, lfo_t *lfo) {
    GuiLFO(x, y, lfo, "LFO2");
}

static void GuiEqualizer(int x, int y, equalizer_t *eq) {
    GuiGroupBox((Rectangle){x, y, 145, 60}, "Equalizer");
    GuiSliderBar((Rectangle){x + 10, y + 10, 60, 10}, "", "low", &eq->low, 0.0f, 64.0f);
    GuiSliderBar((Rectangle){x + 10, y + 25, 60, 10}, "", "mid", &eq->mid, 0.0f, 64.0f);
    GuiSliderBar((Rectangle){x + 10, y + 40, 60, 10}, "", "hi", &eq->hi, 0.0f, 64.0f);
}

static void GuiAmplifier(int x, int y, amplifier_t *amp) {
    GuiGroupBox((Rectangle){x, y, 105, 90}, "Amplifier");
    GuiSliderBar((Rectangle){x + 10, y + 10, 60, 10}, "", "a", &amp->a, 0.0f, 64.0f);
    GuiSliderBar((Rectangle){x + 10, y + 25, 60, 10}, "", "d", &amp->d, 0.0f, 64.0f);
    GuiSliderBar((Rectangle){x + 10, y + 40, 60, 10}, "", "s", &amp->s, 0.0f, 64.0f);
    GuiSliderBar((Rectangle){x + 10, y + 55, 60, 10}, "", "r", &amp->r, 0.0f, 64.0f);
    GuiSliderBar(
        (Rectangle){x + 10, y + 70, 60, 10},
        "",
        "gain",
        &amp->gain,
        0.0f,
        64.0f
    );
}

static void GuiFilter(int x, int y, filter_t *ftr) {
    GuiGroupBox((Rectangle){x, y, 185, 75}, "Filter");
    GuiSliderBar((Rectangle){x + 10, y + 10, 60, 10}, "", "a", &ftr->a, 0.0f, 64.0f);
    GuiSliderBar((Rectangle){x + 10, y + 25, 60, 10}, "", "d", &ftr->d, 0.0f, 64.0f);
    GuiSliderBar((Rectangle){x + 10, y + 40, 60, 10}, "", "s", &ftr->s, 0.0f, 64.0f);
    GuiSliderBar((Rectangle){x + 10, y + 55, 60, 10}, "", "r", &ftr->r, 0.0f, 64.0f);
    GuiSliderBar((Rectangle){x + 90, y + 10, 60, 10}, "", "cut", &ftr->cut, 0.0f, 64.0f);
    GuiSliderBar((Rectangle){x + 90, y + 25, 60, 10}, "", "res", &ftr->res, 0.0f, 64.0f);
    GuiToggleGroup((Rectangle){x + 90, y + 40, 25, 10}, "lp;bp;hp", &ftr->pass);
    GuiToggleGroup((Rectangle){x + 90, y + 55, 25, 10}, "12;24", &ftr->db);
}

static int YBelowRect(Rectangle *rect) {
    return rect->y + rect->height;
}

int main() {
    const int width = 315;
    const int height = 305;

    InitWindow(width, height, "layout_name");
    SetTargetFPS(60);

    GuiSetStyle(BUTTON, BORDER_WIDTH, 1);
    GuiSetStyle(TOGGLE, GROUP_PADDING, 0);

    oscillator1_t osc1 = {0, 64.0f};
    oscillator2_t osc2 = {0, 64.0f, 0.0f, 0.0f};
    modulator_t mod = {0, 0.0f};
    equalizer_t eq = {32.0f, 32.0f, 32.0f};
    lfo_t lfo1 = {0, 0, 0.0f, 0.0f};
    lfo_t lfo2 = {0, 0, 0.0f, 0.0f};
    amplifier_t amp = {0.0f, 0.0f, 64.0f, 0.0f, 32.0f};
    filter_t ftr = {0.0f, 0.0f, 64.0f, 0.0f, 64.0f, 0.0f, 0, 0};
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        GuiOscillator1(10, 10, &osc1, &osc2);
        GuiOscillator2(10, 60, &osc2, &osc1);
        GuiModulator(160, 10, &mod);
        GuiEqualizer(160, 60, &eq);
        GuiAmplifier(200, 125, &amp);
        GuiFilter(10, 140, &ftr);
        GuiLFO1(10, 220, &lfo1);
        GuiLFO2(160, 220, &lfo2);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
