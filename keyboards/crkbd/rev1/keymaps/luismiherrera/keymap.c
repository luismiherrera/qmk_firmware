
#include QMK_KEYBOARD_H
#include "keymap_uk.h"
#include "sendstring_uk.h"


//Combos
const uint16_t PROGMEM combo1[] = {LCTL_T(KC_D), LSFT_T(KC_F), COMBO_END};
const uint16_t PROGMEM combo2[] = {LSFT_T(KC_J), LCTL_T(KC_K), COMBO_END};
combo_t key_combos[] = {
    COMBO(combo1, KC_LPRN),
    COMBO(combo2, KC_RPRN),
};
//End of Combos

//UNICODES
enum unicode_names {
     U_NTIL_LOWER,
     U_NTIL_UPPER,
};
const uint32_t unicode_map[] PROGMEM = {
     [U_NTIL_LOWER] = 0x00f1, //ñ
     [U_NTIL_UPPER] = 0x00d1, //Ñ
};

#define U_NTIL XP(U_NTIL_LOWER, U_NTIL_UPPER)
//

// //Send stings
// enum custom_keycodes {
//     QMKENIE = SAFE_RANGE,
// };

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//     case QMKENIE:
//         if (record->event.pressed) {
//             // when keycode QMKENIE is pressed
//             SEND_STRING("ñ");
//         } else {
//             // when keycode QMKENIE is released
//         }k
//         break;
//     }
//     return true;
// };
// //End of Send strings

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //DEFAULT LAYER
    [0] = LAYOUT_split_3x6_3(
  //,------------------------------------------------------------------------------------.         ,----------------------------------------------------------------------------------------.
       KC_NO,  KC_Q,           KC_W,          KC_E,          KC_R,          KC_T,                    KC_Y,           KC_U,          KC_I,          KC_O,          KC_P,             KC_BSPC,
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
     KC_RALT,  KC_A,           LALT_T(KC_S),  LCTL_T(KC_D),  LSFT_T(KC_F),  KC_G,                    KC_H,           LSFT_T(KC_J),  LCTL_T(KC_K),  LALT_T(KC_L),  KC_SCLN,          KC_QUOT, 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
       KC_NO,  LGUI_T(KC_Z),   KC_X,          KC_C,          KC_V,          KC_B,                    KC_N,           KC_M,          KC_COMM,       KC_DOT,        LGUI_T(KC_SLSH),  TT(3),
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
                                             LT(4,KC_ESC),   LT(3,KC_BSPC), LT(1,KC_TAB),            LT(5,KC_ENT),   LT(2,KC_SPC),  LT(6,KC_DEL)
                                         //`---------------+--------------+--------------'         `---------------+--------------+--------'

  ),

     //NUMBERS LAYER
    [1] = LAYOUT_split_3x6_3(
  //,------------------------------------------------------------------------------------.         ,----------------------------------------------------------------------------------------.
       KC_NO,  KC_NO,          KC_NO,         KC_NO,         KC_NO,         KC_NO,                   KC_LBRC,        KC_7,          KC_8,          KC_9,          KC_RBRC,          KC_BSPC, 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
       KC_NO,  KC_NO,          KC_LALT,       KC_LCTL,       KC_LSFT,       KC_NO,                   KC_EQL,         KC_4,          KC_5,          KC_6,          KC_ASTR,          KC_NO, 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
       KC_NO,  KC_LGUI,        KC_NO,         KC_NO,         KC_NO,         KC_NO,                   KC_PLUS,        KC_1,          KC_2,          KC_3,          KC_SLSH,          KC_NO, 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
                                              KC_NO,         KC_NO,         KC_TRNS,                 KC_MINS,        KC_0,          KC_DOT
                                         //`---------------+--------------+--------------'         `---------------+--------------+--------'

  ),

     //SYMBOLS LAYER
    [2] = LAYOUT_split_3x6_3(
  //,------------------------------------------------------------------------------------.         ,----------------------------------------------------------------------------------------.
       KC_NO,  KC_NO,          KC_AMPR,       KC_ASTR,       KC_LCBR,       KC_RCBR,                 KC_NO,          KC_NO,         KC_NO,         KC_NO,         KC_NO,            KC_BSPC, 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
       KC_NO,  KC_EXLM,        UK_DQUO,       KC_QUOT,       KC_COLN,       UK_HASH,                 KC_NO,          KC_LSFT,       KC_LCTL,       KC_LALT,       KC_NO,            KC_NO, 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
       KC_NO,  UK_BSLS,        KC_DLR,        KC_LPRN,       KC_RPRN,       KC_PERC,                 U_NTIL,         KC_NO,         KC_NO,         KC_NO,         KC_LGUI,          KC_NO, 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
                                              KC_NO,         KC_NO,         KC_UNDS,                 KC_NO,          KC_TRNS,       KC_NO   
                                         //`---------------+--------------+--------------'         `---------------+--------------+--------'

  ),


     //NAVIGATION LAYER
    [3] = LAYOUT_split_3x6_3(
  //,------------------------------------------------------------------------------------.         ,----------------------------------------------------------------------------------------.
       KC_NO,  KC_NO,          KC_NO,         KC_NO,          KC_NO,        KC_NO,                   LCTL(KC_V),     LCTL(KC_C),    LCTL(KC_X),    LCTL(KC_Z),    LCTL(KC_Y),       KC_BSPC, 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
       KC_NO,  KC_NO,          KC_LALT,       KC_LCTL,        KC_LSFT,      KC_NO,                   KC_LEFT,        KC_DOWN,       KC_UP,         KC_RGHT,       KC_CAPS,          KC_NO,      
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
       KC_NO,  KC_LGUI,        KC_NO,         KC_NO,          KC_NO,        KC_NO,                   KC_HOME,        KC_PGDN,       KC_PGUP,       KC_END,        KC_INS,           TG(3), 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
                                              KC_NO,          KC_TRNS,      KC_NO,                   KC_ENT,         KC_SPC,        KC_DEL
                                         //`---------------+--------------+--------------'         `---------------+--------------+--------'

  ),


     //MOUSE LAYER
    [4] = LAYOUT_split_3x6_3(
  //,------------------------------------------------------------------------------------.         ,----------------------------------------------------------------------------------------.
       KC_NO,  KC_NO,          KC_NO,         KC_NO,         KC_NO,         KC_NO,                   LCTL(KC_V),     LCTL(KC_C),    LCTL(KC_X),    LCTL(KC_Z),     LCTL(KC_Y),      KC_BSPC, 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
       KC_NO,  KC_NO,          KC_LALT,       KC_LCTL,       KC_LSFT,       KC_NO,                   KC_MS_L,        KC_MS_D,       KC_MS_U,       KC_MS_R,        KC_NO,           KC_NO, 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
       KC_NO,  KC_LGUI,        KC_NO,         KC_NO,         KC_NO,         KC_NO,                   KC_WH_L,        KC_WH_D,       KC_WH_U,       KC_WH_R,        KC_NO,           KC_NO, 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
                                              KC_TRNS,       KC_NO,         KC_NO,                   KC_BTN1,        KC_BTN2,       KC_BTN3
                                         //`---------------+--------------+--------------'         `---------------+--------------+--------'

  ),


     //FUNCTIONS LAYER
    [5] = LAYOUT_split_3x6_3(
  //,------------------------------------------------------------------------------------.         ,----------------------------------------------------------------------------------------.
       KC_NO,  KC_F12,         KC_F7,         KC_F8,         KC_F9,         KC_PSCR,                 KC_NO,          KC_NO,          KC_NO,         KC_NO,        KC_NO,            KC_BSPC, 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
       KC_NO,  KC_F11,         KC_F4,         KC_F5,         KC_F6,         KC_SCRL,                 KC_NO,          KC_LSFT,        KC_LCTL,       KC_LALT,      KC_NO,            KC_NO, 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
       KC_NO,  KC_F10,         KC_F1,         KC_F2,         KC_F3,         KC_PAUS,                 KC_NO,          KC_NO,          KC_NO,         KC_NO,        KC_LGUI,          KC_NO, 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
                                              KC_NO,         KC_SPC,        KC_TAB,                  KC_TRNS,        KC_NO,          KC_NO
                                         //`---------------+--------------+--------------'         `---------------+--------------+--------'

  ),

     //MEDIA LAYER
    [6] = LAYOUT_split_3x6_3(
  //,------------------------------------------------------------------------------------.         ,----------------------------------------------------------------------------------------.
       QK_BOOT, KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,                   KC_NO,           KC_NO,         KC_NO,        KC_NO,         KC_NO,            KC_NO, 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
       KC_NO,   KC_MPRV,       KC_VOLD,       KC_VOLU,       KC_MNXT,       KC_NO,                   KC_NO,           KC_NO,         KC_NO,        KC_NO,         KC_NO,            KC_NO, 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
       KC_NO,   KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,                   KC_NO,           KC_NO,         KC_NO,        KC_NO,         KC_NO,            KC_NO, 
  //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
                                              KC_MUTE,       KC_MPLY,       KC_MSTP,                 KC_NO,           KC_NO,         KC_TRNS
                                         //`---------------+--------------+--------------'         `---------------+--------------+--------'

  ),

};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
    return OLED_ROTATION_270;
  } 
  // return rotation;
  return OLED_ROTATION_180;
}

static void oled_render_layer_state(void) {
    // Host Keyboard Layer Status
    //oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
          case 0:
               oled_write_P(PSTR(" DEF \n"), false);
               break;
          case 1:
               oled_write_P(PSTR(" NUM \n"), false);
               break;
          case 2:
               oled_write_P(PSTR(" SYM \n"), false);
               break;
          case 3:
               oled_write_P(PSTR(" NAV \n"), false);
               break;
          case 4:
               oled_write_P(PSTR("MOUSE\n"), false);
               break;
          case 5:
               oled_write_P(PSTR(" FUN \n"), false);
               break;
          case 6:
               oled_write_P(PSTR("MEDIA\n"), false);
               break;
          default:
               // Or use the write_ln shortcut over adding '\n' to the end of your string
               oled_write_ln_P(PSTR(" UND \n"), false);
    }

    oled_write_P(PSTR("-----\n"), false);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.caps_lock ? PSTR(" CAP \n") : PSTR("     \n"), false);
    oled_write_P(PSTR("-----\n"), false);    

}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
    } else {
        render_logo();
     }
    return false;
}

#endif

