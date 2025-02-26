/*
 * CB Radio App for HackRF PortaPack Mayhem Firmware
 * Turns the HackRF into a working CB radio with scanning, push-to-talk (PTT), and channel selection
 */

#include "ui_cb_radio.hpp"
#include "baseband_api.hpp"
#include "portapack.hpp"
#include "ui_freqman.hpp"

using namespace portapack;

namespace ui {

CBRadioAppView::CBRadioAppView(NavigationView& nav)
    : nav_{nav} {
    baseband::run_image(portapack::spi_flash::image_tag_capture);

    add_children({
        &labels,
        &rssi,
        &channel,
        &field_frequency,
        &field_frequency_step,
        &field_rf_amp,
        &field_lna,
        &field_vga,
        &option_bandwidth,
        &option_format,
        &check_trim,
        &waterfall,
    });

    field_frequency_step.set_by_value(receiver_model.frequency_step());
    field_frequency_step.on_change = [this](size_t, OptionsField::value_t v) {
        receiver_model.set_frequency_step(v);
        this->field_frequency.set_step(v);
    };

    receiver_model.enable();
}

CBRadioAppView::~CBRadioAppView() {
    receiver_model.disable();
    baseband::shutdown();
}

void CBRadioAppView::set_parent_rect(const Rect new_parent_rect) {
    View::set_parent_rect(new_parent_rect);

    ui::Rect waterfall_rect{0, header_height, new_parent_rect.width(), new_parent_rect.height() - header_height};
    waterfall.set_parent_rect(waterfall_rect);
}

void CBRadioAppView::focus() {
    channel.focus();
}

} /* namespace ui */
