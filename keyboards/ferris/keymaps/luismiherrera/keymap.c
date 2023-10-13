//qmk flash -c -kb ferris/sweep -km luismiherrera -bl uf2-split-left -e CONVERT_TO=promicro_rp2040

#include QMK_KEYBOARD_H
#include "keymap_uk.h"
#include "sendstring_uk.h"

enum luismi_layers {
     DEF,
     MAYA,
     NUM,
     SYM,
     NAV,
     MOUSE,
     FUN,
     MEDIA,
};

//Combos
const uint16_t PROGMEM combo1[] = {LCTL_T(KC_D), LSFT_T(KC_F), COMBO_END};
const uint16_t PROGMEM combo2[] = {LSFT_T(KC_J), LCTL_T(KC_K), COMBO_END};
const uint16_t PROGMEM combo3[] = {LSFT_T(KC_F), LSFT_T(KC_J), COMBO_END};
const uint16_t PROGMEM combo4[] = {LGUI_T(KC_Z), LGUI_T(KC_SLSH), COMBO_END};
const uint16_t PROGMEM combo5[] = {LCTL_T(KC_Z), LGUI_T(KC_SLSH), COMBO_END};
const uint16_t PROGMEM combo6[] = {KC_Q, KC_A, COMBO_END};
const uint16_t PROGMEM combo7[] = {KC_Q, LSFT_T(KC_A), COMBO_END};
const uint16_t PROGMEM combo8[] = {KC_P, KC_QUOT, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo1, KC_LPRN),
    COMBO(combo2, KC_RPRN),
    COMBO(combo3, KC_CAPS),
    COMBO(combo4, DF(MAYA)),
    COMBO(combo5, DF(DEF)),
    COMBO(combo6, KC_ESC),
    COMBO(combo7, KC_ESC),
    COMBO(combo8, KC_BSPC),
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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //DEFAULT LAYER
    [DEF] = LAYOUT(
  
     KC_Q,          KC_W,          KC_E,          KC_R,            KC_T,              KC_Y,            KC_U,            KC_I,          KC_O,          KC_P,            
     KC_A,          LALT_T(KC_S),  LCTL_T(KC_D),  LSFT_T(KC_F),    KC_G,              KC_H,            LSFT_T(KC_J),    LCTL_T(KC_K),  LALT_T(KC_L),  KC_QUOT,        
     LGUI_T(KC_Z),  KC_X,          KC_C,          KC_V,            KC_B,              KC_N,            KC_M,            KC_COMM,       KC_DOT,        LGUI_T(KC_SLSH),
                                                  LT(NAV,KC_TAB),  LT(NUM,KC_BSPC),   LT(FUN,KC_ENT),  LT(SYM,KC_SPC)
     ),
    
    //MAYA LAYER
    [MAYA] = LAYOUT(
  
     KC_Q,          KC_W,          KC_E,          KC_R,            KC_T,              KC_Y,            KC_U,            KC_I,          KC_O,          KC_P,            
     LSFT_T(KC_A),  KC_S,          KC_D,          KC_F,            KC_G,              KC_H,            LSFT_T(KC_J),    LCTL_T(KC_K),  LALT_T(KC_L),  KC_QUOT,        
     LCTL_T(KC_Z),  KC_X,          KC_C,          KC_V,            KC_B,              KC_N,            KC_M,            KC_COMM,       KC_DOT,        LGUI_T(KC_SLSH),
                                                  KC_LALT,         KC_SPC,            LT(FUN,KC_ENT),  LT(SYM,KC_SPC)
     ),

     //FUNCTIONS LAYER
    [FUN] = LAYOUT(

     KC_F12,         KC_F7,         KC_F8,         KC_F9,         KC_PSCR,          KC_PLUS,        KC_7,          KC_8,          KC_9,          KC_MINS,
     KC_F11,         KC_F4,         KC_F5,         KC_F6,         KC_SCRL,          KC_EQL,         LSFT_T(KC_4),  LCTL_T(KC_5),  LALT_T(KC_6),  KC_ASTR,
     KC_F10,         KC_F1,         KC_F2,         KC_F3,         KC_PAUS,          KC_DOT,         KC_1,          KC_2,          KC_3,          LGUI_T(KC_SLSH),
                                                   KC_ESC,        KC_UNDS,          KC_TRNS,        KC_0
  ),
     //NUMBERS LAYER
    [NUM] = LAYOUT(

     KC_F12,         KC_F7,         KC_F8,         KC_F9,         KC_PSCR,          KC_PLUS,        KC_7,          KC_8,          KC_9,          KC_MINS,
     KC_F11,         LALT_T(KC_F4), LCTL_T(KC_F5), LSFT_T(KC_F6), KC_SCRL,          KC_EQL,         KC_4,          KC_5,          KC_6,          KC_ASTR,
     LGUI_T(KC_F10), KC_F1,         KC_F2,         KC_F3,         KC_PAUS,          KC_DOT,         KC_1,          KC_2,          KC_3,          KC_SLSH,
                                                   KC_NO,         KC_TRNS,          KC_ENT,         KC_0
  ),

     //SYMBOLS LAYER
    [SYM] = LAYOUT(
 
    UK_GRV,         KC_AMPR,       KC_LBRC,       KC_RBRC,       KC_PERC,             LCTL(KC_V),      LCTL(KC_C),       LCTL(KC_X),    LCTL(KC_Z),      LCTL(KC_Y),      
    KC_EXLM,        UK_DQUO,       KC_SCLN,       KC_COLN,       KC_ASTR,             KC_LEFT,         LSFT_T(KC_DOWN),  LCTL_T(KC_UP), LALT_T(KC_RGHT), U_NTIL,         
    UK_BSLS,        KC_DLR,        KC_LCBR,       KC_RCBR,       UK_HASH,             KC_HOME,         KC_PGDN,          KC_PGUP,       KC_END,          LGUI_T(KC_NO), 
                                                  KC_ESC,        KC_DEL,              KC_NO,           KC_TRNS
  ),

       //NAVIGATION LAYER
    [NAV] = LAYOUT(
 
    UK_GRV,           KC_AMPR,           KC_LBRC,          KC_RBRC,          KC_PERC,             LCTL(KC_V),      LCTL(KC_C),       LCTL(KC_X),    LCTL(KC_Z),      LCTL(KC_Y),      
    KC_EXLM,          LALT_T(UK_DQUO),   LCTL_T(KC_SCLN),  LSFT_T(KC_COLN),  KC_ASTR,             KC_LEFT,         KC_DOWN,          KC_UP,         KC_RGHT,         U_NTIL,         
    LGUI_T(UK_BSLS),  KC_DLR,            KC_LCBR,          KC_RCBR,          UK_HASH,             KC_HOME,         KC_PGDN,          KC_PGUP,       KC_END,          KC_NO, 
                                                           KC_TRNS,          KC_NO,               KC_ENTER,        MO(MOUSE)
  ),

     //MOUSE LAYER
    [MOUSE] = LAYOUT(

    QK_BOOT,        KC_NO,             KC_NO,            KC_NO,             KC_NO,             KC_NO,          KC_BTN1,       KC_BTN2,       KC_BTN3,        KC_NO,  
    KC_MPRV,        LALT_T(KC_VOLD),   LCTL_T(KC_VOLU),  LSFT_T(KC_MNXT),   KC_NO,             KC_MS_L,        KC_MS_D,       KC_MS_U,       KC_MS_R,        KC_NO, 
    KC_LGUI,        KC_NO,             KC_NO,            KC_MPLY,           KC_NO,             KC_WH_L,        KC_WH_D,       KC_WH_U,       KC_WH_R,        KC_NO,  
                                                         KC_TRNS,           KC_NO,             KC_NO,          KC_TRNS
  ),

//       //MAYA LAYER
//     [MAYA] = LAYOUT(
//   //,------------------------------------------------------------------------------------.         ,----------------------------------------------------------------------------------------.
//        KC_NO,   KC_Q,            KC_W,          KC_E,          KC_R,          KC_T,                    KC_Y,           KC_U,          KC_I,          KC_O,          KC_P,             KC_NO, 
//   //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
//        KC_NO,   LSFT_T(KC_A),    KC_S,          KC_D,          KC_F,          KC_G,                    KC_H,           LSFT_T(KC_J),  LCTL_T(KC_K),  LALT_T(KC_L),  KC_SCLN,          KC_NO, 
//   //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
//        KC_NO,   LCTL_T(KC_Z),    KC_X,          KC_C,          KC_V,          KC_B,                    KC_N,           KC_M,          KC_COMM,       KC_DOT,        LGUI_T(KC_SLSH),  KC_NO,
//   //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
//                                                 KC_NO,         KC_LALT,       KC_SPC,                LT(FUN,KC_ENT),  LT(SYM,KC_SPC), KC_NO
//                                          //`---------------+--------------+--------------'         `---------------+--------------+--------'

//   ),


//      //MEDIA LAYER
//     [MEDIA] = LAYOUT(
//   //,------------------------------------------------------------------------------------.         ,----------------------------------------------------------------------------------------.
//        QK_BOOT, KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,                   KC_NO,           KC_NO,         KC_NO,        KC_NO,         KC_NO,            KC_TRNS, 
//   //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
//        KC_NO,   KC_MPRV,       KC_VOLD,       KC_VOLU,       KC_MNXT,       KC_NO,                   KC_NO,           KC_NO,         KC_NO,        KC_NO,         KC_NO,            KC_NO, 
//   //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
//        KC_NO,   KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,                   KC_NO,           KC_NO,         KC_NO,        KC_NO,         KC_NO,            KC_NO, 
//   //|--------+---------------+--------------+--------------+--------------+--------------|         |---------------+--------------+--------------+--------------+-----------------+----------|
//                                               KC_NO,         KC_MUTE,       KC_MPLY,                 KC_NO,           KC_NO,         KC_TRNS
//                                          //`---------------+--------------+--------------'         `---------------+--------------+--------'

//   ),

 

};