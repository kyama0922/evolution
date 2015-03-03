#ifndef __EVOLUTION_ETC__
#define __EVOLUTION_ETC__

//EVOLUTIONユーティリティ
#include "evolution-utility/evolution_utility.h"

//EVOLUTIONネットワーク機能
#include "evolution-network/evolution_network.h"

#if defined(WIN32) || defined(WIN64)
//EVOLUTIONグラフィック機能
#include "evolution-graphic/evolution_graphic.h"

//EVOLUTIONインプット機能
#include "evolution-input/evolution_input.h"

//EVOLUTIONサウンド機能
#include "evolution-sound/evolution_sound.h"

//EVOLUTIONフレームワーク
#include "evolution-framework/evolution_framework_interface.h"
#endif

#endif //!__EVOLUTION_ETC__