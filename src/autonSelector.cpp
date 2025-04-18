#include "main.h"
#include "autonSelector/autonSelector.h"

namespace autonSelector {

int auton;
int autonCount;
const char *btnmMap[] = {"ringSide", "goalSide", "SAWP"};

lv_obj_t *tabview;
lv_obj_t *redCont;
lv_obj_t *blueCont;
lv_obj_t *selectorScreen;
lv_obj_t *homeScreen;
lv_obj_t *homeScreenLabel;

lv_obj_t *selectedRedBtn = nullptr;
lv_obj_t *selectedBlueBtn = nullptr;
lv_obj_t *selectedSkillsBtn = nullptr;

lv_color_t redDefaultColor = lv_palette_main(LV_PALETTE_RED);
lv_color_t blueDefaultColor = lv_palette_main(LV_PALETTE_BLUE);
lv_color_t greyDefaultColor = lv_palette_main(LV_PALETTE_GREY);

std::vector<lv_obj_t*> allButtons;
std::unordered_map<lv_obj_t*, lv_color_t> buttonDefaults;

// lv_obj_t* debugScreen = NULL;  // Debug screen object (commented out for now)
// lv_obj_t* debugLabels[10];  // Debug labels (commented out for now)

// Commenting out the debug screen creation for now
/*
void create_debug_screen() {
    if (debugScreen) {
        return; // Debug screen already created, no need to recreate
    }

    debugScreen = lv_obj_create(NULL); // Create a new screen if it doesn't exist
    lv_obj_set_layout(debugScreen, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(debugScreen, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_column(debugScreen, 5, 0);
    lv_obj_set_style_pad_all(debugScreen, 10, 0);

    // Create labels for displaying debug information
    for (int i = 0; i < 10; i++) {
        debugLabels[i] = lv_label_create(debugScreen);
        lv_label_set_text(debugLabels[i], "...");
    }

    // Add Back button to go back to the main screen
    lv_obj_t* backBtn = lv_btn_create(debugScreen);
    lv_obj_set_size(backBtn, 140, 40);
    lv_obj_align(backBtn, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_radius(backBtn, 10, 0);
    lv_obj_set_style_bg_color(backBtn, lv_palette_main(LV_PALETTE_GREY), 0);

    lv_obj_t* backLbl = lv_label_create(backBtn);
    lv_label_set_text(backLbl, "Back");
    lv_obj_center(backLbl);

    lv_obj_add_event_cb(backBtn, [](lv_event_t* e) {
        lv_scr_load(homeScreen); // Go back to the home screen when the Back button is pressed
    }, LV_EVENT_CLICKED, NULL);
}
*/

// Commenting out the debug screen loading functionality for now
/*
void load_debug_screen() {
    create_debug_screen();  // Ensure debug screen is created
    lv_scr_load(debugScreen); // Load the debug screen
}
*/

// Highlight the selected button
void update_selected_btn(lv_obj_t *&currentSelected, lv_obj_t *newSelected, lv_color_t defaultColor) {
    for (auto btn : allButtons) {
        lv_obj_set_style_bg_color(btn, buttonDefaults[btn], 0);
    }
    lv_obj_set_style_bg_color(newSelected, lv_palette_main(LV_PALETTE_GREEN), 0);
    currentSelected = newSelected;
}

// Reusable button creator with integer index
static lv_obj_t *create_btn(lv_obj_t *parent, const char *labelText, lv_event_cb_t cb, lv_color_t defaultColor, int index = -1) {
    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_size(btn, 150, 50);
    lv_obj_set_style_radius(btn, 12, 0);
    lv_obj_set_style_bg_color(btn, defaultColor, 0);
    lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);

    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, labelText);
    lv_obj_center(label);

    if (index >= 0)
        lv_obj_add_event_cb(btn, cb, LV_EVENT_CLICKED, (void*)(intptr_t)index);
    else
        lv_obj_add_event_cb(btn, cb, LV_EVENT_CLICKED, nullptr);

    allButtons.push_back(btn);
    buttonDefaults[btn] = defaultColor;

    return btn;
}

// Red selection handler
static void redBtnmAction(lv_event_t *e) {
    lv_obj_t *btn = lv_event_get_target(e);
    update_selected_btn(selectedRedBtn, btn, redDefaultColor);

    int index = (int)(intptr_t)lv_event_get_user_data(e);
    auton = index + 1; // Red autons are positive
}

// Blue selection handler
static void blueBtnmAction(lv_event_t *e) {
    lv_obj_t *btn = lv_event_get_target(e);
    update_selected_btn(selectedBlueBtn, btn, blueDefaultColor);

    int index = (int)(intptr_t)lv_event_get_user_data(e);
    auton = -(index + 1); // Blue autons are negative
}

// Skills button action
static void skillsBtnAction(lv_event_t *e) {
    lv_obj_t *btn = lv_event_get_target(e);
    update_selected_btn(selectedSkillsBtn, btn, greyDefaultColor);
    auton = 0; // Skills auto
}

// Save button action: go to full-screen home screen
static void saveBtnAction(lv_event_t *e) {
    const char *autoText;
    switch (auton) {
        case 0: autoText = "Skills"; break;
        case 1: autoText = "Red Ring"; break;
        case 2: autoText = "Red Goal"; break;
        case 3: autoText = "Red SAWP"; break;
        case -1: autoText = "Blue Ring"; break;
        case -2: autoText = "Blue Goal"; break;
        case -3: autoText = "Blue SAWP"; break;
        default: autoText = "None"; break;
    }

    if (!homeScreen) {
        homeScreen = lv_obj_create(NULL);
        lv_obj_set_style_bg_color(homeScreen, lv_color_black(), 0);
        lv_obj_set_size(homeScreen, LV_HOR_RES, LV_VER_RES);

        // Team name label
        lv_obj_t *teamNameLabel = lv_label_create(homeScreen);
        lv_label_set_text(teamNameLabel, "25600Y x blackbird");
        lv_obj_set_style_text_color(teamNameLabel, lv_color_white(), 0);
        lv_obj_set_style_text_font(teamNameLabel, &lv_font_montserrat_48, 0);
        lv_obj_align(teamNameLabel, LV_ALIGN_TOP_MID, 0, 40); // more space at the top

        // Selected auto label
        homeScreenLabel = lv_label_create(homeScreen);
        lv_obj_set_style_text_color(homeScreenLabel, lv_color_white(), 0);
        lv_obj_set_style_text_font(homeScreenLabel, &lv_font_montserrat_20, 0);
        lv_obj_align(homeScreenLabel, LV_ALIGN_CENTER, 0, 0);

        // Two buttons side by side (bottom, smaller and spaced)
				lv_obj_t *buttonCont = lv_obj_create(homeScreen);
				lv_obj_set_size(buttonCont, LV_HOR_RES - 20, 70);  // Smaller height
				lv_obj_align(buttonCont, LV_ALIGN_BOTTOM_MID, 0, -10);  // Slightly above bottom

				// Make container black and remove borders to blend into background
				lv_obj_set_style_bg_color(buttonCont, lv_color_black(), 0);
				lv_obj_set_style_border_width(buttonCont, 0, 0);
				lv_obj_set_style_pad_all(buttonCont, 0, 0);

				lv_obj_set_layout(buttonCont, LV_LAYOUT_FLEX);
				lv_obj_set_flex_flow(buttonCont, LV_FLEX_FLOW_ROW);
				lv_obj_set_flex_align(buttonCont, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

				// Button 1: Back to Selector
				lv_obj_t *backBtn = lv_btn_create(buttonCont);
				lv_obj_set_size(backBtn, 140, 40);
				lv_obj_set_style_radius(backBtn, 10, 0);
				lv_obj_set_style_bg_color(backBtn, lv_palette_main(LV_PALETTE_GREY), 0);

				lv_obj_t *label1 = lv_label_create(backBtn);
				lv_label_set_text(label1, "Back to Selector");
				lv_obj_center(label1);

				lv_obj_add_event_cb(backBtn, [](lv_event_t *e) {
						lv_scr_load(selectorScreen);
				}, LV_EVENT_CLICKED, NULL);

				// Button 2: Debug Info (close UI to see Brain screen)
				lv_obj_t *debugBtn = lv_btn_create(buttonCont);
				lv_obj_set_size(debugBtn, 140, 40);
				lv_obj_set_style_radius(debugBtn, 10, 0);
				lv_obj_set_style_bg_color(debugBtn, lv_palette_main(LV_PALETTE_BLUE), 0);

				lv_obj_t *label2 = lv_label_create(debugBtn);
				lv_label_set_text(label2, "Debug Info");
				lv_obj_center(label2);

				// lv_obj_add_event_cb(debugBtn, [](lv_event_t *e) {
				// 		lv_scr_load(NULL); // Clear LVGL screen to reveal Brain LCD output
				// }, LV_EVENT_CLICKED, NULL);
    }

    if (homeScreenLabel) {
        lv_label_set_text_fmt(homeScreenLabel, "Selected Auto: %s", autoText);
    }

    lv_scr_load(homeScreen);
}

void init(int hue, int default_auton, const char **autons) {
    int i = 0;
    do {
        btnmMap[i] = autons[i];
        i++;
    } while (strcmp(autons[i], "") != 0);
    autonCount = i;
    auton = default_auton;

    selectorScreen = lv_scr_act();

    lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    tabview = lv_tabview_create(selectorScreen, LV_DIR_TOP, 50);

    lv_obj_t *redTab = lv_tabview_add_tab(tabview, "Red");
    lv_obj_t *blueTab = lv_tabview_add_tab(tabview, "Blue");
    lv_obj_t *skillsTab = lv_tabview_add_tab(tabview, "Skills");
    lv_obj_t *saveTab = lv_tabview_add_tab(tabview, "Save");

    // Red tab
    redCont = lv_obj_create(redTab);
    lv_obj_set_size(redCont, 450, 200);
    lv_obj_center(redCont);
    lv_obj_set_layout(redCont, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(redCont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(redCont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    create_btn(redCont, "Red Ring", redBtnmAction, redDefaultColor, 0);
    create_btn(redCont, "Red Goal", redBtnmAction, redDefaultColor, 1);
    create_btn(redCont, "Red SAWP", redBtnmAction, redDefaultColor, 2);

    // Blue tab
    blueCont = lv_obj_create(blueTab);
    lv_obj_set_size(blueCont, 450, 200);
    lv_obj_center(blueCont);
    lv_obj_set_layout(blueCont, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(blueCont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(blueCont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    create_btn(blueCont, "Blue Ring", blueBtnmAction, blueDefaultColor, 0);
    create_btn(blueCont, "Blue Goal", blueBtnmAction, blueDefaultColor, 1);
    create_btn(blueCont, "Blue SAWP", blueBtnmAction, blueDefaultColor, 2);

    // Skills tab
    lv_obj_t *skillsCont = lv_obj_create(skillsTab);
    lv_obj_set_size(skillsCont, 450, 200);
    lv_obj_center(skillsCont);
    lv_obj_set_layout(skillsCont, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(skillsCont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(skillsCont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    create_btn(skillsCont, "Skills", skillsBtnAction, greyDefaultColor);

    // Save tab
    lv_obj_t *saveCont = lv_obj_create(saveTab);
    lv_obj_set_size(saveCont, 450, 200);
    lv_obj_center(saveCont);
    lv_obj_set_layout(saveCont, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(saveCont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(saveCont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    create_btn(saveCont, "Save", saveBtnAction, greyDefaultColor);
}
}