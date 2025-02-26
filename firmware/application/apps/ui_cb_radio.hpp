#ifndef UI_CB_RADIO_HPP
#define UI_CB_RADIO_HPP

#include "navigation_view.hpp"
#include "view.hpp"

namespace ui {

class CBRadioAppView : public View {
public:
    explicit CBRadioAppView(NavigationView& nav);
    virtual ~CBRadioAppView();

    virtual void set_parent_rect(const Rect new_parent_rect);
    virtual void focus();

private:
    NavigationView& nav_;
};

} /* namespace ui */

#endif /* UI_CB_RADIO_HPP */
