#include "gameicons.h"
#include "gui/key.h"
#include "info.h"
#include "alert.h"
#include "tiles.h"
#include "gui/builder.h"
#include "base/misctypes.h"

extern bool saved;
extern miscQdata QMisc;

bool call_gameicons_dialog()
{
	GameIconsDialog().show();
	return true;
}

GameIconsDialog::GameIconsDialog()
{
	memcpy(local_icons, QMisc.icons, sizeof(QMisc.icons));
}

std::shared_ptr<GUI::Widget> GameIconsDialog::view()
{
	using namespace GUI::Builder;
	using namespace GUI::Props;

	for (int q = 0; q < 4; ++q)
	{
		ts_icon[q] = SelTileSwatch(
			tile = local_icons[q],
			cset = q + 6,
			showFlip = false,
			showvals = false,
			onSelectFunc = [&, q](int32_t t, int32_t, int32_t, int32_t)
			{
				local_icons[q] = t;
				ts_icon[q]->setCSet(q + 6);
				ts_icon[q]->sel_color = q + 6;
			}
		);
	}

	window = Window(
		use_vsync = true,
		title = "Game Icons",
		onClose = message::CANCEL,
		Column(
			Row(
				Column(Label("Ring:"),_d),
				Column(Label("0"),ts_icon[0]),
				Column(Label("1"), ts_icon[1]),
				Column(Label("2"), ts_icon[2]),
				Column(Label("3+"), ts_icon[3])
			),
			Row(
				topPadding = 0.5_em,
				vAlign = 1.0,
				spacing = 2_em,
				Button(
					text = "OK",
					minwidth = 90_px,
					onClick = message::OK),
				Button(
					text = "Cancel",
					minwidth = 90_px,
					onClick = message::CANCEL)
			)
		)
	);
	return window;
}

bool GameIconsDialog::handleMessage(const GUI::DialogMessage<message>& msg)
{
	switch (msg.message)
	{
	case message::OK:
		memcpy(QMisc.icons, local_icons, sizeof(QMisc.icons));
		[[fallthrough]];
	case message::CANCEL:
		//change cset 6-9 back to original
		return true;
	}
	return false;
}