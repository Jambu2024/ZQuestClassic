#ifndef ZC_DIALOG_GAMEICONS_H_
#define ZC_DIALOG_GAMEICONS_H_

#include <gui/dialog.h>
#include <gui/label.h>
#include <zq/gui/seltile_swatch.h>
#include <gui/window.h>
#include <functional>
#include <string_view>

bool call_gameicons_dialog();

class GameIconsDialog : public GUI::Dialog<GameIconsDialog>
{
public:
	enum class message
	{
		REFR_INFO, OK, CANCEL
	};

	std::shared_ptr<GUI::Widget> view() override;
	std::shared_ptr<GUI::SelTileSwatch> ts_icon[4];
	bool handleMessage(const GUI::DialogMessage<message>& msg);

private:
	GameIconsDialog();
	std::shared_ptr<GUI::Window> window;
	int32_t local_icons[4];
	friend bool call_gameicons_dialog();
};

#endif