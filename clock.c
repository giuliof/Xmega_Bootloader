#include <avr/io.h>
#include "clock.h"

// Set up PLL driven by internal 2MHz oscillator using 32kHz DFLL reference
void initclock() {
  /** DFLL calibration setup **/
  // Enable the internal 32KHz oscillator for DFLL reference
  OSC.CTRL |= OSC_RC32KEN_bm;
  while (!(OSC.STATUS & OSC_RC32KRDY_bm))
    ;  // Wait for stabilization
  // Enable DFLL
  DFLLRC2M.CTRL = DFLL_ENABLE_bm;

  /** PLL setup **/
  // Apply multiplying factor x1 (2MHz x 1 = 2MHz)
  OSC.PLLCTRL = 1;
  // Turn on PLL
  OSC.CTRL = OSC_PLLEN_bm;
  while (!(OSC.STATUS & OSC_PLLRDY_bm))
    ;  // Is PLL clk rdy to go?

  CCP = 0xD8;  // Unlock secure register
  CLK.CTRL = CLK_SCLKSEL_PLL_gc;
}