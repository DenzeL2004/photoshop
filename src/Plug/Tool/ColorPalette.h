/**
 * @file ColorPalette.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 *
 * @brief
 *
 * @version 0.1
 * @date 2023-11-15
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __PLUG_TOOL_COLOR_PALETTE_H
#define __PLUG_TOOL_COLOR_PALETTE_H

#include "Plug/Color.h"

namespace plug {

/**
 * @brief Palette of tool colors
 */
class ColorPalette {
public:
  /**
   * @brief Get active foreground color
   *
   * @return Active foreground color
   */
  Color getFGColor(void) const;

  /**
   * @brief Get active background color
   *
   * @return Active background color
   */
  Color getBGColor(void) const;

  /**
   * @brief Set new foreground color
   *
   * @param[in] new_fg_color  New value of background color
   */
  void setFGColor(Color new_fg_color);

  /**
   * @brief Set new background color
   *
   * @param[in] new_bg_color  New value of background color
   */
  void setBGColor(Color new_bg_color);
};

} // namespace plug

#endif /* ColorPalette.h */
