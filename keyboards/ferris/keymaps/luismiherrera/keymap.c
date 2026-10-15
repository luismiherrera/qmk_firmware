/*
 ============================================================================
  FERRIS SWEEP - KEYMAP "luismiherrera"  (QMK)   -- HOW TO UPDATE THE KEYBOARD
 ============================================================================

  HARDWARE / SETUP
  - Keyboard: Ferris Sweep (split, 34 keys), UK layout
  - Controllers: Pro Micro RP2040 boards, built with CONVERT_TO=promicro_rp2040
  - Handedness: EE_HANDS (each half stores in its own flash whether it is LEFT
    or RIGHT). So each half MUST be flashed with its own LEFT or RIGHT file.
  - Files live in:
      C:\Users\Luismi Herrera\qmk_firmware\keyboards\ferris\sweep\keymaps\luismiherrera\
      (keymap.c, config.h, rules.mk)  -> keep a backup / git repo of this folder!
  - Run all commands in the "QMK MSYS" terminal (NOT PowerShell / cmd).

  UPDATE PROCEDURE (this is the one that works, drag and drop)
  1. Edit keymap.c (and config.h / rules.mk if needed).
  2. LEFT build: in config.h make sure exactly ONE of these lines is active:
         #define INIT_EE_HANDS_LEFT
         //#define INIT_EE_HANDS_RIGHT
     then in QMK MSYS run:
         qmk compile -kb ferris/sweep -km luismiherrera -e CONVERT_TO=promicro_rp2040
     Copy qmk_firmware\ferris_sweep_luismiherrera_promicro_rp2040.uf2
     somewhere safe and rename it  sweep_LEFT.uf2
  3. RIGHT build: in config.h swap to:
         //#define INIT_EE_HANDS_LEFT
         #define INIT_EE_HANDS_RIGHT
     run the SAME compile command, rename the new uf2  sweep_RIGHT.uf2
  4. Unplug the TRRS cable between the halves (and USB).
  5. Hold the BOOT button on the LEFT half while plugging in USB. A drive
     called RPI-RP2 appears. Drag sweep_LEFT.uf2 onto it. It reboots by itself.
  6. Same for the RIGHT half with sweep_RIGHT.uf2.
  7. Unplug everything, connect the TRRS cable while USB is UNPLUGGED, then
     plug USB into either half.
  NEVER flash the same file to both halves.

  IF THE KEYBOARD STOPS WORKING / HALVES DON'T TALK / FRESH START
  - RP2040 cannot be bricked: BOOT button + plug in USB always gives RPI-RP2.
  - Optional wipe: drag Raspberry Pi's flash_nuke.uf2 onto RPI-RP2 (erases
    everything incl. handedness), then redo steps 4-7 above with both files.
  - A reset/wipe loses the LEFT/RIGHT flag, so both halves need their own
    file flashed again.
  - Another way into the bootloader: QK_BOOT key on the MOUSE layer.

  OPTIONAL: "qmk flash" INSTEAD OF DRAG AND DROP
  - Needs wmic.exe (removed from recent Windows 11; it was missing here, so
    I use drag and drop). If wmic is present, with the half in bootloader mode:
      qmk flash -c -kb ferris/sweep -km luismiherrera -bl uf2-split-left  -e CONVERT_TO=promicro_rp2040
      qmk flash -c -kb ferris/sweep -km luismiherrera -bl uf2-split-right -e CONVERT_TO=promicro_rp2040
    (then do NOT also define INIT_EE_HANDS_* in config.h)
  - Error "FileNotFoundError ... wmic" in uf2conv.py = wmic is missing.

  NOTES ON THE CONFIG
  - rules.mk: RAW_ENABLE = yes is needed for the Maya layer status that is sent
    to the PC over raw HID. Only the USB master half sends it, and only when
    the state changes (an earlier version sent on every layer change and was
    the suspect for freezes on Linux/Omarchy).
    If Linux freezes come back: set RAW_ENABLE = no and remove the raw_hid code.
  - config.h: RP2040_FLASH_GD25Q64CS is specific to the flash chip on my
    boards, don't remove it. BILATERAL_COMBINATIONS_* only matter on the
    Miryoku fork, ignored on normal QMK. TAPPING_TERM 200.

  LAYERS
  - DEF (home-row mods), MAYA (for Maya, DF layer), NUM, SYM, NAV, MOUSE,
    FUN, MEDIA (declared, not used yet)
  - Thumbs on DEF: TAB/NAV, BSPC/NUM, ENT/FUN, SPC/SYM
  - Combos: D+F = (   J+K = )   F+J = CapsLock   Q+A = Esc   P+' = Backspace
            Z + / (both bottom corners) = switch to MAYA (left Z is GUI);
            on the MAYA layer the same keys switch back to DEF.
  ============================================================================
*/

#include QMK_KEYBOARD_H
#include "keymap_uk.h"
#include "sendstring_uk.h"
#include "raw_hid.h"

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

// Raw HID: tell the host (e.g. the Windows Maya script) whether the Maya layer is active.
// Only the USB master half sends, and only when the state actually changes.
static bool maya_sent_once = false;
static bool maya_last      = false;

static void send_maya_status(bool maya) {
    if (!is_keyboard_master()) return;                // slave half has no USB host
    if (maya_sent_once && maya == maya_last) return;  // only send on change
    maya_sent_once = true;
    maya_last      = maya;
    uint8_t data[32] = {0}; // HID report must be 32 bytes
    data[0] = maya ? 1 : 0; // 1 = Maya layer active, 0 = inactive
    raw_hid_send(data, 32);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    send_maya_status(layer_state_cmp(state | default_layer_state, MAYA));
    return state;
}

// DF(MAYA) / DF(DEF) change the default layer, which doesn't go through layer_state_set_user
layer_state_t default_layer_state_set_user(layer_state_t state) {
    send_maya_status(layer_state_cmp(state | layer_state, MAYA));
    return state;
}

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
                                                   KC_TRNS,       KC_TRNS,          KC_ENT,         KC_0 // <-- CHANGED FIRST KEY TO KC_TRNS
  ),

     //SYMBOLS LAYER
    [SYM] = LAYOUT(
 
    UK_GRV,         KC_AMPR,       KC_LBRC,       KC_RBRC,       KC_PERC,             LCTL(KC_V),      LCTL(KC_C),       LCTL(KC_X),    LCTL(KC_Z),      LCTL(KC_Y),      
    KC_EXLM,        UK_DQUO,       KC_COLN,       KC_SCLN,       KC_ASTR,             KC_LEFT,         LSFT_T(KC_DOWN),  LCTL_T(KC_UP), LALT_T(KC_RGHT), U_NTIL,         
    UK_BSLS,        KC_DLR,        KC_LCBR,       KC_RCBR,       UK_HASH,             KC_HOME,         KC_PGDN,          KC_PGUP,       KC_END,          LGUI_T(KC_NO), 
                                                  MO(MOUSE),     KC_DEL,              KC_NO,           KC_TRNS
  ),

       //NAVIGATION LAYER
    [NAV] = LAYOUT(
 
    UK_GRV,           KC_AMPR,           KC_LBRC,          KC_RBRC,          KC_PERC,             LCTL(KC_V),      LCTL(KC_C),       LCTL(KC_X),    LCTL(KC_Z),      LCTL(KC_Y),      
    KC_EXLM,          LALT_T(UK_DQUO),   LCTL_T(KC_COLN),  LSFT_T(KC_SCLN),  KC_ASTR,             KC_LEFT,         KC_DOWN,          KC_UP,         KC_RGHT,         U_NTIL,         
    LGUI_T(UK_BSLS),  KC_DLR,            KC_LCBR,          KC_RCBR,          UK_HASH,             KC_HOME,         KC_PGDN,          KC_PGUP,       KC_END,          KC_NO, 
                                                           KC_TRNS,          KC_TRNS,             KC_ENTER,        MO(MOUSE) // <-- CHANGED SECOND KEY TO KC_TRNS
  ),


     //MOUSE LAYER
    [MOUSE] = LAYOUT(

    QK_BOOT,        KC_NO,             KC_NO,            KC_NO,             KC_NO,             KC_NO,          KC_BTN1,       KC_BTN2,       KC_BTN3,        KC_NO,  
    KC_MPRV,        LALT_T(KC_VOLD),   LCTL_T(KC_VOLU),  LSFT_T(KC_MNXT),   KC_NO,             KC_MS_L,        KC_MS_D,       KC_MS_U,       KC_MS_R,        KC_NO, 
    KC_LGUI,        KC_NO,             KC_NO,            KC_MPLY,           KC_NO,             KC_WH_L,        KC_WH_D,       KC_WH_U,       KC_WH_R,        KC_NO,  
                                                         KC_TRNS,           KC_NO,             KC_NO,          KC_TRNS
  ),
};