#ifndef _APP_H_
#define _APP_H_

#include "Plug/Math.h"
#include "Impl/Util/Sfml.h"

#include "AppConfig.h"

#include "Impl/RenderTarget/SfmlRenderTarget/RenderTarget.h"
#include "Impl/Graphic/Graphic.h"

#include "Impl/TransformStack/TransformStack.h"

#include "Impl/LayoutBox/BaseLayoutBox/BaseLayoutBox.h"
#include "Impl/Widget/Widget.h"

#include "Impl/Widget/Window/Window.h"
#include "Impl/Widget/Frame/Frame.h"
#include "Impl/Widget/Button/Button.h"

#include "Impl/Canvas/Canvas.h"

#include "Impl/Widget/CanvasManager/CanvasManager.h"

#include "Impl/Tool/ColorPalette/ColorPalette.h"

#include "Impl/Tool/Filters/FilterPalette.h"

void useApp();

#endif