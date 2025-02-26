#include "app.h"
#include "ui.h"
#include "radio.h"
#include "audio.h"
#include "storage.h"

#define CB_BAND_START 26965000  // Channel 1 (26.965 MHz)
#define CB_BAND_END   27405000  // Channel 40 (27.405 MHz)
#define CHANNEL_STEP  10000     // 10 kHz channel spacing

static int current_channel = 1;
bool ptt_active = false;

void scan_cb_channels();
void select_channel(int channel);
void on_ptt_pressed();
void on_ptt_released();
void exit_cb_radio_app();

void scan_cb_channels() {
    for (int i = 1; i <= 40; i++) {
        int freq = CB_BAND_START + (i - 1) * CHANNEL_STEP;
        if (is_signal_active(freq)) {
            display_active_channel(i, "CB Channel");
        }
    }
}

void select_channel(int channel) {
    if (channel < 1 || channel > 40) return;
    current_channel = channel;
    tune_hackrf_to(CB_BAND_START + (channel - 1) * CHANNEL_STEP);
    display_selected_channel(channel, "CB Channel Selected");
}

void on_ptt_pressed() {
    if (!ptt_active) {
        ptt_active = true;
        enable_transmission();
        display_status("Transmitting...");
    }
}

void on_ptt_released() {
    if (ptt_active) {
        ptt_active = false;
        disable_transmission();
        display_status("Listening...");
    }
}

void exit_cb_radio_app() {
    return_to_main_menu();
}

// Register the app in the menu
void setup_cb_radio_app() {
    display_status("CB Radio App Loaded");
    select_channel(1);  // Start on Channel 1
}

REGISTER_APP(cb_radio_app, "CB Radio Australia", setup_cb_radio_app, "cb_radio_aus.png");
