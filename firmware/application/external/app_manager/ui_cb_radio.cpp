#include "ui.hpp"
#include "ui_navigation.hpp"

namespace ui::external_app::cb_radio {
void initialize_app(ui::NavigationView& nav) {
    nav.push<CbRadioAppView>();  // Ensure `CbRadioAppView` is implemented
}
}  // namespace ui::external_app::cb_radio

extern "C" {

__attribute__((section(".external_app.app_cb_radio.application_information"), used)) application_information_t _application_information_cb_radio = {
    /*.memory_location = */ (uint8_t*)0x00000000,
    /*.externalAppEntry = */ ui::external_app::cb_radio::initialize_app,
    /*.header_version = */ CURRENT_HEADER_VERSION,
    /*.app_version = */ VERSION_MD5,

    /*.app_name = */ "CB Radio Australia",
    /*.bitmap_data = */ {
        0xE0, 0x00, 0x10, 0x01, 0x10, 0x01, 0x1F, 0x1F,  // Replace with an appropriate icon
    },
    /*.icon_color = */ ui::Color::yellow().v,  // Change color to preference
    /*.menu_location = */ app_location_t::RADIO,  // Place in the Radio category
    /*.desired_menu_position = */ -1,

    /*.m4_app_tag = portapack::spi_flash::image_tag_none */ {0, 0, 0, 0},
    /*.m4_app_offset = */ 0x00000000,  // Will be filled at compile time
};
}
