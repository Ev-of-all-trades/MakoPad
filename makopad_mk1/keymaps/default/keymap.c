#include QMK_KEYBOARD_H

typedef enum {
    ENC_VOLUME,
    ENC_SCROLL,
    ENC_BRIGHTNESS
} encoder_mode_t;

encoder_mode_t encoder_mode = ENC_VOLUME;

void keyboard_post_init_user(void) {
    setPinInputHigh(GP0);
}


enum layers {
    _BASE,
    _FRC,
    _DS,
    _LIMELITE
};


enum custom_keycodes {
    FRC_BUILD = SAFE_RANGE,
    FRC_DEPLOY,
    FRC_SIMULATE,
    FRC_DEBUG,
    FRC_RIOLOG,
    FRC_SUFFLEBOARD,

    DS_ENABLE,
    DS_DISABLE,
    DS_TELEOP,
    DS_AUTO,
    DS_TEST,
    DS_ESTOP,
    DS_ASTOP,

    LIMELIGHT_LEFT,
    LIMELIGHT_FRONT,
    LIMELIGHT_RIGHT
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_ortho_2x3(
        KC_A,       KC_B,       KC_C,
        KC_D,       KC_E,       KC_F
    ),

    [_FRC] = LAYOUT_ortho_2x3(
        FRC_BUILD,          FRC_DEPLOY,        FRC_SIMULATE,
        FRC_DEBUG,          FRC_RIOLOG,        FRC_SUFFLEBOARD
    ),  

    [_DS] = LAYOUT_ortho_2x3(
        DS_ENABLE,          DS_DISABLE,        DS_TELEOP,
        DS_AUTO,            DS_TEST,           DS_ESTOP
    ),

    [_LIMELITE] = LAYOUT_ortho_2x3(
        LIMELIGHT_LEFT,     LIMELIGHT_FRONT,   LIMELIGHT_RIGHT,
        KC_NO,              KC_NO,             KC_NO
    )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed) {

        switch (keycode) {

            case FRC_BUILD:
                tap_code16(LCTL(LALT(KC_B)));
                return false;

            case FRC_DEPLOY:
                tap_code16(LCTL(LALT(KC_D)));
                return false;

            case FRC_SIMULATE:
                tap_code16(LCTL(LALT(KC_S)));
                return false;

            case FRC_DEBUG:
                tap_code16(LCTL(LALT(KC_D)));
                return false;

            case FRC_RIOLOG:
                tap_code16(LCTL(LALT(KC_R)));
                return false;

            case FRC_SHUFFLEBOARD:
                tap_code16(LCTL(LALT(KC_M)));
                return false;

            case DS_ENABLE:
                tap_code16(LCTL(LALT(KC_E)));
                return false;

            case DS_DISABLE:
                tap_code16(LCTL(LALT(KC_D)));
                return false;

            case DS_TELEOP:
                tap_code16(LCTL(LALT(KC_T)));
                return false;

            case DS_AUTO:
                tap_code16(LCTL(LALT(KC_A)));
                return false;

            case DS_TEST:
                tap_code16(LCTL(LALT(KC_T)));
                return false;

            case DS_ESTOP:
                tap_code16(KC_SPC);
                return false;

            case DS_ASTOP:
                tap_code16(KC_BSPC);
                return false;

            case DS_REFRESH:
                tap_code16(LCTL(LALT(KC_L)))
                return false;

            case LIMELIGHT_LEFT:
                SEND_STRING("10.51.99.11:5801");
                return false;

            case LIMELIGHT_FRONT:
                SEND_STRING("10.51.99.12:5801");
                return false;

            case LIMELIGHT_RIGHT:
                SEND_STRING("10.51.99.13:5801");
                return false;
        }
    }

    return true;
}


bool encoder_update_user(uint8_t index, bool clockwise) {

    // We only have one encoder.
    if (index != 0) {
        return false;
    }

    if (!readPin(GP0)) {

        if (clockwise) {

            // Move to the next encoder function.
            encoder_mode++;

            // Wrap back to volume after brightness.
            if (encoder_mode > ENC_BRIGHTNESS) {
                encoder_mode = ENC_VOLUME;
            }

        } else {

            // Move to the previous encoder function.
            if (encoder_mode == ENC_VOLUME) {
                encoder_mode = ENC_BRIGHTNESS;
            } else {
                encoder_mode--;
            }
        }

        // Do not perform the normal encoder action.
        return false;
    }

    switch (encoder_mode) {

        case ENC_VOLUME:

            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }

            break;

        case ENC_SCROLL:

            if (clockwise) {
                tap_code(KC_WH_D);
            } else {
                tap_code(KC_WH_U);
            }

            break;

        case ENC_BRIGHTNESS:

            if (clockwise) {
                tap_code(KC_BRIU);
            } else {
                tap_code(KC_BRID);
            }

            break;
    }

    return false;
}


bool dip_switch_update_user(uint8_t index, bool active) {

    // Only act when the switch becomes active.
    if (!active) {
        return true;
    }

    uint8_t current_layer =
        get_highest_layer(default_layer_state | layer_state);

    switch (index) {

        case 0:

            layer_move(
                (current_layer + 1) % _LAYER_COUNT
            );

            break;

        case 1:

            layer_move(
                (current_layer + _LAYER_COUNT - 1)
                % _LAYER_COUNT
            );

            break;
    }

    return true;
}