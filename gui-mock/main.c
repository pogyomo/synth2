#include <math.h>
#include <stddef.h>
#include <stdio.h>

#include "raygui.h"
#include "raylib.h"

typedef struct oscillator1 {
    int wav;
    float det;
} oscillator1_t;

typedef struct oscillator2 {
    int wav;
    int pitch;
    int cent;
} oscillator2_t;

typedef struct oscillators {
    float pw;
    float mix;
    bool osc1, osc2;
} oscillators_t;

typedef struct amplifier {
    float a, d, s, r;
    float amt, vel;
} amplifier_t;

typedef struct filter {
    float a, d, s, r;
    float amt, vel;
    float cut, res;
    int type, db;
} filter_t;

typedef struct modulator {
    int type;
    float a, d, s, r;
    float amt;
} modulator_t;

typedef struct lfo {
    int wav;
    int dst;
    float speed;
    float amt;
    bool osc1, osc2;
} lfo_t;

typedef struct equalizer {
    float low, mid, hi;
} equalizer_t;

static int GuiSliderInt(
    Rectangle bounds,
    const char *textLeft,
    const char *textRight,
    int *value,
    int minValue,
    int maxValue
) {
    float value_ = (float)*value;
    int res =
        GuiSlider(bounds, textLeft, textRight, &value_, (float)minValue, (float)maxValue);
    *value = (int)floorf(value_);
    return res;
}

static int GuiSliderBarInt(
    Rectangle bounds,
    const char *textLeft,
    const char *textRight,
    int *value,
    int minValue,
    int maxValue
) {
    float value_ = (float)*value;
    int res = GuiSliderBar(
        bounds,
        textLeft,
        textRight,
        &value_,
        (float)minValue,
        (float)maxValue
    );
    *value = (int)floorf(value_);
    return res;
}

static bool CheckMouseInBounds(Rectangle bounds) {
    Vector2 pos = GetMousePosition();
    bool bx = bounds.x <= pos.x && pos.x <= bounds.x + bounds.width;
    bool by = bounds.y <= pos.y && pos.y <= bounds.y + bounds.height;
    return bx && by;
}

static void GuiOscillator1(int x, int y, oscillator1_t *osc1) {
    const Rectangle rect_group = {x, y, 145, 45};
    const Rectangle rect_wav = {x + 10, y + 10, 25, 10};
    const Rectangle rect_det = {x + 10, y + 25, 75, 10};

    GuiGroupBox(rect_group, "Oscillator1");

    GuiToggleGroup(rect_wav, "sin;saw;tri;sqr;nos", &osc1->wav);
    GuiSliderBar(rect_det, NULL, "det", &osc1->det, 0.0f, 128.0f);
}

static void GuiOscillator2(int x, int y, oscillator2_t *osc2) {
    static char buf[1024];
    const Rectangle rect_group = {x, y, 145, 60};
    const Rectangle rect_wav = {x + 10, y + 10, 25, 10};
    const Rectangle rect_pit = {x + 10, y + 25, 75, 10};
    const Rectangle rect_pit_cls = {x + 110, y + 25, 25, 10};
    const Rectangle rect_cnt = {x + 10, y + 40, 75, 10};
    const Rectangle rect_cnt_cls = {x + 110, y + 40, 25, 10};

    GuiGroupBox(rect_group, "Oscillator2");

    GuiToggleGroup(rect_wav, "sin;saw;tri;sqr;nos", &osc2->wav);

    if (GuiButton(rect_pit_cls, "cls")) osc2->pitch = 0;
    GuiSliderInt(rect_pit, NULL, "pit", &osc2->pitch, -12, 12);
    if (CheckMouseInBounds(rect_pit)) {
        snprintf(buf, 1024, "%d", osc2->pitch);
        GuiLabel((Rectangle){GetMouseX(), rect_pit.y - 5, 30, 10}, buf);
    }

    if (GuiButton(rect_cnt_cls, "cls")) osc2->cent = 0;
    GuiSliderInt(rect_cnt, NULL, "cnt", &osc2->cent, -64, 64);
    if (CheckMouseInBounds(rect_cnt)) {
        snprintf(buf, 1024, "%d", osc2->cent);
        GuiLabel((Rectangle){GetMouseX(), rect_cnt.y - 5, 30, 10}, buf);
    }
}

static void GuiOscillators(int x, int y, oscillators_t *oscs) {
    const Rectangle rect_group = {x, y, 145, 45};
    const Rectangle rect_pw = {x + 10, y + 10, 75, 10};
    const Rectangle rect_mix = {x + 10, y + 25, 75, 10};
    const Rectangle rect_osc1 = {x + 110, y + 10, 25, 10};
    const Rectangle rect_osc2 = {x + 110, y + 25, 25, 10};

    GuiGroupBox(rect_group, "Oscillators");
    GuiSliderBar(rect_pw, NULL, "pw", &oscs->pw, 0.0f, 64.0f);
    GuiSlider(rect_mix, NULL, "mix", &oscs->mix, 0.0f, 64.0f);
    GuiToggle(rect_osc1, "oc1", &oscs->osc1);
    GuiToggle(rect_osc2, "oc2", &oscs->osc2);
}

static void GuiAmplifier(int x, int y, amplifier_t *amp) {
    const Rectangle rect_group = {x, y, 120, 110};
    const Rectangle rect_a = {x + 10, y + 10, 75, 10};
    const Rectangle rect_d = {x + 10, y + 25, 75, 10};
    const Rectangle rect_s = {x + 10, y + 40, 75, 10};
    const Rectangle rect_r = {x + 10, y + 55, 75, 10};
    const Rectangle rect_amt = {x + 10, y + 70, 75, 10};
    const Rectangle rect_vel = {x + 10, y + 85, 75, 10};

    GuiGroupBox(rect_group, "Amplifier");
    GuiSliderBar(rect_a, NULL, "a", &amp->a, 0.0f, 64.0f);
    GuiSliderBar(rect_d, NULL, "d", &amp->d, 0.0f, 64.0f);
    GuiSliderBar(rect_s, NULL, "s", &amp->s, 0.0f, 64.0f);
    GuiSliderBar(rect_r, NULL, "r", &amp->r, 0.0f, 64.0f);
    GuiSliderBar(rect_amt, NULL, "amt", &amp->amt, 0.0f, 64.0f);
    GuiSliderBar(rect_vel, NULL, "vel", &amp->vel, 0.0f, 64.0f);
}

static void GuiFilter(int x, int y, filter_t *filter) {
    const Rectangle rect_group = {x, y, 245, 110};
    const Rectangle rect_a = {x + 10, y + 10, 75, 10};
    const Rectangle rect_d = {x + 10, y + 25, 75, 10};
    const Rectangle rect_s = {x + 10, y + 40, 75, 10};
    const Rectangle rect_r = {x + 10, y + 55, 75, 10};
    const Rectangle rect_amt = {x + 10, y + 70, 75, 10};
    const Rectangle rect_vel = {x + 10, y + 85, 75, 10};
    const Rectangle rect_cut = {x + 135, y + 10, 75, 10};
    const Rectangle rect_res = {x + 135, y + 25, 75, 10};
    const Rectangle rect_type = {x + 135, y + 40, 25, 10};
    const Rectangle rect_db = {x + 135, y + 55, 25, 10};

    GuiGroupBox(rect_group, "Filter");
    GuiSliderBar(rect_a, NULL, "a", &filter->a, 0.0f, 64.0f);
    GuiSliderBar(rect_d, NULL, "d", &filter->d, 0.0f, 64.0f);
    GuiSliderBar(rect_s, NULL, "s", &filter->s, 0.0f, 64.0f);
    GuiSliderBar(rect_r, NULL, "r", &filter->r, 0.0f, 64.0f);
    GuiSlider(rect_amt, NULL, "amt", &filter->amt, -64.0f, 64.0f);
    GuiSliderBar(rect_cut, NULL, "cut", &filter->cut, 0.0f, 64.0f);
    GuiSliderBar(rect_res, NULL, "res", &filter->res, 0.0f, 64.0f);
    GuiSliderBar(rect_vel, NULL, "vel", &filter->vel, 0.0f, 64.0f);
    GuiToggleGroup(rect_type, "lp;bp;hp", &filter->type);
    GuiToggleGroup(rect_db, "6;12;24", &filter->db);
}

static void GuiModulator(int x, int y, modulator_t *mod) {
    const Rectangle rect_group = {x, y, 120, 110};
    const Rectangle rect_type = {x + 10, y + 10, 25, 10};
    const Rectangle rect_a = {x + 10, y + 25, 75, 10};
    const Rectangle rect_d = {x + 10, y + 40, 75, 10};
    const Rectangle rect_s = {x + 10, y + 55, 75, 10};
    const Rectangle rect_r = {x + 10, y + 70, 75, 10};
    const Rectangle rect_amt = {x + 10, y + 85, 75, 10};

    GuiGroupBox(rect_group, "Modulator");
    GuiToggleGroup(rect_type, "fm;am", &mod->type);
    GuiSliderBar(rect_a, NULL, "a", &mod->a, 0.0f, 64.0f);
    GuiSliderBar(rect_d, NULL, "d", &mod->d, 0.0f, 64.0f);
    GuiSliderBar(rect_s, NULL, "s", &mod->s, 0.0f, 64.0f);
    GuiSliderBar(rect_r, NULL, "r", &mod->r, 0.0f, 64.0f);
    GuiSliderBar(rect_amt, NULL, "amt", &mod->amt, 0.0f, 64.0f);
}

static void GuiLFO(int x, int y, lfo_t *lfo, const char *text) {
    const Rectangle rect_group = (Rectangle){x, y, 145, 75};
    const Rectangle rect_wav = {x + 10, y + 10, 25, 10};
    const Rectangle rect_dst = {x + 10, y + 25, 25, 10};
    const Rectangle rect_speed = {x + 10, y + 40, 60, 10};
    const Rectangle rect_amt = {x + 10, y + 55, 60, 10};
    const Rectangle rect_osc1 = {x + 100, y + 40, 10, 10};
    const Rectangle rect_osc2 = {x + 100, y + 55, 10, 10};

    GuiGroupBox(rect_group, text);
    GuiToggleGroup(rect_wav, "sin;saw;tri;sqr;nos", &lfo->wav);
    GuiToggleGroup(rect_dst, "osc;p/w;mod;amp;ftr", &lfo->dst);
    GuiSliderBar(rect_speed, "", "spd", &lfo->speed, 0.0f, 64.0f);
    GuiSliderBar(rect_amt, "", "amt", &lfo->amt, 0.0f, 64.0f);
    GuiCheckBox(rect_osc1, "osc1", &lfo->osc1);
    GuiCheckBox(rect_osc2, "osc2", &lfo->osc2);
}

static void GuiLFO1(int x, int y, lfo_t *lfo) {
    GuiLFO(x, y, lfo, "LFO1");
}

static void GuiLFO2(int x, int y, lfo_t *lfo) {
    GuiLFO(x, y, lfo, "LFO2");
}

static void GuiEqualizer(int x, int y, equalizer_t *eq) {
    const Rectangle rect_group = (Rectangle){x, y, 145, 60};
    const Rectangle rect_low = {x + 10, y + 10, 75, 10};
    const Rectangle rect_mid = {x + 10, y + 25, 75, 10};
    const Rectangle rect_hi = {x + 10, y + 40, 75, 10};

    GuiGroupBox(rect_group, "Equalizer");
    GuiSliderBar(rect_low, NULL, "low", &eq->low, 0.0f, 64.0f);
    GuiSliderBar(rect_mid, NULL, "mid", &eq->mid, 0.0f, 64.0f);
    GuiSliderBar(rect_hi, NULL, "hi", &eq->hi, 0.0f, 64.0f);
}

int main(void) {
    const int width = 415;
    const int height = 325;

    InitWindow(width, height, "synth2");
    SetTargetFPS(60);

    GuiSetStyle(BUTTON, BORDER_WIDTH, 1);
    GuiSetStyle(TOGGLE, GROUP_PADDING, 0);

    oscillator1_t osc1 = {0, 0.0f};
    oscillator2_t osc2 = {0, 0, 0};
    oscillators_t oscs = {64.0f, 0.0f, true, false};
    equalizer_t eq = {32.0f, 32.0f, 32.0f};
    amplifier_t amp = {0.0f, 0.0f, 64.0f, 0.0f, 32.0f, false};
    filter_t filter = {0.0f, 0.0f, 64.0f, 0.0f, 0.0f, 0.0f, 64.0f, 0.0f, 0, 0};
    modulator_t mod = {0, 0.0f};
    lfo_t lfo1 = {0, 0, 0.0f, 0.0f, true, false};
    lfo_t lfo2 = {0, 0, 0.0f, 0.0f, true, false};
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        GuiOscillator1(10, 10, &osc1);
        GuiOscillator2(10, 60, &osc2);
        GuiOscillators(10, 125, &oscs);
        GuiEqualizer(10, 175, &eq);
        GuiFilter(160, 125, &filter);
        GuiModulator(160, 10, &mod);
        GuiAmplifier(285, 10, &amp);
        GuiLFO1(10, 240, &lfo1);
        GuiLFO2(160, 240, &lfo2);

        GuiGroupBox((Rectangle){310, 240, 95, 75}, NULL);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
