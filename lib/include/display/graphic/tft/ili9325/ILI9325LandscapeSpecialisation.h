/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

#include "display/graphic/tft/ili9325/commands/AllCommands.h"


namespace stm32plus {
	namespace display {


		/**
		 * Specialisation of ILI9325Orientation for the panel in landscape mode.
		 * @tparam TAccessMode the access mode implementation, e.g. FSMC
		 */

		template<class TAccessMode>
		class ILI9325Orientation<LANDSCAPE,TAccessMode> {

			private:
				TAccessMode& _accessMode;

			protected:
				ILI9325Orientation(TAccessMode& accessMode);

				constexpr uint16_t getOrientationEntryMode() const;

		  public:
				constexpr int16_t getWidth() const;
				constexpr int16_t getHeight() const;

				void moveTo(int16_t xstart,int16_t ystart,int16_t xend,int16_t yend) const;
				void moveTo(const Rectangle& rc) const;
				void moveX(int16_t xstart,int16_t xend) const;
				void moveY(int16_t ystart,int16_t yend) const;

				void setScrollPosition(int16_t scrollPosition);
		};


		/**
		 * Constructor
		 */

		template<class TAccessMode>
		inline ILI9325Orientation<LANDSCAPE,TAccessMode>::ILI9325Orientation(TAccessMode& accessMode)
			: _accessMode(accessMode) {
		}


		/**
		 * Get the register setting for portrait mode
		 * @return The entry mode register setting for landscape
		 */

		template<class TAccessMode>
		constexpr inline uint16_t ILI9325Orientation<LANDSCAPE,TAccessMode>::getOrientationEntryMode() const {
			return ili9325::EntryModeCmd::AM_VERTICAL | ili9325::EntryModeCmd::ID_HINC_VDEC;
		}


		/**
		 * Get the width in pixels
		 * @return 320px
		 */

		template<class TAccessMode>
		constexpr inline int16_t ILI9325Orientation<LANDSCAPE,TAccessMode>::getWidth() const {
		  return 320;
		}


		/**
		 * Get the height in pixels
		 * @return 240px
		 */

		template<class TAccessMode>
		constexpr inline int16_t ILI9325Orientation<LANDSCAPE,TAccessMode>::getHeight() const {
		  return 240;
		}


		/**
		 * Move the display output rectangle
		 * @param rc The display output rectangle
		 */

		template<class TAccessMode>
		inline void ILI9325Orientation<LANDSCAPE,TAccessMode>::moveTo(const Rectangle& rc) const {
			moveTo(rc.X,rc.Y,rc.X+rc.Width-1,rc.Y+rc.Height-1);
		}


		/**
		 * Move the display rectangle to the rectangle described by the co-ordinates
		 * @param xstart starting X position
		 * @param ystart starting Y position
		 * @param xend ending X position
		 * @param yend ending Y position
		 */

		template<class TAccessMode>
		inline void ILI9325Orientation<LANDSCAPE,TAccessMode>::moveTo(int16_t xstart,int16_t ystart,int16_t xend,int16_t yend) const {

			this->_accessMode.writeCommand(ili9325::HorizontalRAMPositionStartCmd::Opcode,ystart);
			this->_accessMode.writeCommand(ili9325::HorizontalRAMPositionEndCmd::Opcode,yend);

			this->_accessMode.writeCommand(ili9325::VerticalRAMPositionEndCmd::Opcode,319-xstart);
			this->_accessMode.writeCommand(ili9325::VerticalRAMPositionStartCmd::Opcode,319-xend);

			this->_accessMode.writeCommand(ili9325::HorizontalAddressCmd::Opcode,ystart);
			this->_accessMode.writeCommand(ili9325::VerticalAddressCmd::Opcode,319-xstart);
		}


		/**
		 * Move the X position
		 * @param xstart The new X start position
		 * @param xend The new X end position
		 */

		template<class TAccessMode>
		inline void ILI9325Orientation<LANDSCAPE,TAccessMode>::moveX(int16_t xstart,int16_t xend) const {
			this->_accessMode.writeCommand(ili9325::VerticalRAMPositionEndCmd::Opcode,319-xstart);
			this->_accessMode.writeCommand(ili9325::VerticalRAMPositionStartCmd::Opcode,319-xend);
			this->_accessMode.writeCommand(ili9325::VerticalAddressCmd::Opcode,319-xstart);
		}


		/**
		 * Move the Y position
		 * @param ystart The new Y start position
		 * @param yend The new Y end position
		 */

		template<class TAccessMode>
		inline void ILI9325Orientation<LANDSCAPE,TAccessMode>::moveY(int16_t ystart,int16_t yend) const {
			this->_accessMode.writeCommand(ili9325::HorizontalRAMPositionStartCmd::Opcode,ystart);
			this->_accessMode.writeCommand(ili9325::HorizontalRAMPositionEndCmd::Opcode,yend);
			this->_accessMode.writeCommand(ili9325::HorizontalAddressCmd::Opcode,ystart);
		}


		/**
		 * Set a vertical scroll position
		 * @param scrollPosition The new scroll position
		 */

		template<class TAccessMode>
		inline void ILI9325Orientation<LANDSCAPE,TAccessMode>::setScrollPosition(int16_t scrollPosition) {

			if(scrollPosition<0)
        scrollPosition+=320;
      else if(scrollPosition>319)
        scrollPosition-=320;

      // write to the register

      this->_accessMode.writeCommand(ili9325::GateScanControlScrollCmd::Opcode,scrollPosition);
		}
	}
}

