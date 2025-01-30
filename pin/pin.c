#include <stdio.h>
#include "soc/reg_base.h" // DR_REG_GPIO_BASE, DR_REG_IO_MUX_BASE
#include "driver/rtc_io.h" // rtc_gpio_*
#include "pin.h"

// GPIO Matrix Registers - GPIO_OUT_REG, GPIO_OUT_W1TS_REG, ...
// NOTE: Remember to enclose the macro values in parenthesis, as below
#define GPIO_OUT_REG          			(DR_REG_GPIO_BASE+0x04)
#define GPIO_OUT1_REG         			(DR_REG_GPIO_BASE+0x10)
#define GPIO_ENABLE_REG       			(DR_REG_GPIO_BASE+0x20)
#define GPIO_ENABLE1_REG      			(DR_REG_GPIO_BASE+0x2C)
#define GPIO_IN_REG			  			(DR_REG_GPIO_BASE+0x3C)
#define GPIO_IN1_REG	      			(DR_REG_GPIO_BASE+0x40)
#define GPIO_PIN_REG(n)	  	  			(DR_REG_GPIO_BASE+0x88+(n*4))	
#define GPIO_FUNC_OUT_SEL_CFG_REG(n) 	(DR_REG_GPIO_BASE+0x530+(n*4))

// GPIO Register offsets for pad driver and output offset
#define GPIO_PIN_PAD_DRIVER 2
#define GPIO_FUNC_OUT_SEL 8


// IO MUX Register Modifiers
#define IO_MUX_REG(n) (DR_REG_IO_MUX_BASE+PIN_MUX_REG_OFFSET[n])

// IO MUX Register Fields - FUN_WPD, FUN_WPU, ...
#define FUN_WPD  7
#define FUN_WPU  8
#define FUN_IE   9
#define FUN_DRV  11
#define MCU_SEL  13

// Register bit modification macros
#define REG(r) (*(volatile uint32_t *)(r))
#define REG_BITS 32
#define REG_SET_BIT(r,b) (REG(r) |= (1 << b))	// Left-shift 1 by b and bitwise | the bits to r.
#define REG_CLR_BIT(r,b) (REG(r) &= ~(1 << b)) // Left-shift 1 by b, negate that bit, and bitwise & the bits to r.
#define REG_GET_BIT(r,b) ((REG(r) >> b) & 1) // Right-shift the bits in register r by b. Bitwise & 1 with the least significant bit to get the bit value.

// Gives byte offset of IO_MUX Configuration Register
// from base address DR_REG_IO_MUX_BASE
static const uint8_t PIN_MUX_REG_OFFSET[] = {
    0x44, 0x88, 0x40, 0x84, 0x48, 0x6c, 0x60, 0x64, // pin  0- 7
    0x68, 0x54, 0x58, 0x5c, 0x34, 0x38, 0x30, 0x3c, // pin  8-15
    0x4c, 0x50, 0x70, 0x74, 0x78, 0x7c, 0x80, 0x8c, // pin 16-23
    0x90, 0x24, 0x28, 0x2c, 0xFF, 0xFF, 0xFF, 0xFF, // pin 24-31
    0x1c, 0x20, 0x14, 0x18, 0x04, 0x08, 0x0c, 0x10, // pin 32-39
};

// Reset the configuration of a pin to not be an input or an output.
// Pull-up is enabled so the pin does not float. Returns 0 after reset.
int32_t pin_reset(pin_num_t pin)
{
	if (rtc_gpio_is_valid_gpio(pin)) { // hand-off work to RTC subsystem
		rtc_gpio_deinit(pin);
		rtc_gpio_pullup_en(pin);
		rtc_gpio_pulldown_dis(pin);
	}
	// Reset GPIO_PINn_REG: All fields to zero
	REG(GPIO_PIN_REG(pin)) = 0;
	
	// Reset GPIO_FUNCn_OUT_SEL_CFG_REG: GPIO_FUNCn_OUT_SEL=0x100
	REG_SET_BIT(GPIO_FUNC_OUT_SEL_CFG_REG(pin), GPIO_FUNC_OUT_SEL);

	// Reset IO_MUX_x_REG to zero and set MCU_SEL=2, FUN_DRV=2, FUN_WPU=1
	REG(IO_MUX_REG(pin)) = 0;
	REG_SET_BIT(IO_MUX_REG(pin), MCU_SEL);
	REG_SET_BIT(IO_MUX_REG(pin), FUN_WPU);
	REG_SET_BIT(IO_MUX_REG(pin), FUN_DRV);

	// NOTE: By default, pin should not float, save power with FUN_WPU=1

	// Now that the pin is reset, set the output level to zero
	return pin_set_level(pin, 0);
}

// Enable or disable a pull-up resistor on the specified pin.
int32_t pin_pullup(pin_num_t pin, bool enable)
{
	// hand-off work to RTC subsystem
	if (rtc_gpio_is_valid_gpio(pin)) { 
		if (enable) return rtc_gpio_pullup_en(pin);
		else return rtc_gpio_pullup_dis(pin);
	}
	// Set or clear the FUN_WPU bit in an IO_MUX register for the specified pin
	if(enable){
		REG_SET_BIT(IO_MUX_REG(pin), FUN_WPU);
	}
	else{
		REG_CLR_BIT(IO_MUX_REG(pin), FUN_WPU);
	}
	return 0;
}

// Enable or disable a pull-down resistor on the specified pin.
int32_t pin_pulldown(pin_num_t pin, bool enable)
{
	// hand-off work to RTC subsystem
	if (rtc_gpio_is_valid_gpio(pin)) { 
		if (enable) return rtc_gpio_pulldown_en(pin);
		else return rtc_gpio_pulldown_dis(pin);
	}
	// Set or clear the FUN_WPD bit in an IO_MUX register based on function parameters.
	if(enable){
		REG_SET_BIT(IO_MUX_REG(pin), FUN_WPD);
	}
	else{
		REG_CLR_BIT(IO_MUX_REG(pin), FUN_WPD);
	}
	return 0;
}

// Enable or disable the specified pin as an input signal.
int32_t pin_input(pin_num_t pin, bool enable)
{
	// Set or clear the FUN_IE bit in an IO_MUX register based on function parameters.
	if(enable){
		REG_SET_BIT(IO_MUX_REG(pin), FUN_IE);
	}
	else{
		REG_CLR_BIT(IO_MUX_REG(pin), FUN_IE);
	}
	return 0;
}

// Enable or disable the specified pin as an output signal.
int32_t pin_output(pin_num_t pin, bool enable)
{
	// Set or clear the I/O pin bit in the ENABLE or ENABLE1 register based on function parameters.
	if(pin < REG_BITS){
		if(enable){
			REG_SET_BIT(GPIO_ENABLE_REG, pin);
		}
		else{
			REG_CLR_BIT(GPIO_ENABLE_REG, pin);
		}
	}
	else{
		if(enable){
			REG_SET_BIT(GPIO_ENABLE1_REG, (pin-REG_BITS));
		}
		else{
			REG_CLR_BIT(GPIO_ENABLE1_REG, (pin-REG_BITS));
		}
	}
	return 0;
}

// Enable or disable the specified pin as an open-drain signal.
int32_t pin_odrain(pin_num_t pin, bool enable)
{
	// Set or clear the PAD_DRIVER bit in a PIN register based on function parameters.
	if(enable){
		REG_SET_BIT(GPIO_PIN_REG(pin), GPIO_PIN_PAD_DRIVER);
	}
	else{
		REG_CLR_BIT(GPIO_PIN_REG(pin), GPIO_PIN_PAD_DRIVER);
	}
	return 0;
}

// Sets the output signal level if the pin is configured as an output.
int32_t pin_set_level(pin_num_t pin, int32_t level)
{	
	// Check which register to modify by the pin number. If the pin number is less than 32, 
	// modify the OUT register. Otherwise, modify the OUT1 register. Determine if the level is a one
	// or zero and set or clear the bit in the register respectively.
	if(pin < REG_BITS){
		if(level){
			REG_SET_BIT(GPIO_OUT_REG, pin);
		}
		else{
			REG_CLR_BIT(GPIO_OUT_REG, pin);
		}
	}
	else{
		if(level){
			REG_SET_BIT(GPIO_OUT1_REG, (pin-REG_BITS));
		}
		else{
			REG_CLR_BIT(GPIO_OUT1_REG, (pin-REG_BITS));
		}
	}
	return 0;
}

// Gets the input signal level if the pin is configured as an input.
int32_t pin_get_level(pin_num_t pin)
{
	// Determine which register to read from based on the pin number. If the pin number is less than 32,
	// read from the IN register. Otherwise, read from the IN1 register. Use the REG_GET_BIT macro to get the
	// value of the pin level from the register.
	if(pin < REG_BITS){
		return REG_GET_BIT(GPIO_IN_REG, pin);
	}
	else{
		return REG_GET_BIT(GPIO_IN1_REG, (pin-REG_BITS));
	}
}

// Get the value of the input registers, one pin per bit.
// The two 32-bit input registers are concatenated into a uint64_t.
// The concatenated value is then returned.
uint64_t pin_get_in_reg(void)
{
	uint64_t in_reg = 0;
	in_reg = REG(GPIO_IN1_REG);
	in_reg = in_reg << REG_BITS;
	in_reg |= REG(GPIO_IN_REG);
	return in_reg;
}

// Get the value of the output registers, one pin per bit.
// The two 32-bit output registers are concatenated into a uint64_t.
// The concatenated value is then returned.
uint64_t pin_get_out_reg(void)
{
	uint64_t out_reg = 0;
	out_reg = REG(GPIO_OUT1_REG);
	out_reg = out_reg << REG_BITS;
	out_reg |= REG(GPIO_OUT_REG);
	return out_reg;
}
