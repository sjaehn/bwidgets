/* DialValue.cpp
 * Copyright (C) 2018  Sven Jähnichen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "DialValue.hpp"

namespace BWidgets
{

DialValue::DialValue () :
		DialValue (0.0, 0.0, BWIDGETS_DEFAULT_DIALVALUE_WIDTH, BWIDGETS_DEFAULT_DIALVALUE_HEIGHT,
							  "dialvalue",
							  BWIDGETS_DEFAULT_VALUE, BWIDGETS_DEFAULT_RANGE_MIN, BWIDGETS_DEFAULT_RANGE_MAX, BWIDGETS_DEFAULT_RANGE_STEP,
							  BWIDGETS_DEFAULT_VALUE_FORMAT) {}

DialValue::DialValue (const double x, const double y, const double width, const double height, const std::string& name,
											const double value, const double min, const double max, const double step,
											const std::string& valueFormat) :
	Dial (x, y, width, height, name, value, min, max, step),
	valueDisplay(0, 0.75 * height, width, 0.25 * height, name),
	valFormat (valueFormat)
{
	valueDisplay.setText (BValues::toBString (valueFormat, value));
	add (valueDisplay);
}

DialValue::DialValue (const DialValue& that) :
		Dial (that), valueDisplay (that.valueDisplay), valFormat (that.valFormat)
{
	add (valueDisplay);
}

DialValue::~DialValue () {}

DialValue& DialValue::operator= (const DialValue& that)
{
	release (&valueDisplay);
	valFormat = that.valFormat;
	Dial::operator= (that);
	valueDisplay = that.valueDisplay;
	add (valueDisplay);

	return *this;
}

Widget* DialValue::clone () const {return new DialValue (*this);}

void DialValue::setValue (const double val)
{
	Dial::setValue (val);
	valueDisplay.setText(BValues::toBString (valFormat, value));
}

void DialValue::setValueFormat (const std::string& valueFormat)
{
	valFormat = valueFormat;
	update ();
}

std::string DialValue::getValueFormat () const {return valFormat;}

Label* DialValue::getDisplayLabel () {return &valueDisplay;}

void DialValue::update ()
{
	Dial::update();

	// Update display
	valueDisplay.moveTo (dialCenterX - dialRadius, dialCenterY + 0.7 * dialRadius);
	valueDisplay.setWidth (2 * dialRadius);
	valueDisplay.setHeight (0.5 * dialRadius);
	if (valueDisplay.getFont ()->getFontSize () != 0.4 * dialRadius)
	{
		valueDisplay.getFont ()->setFontSize (0.4 * dialRadius);
		valueDisplay.update ();
	}
	valueDisplay.setText (BValues::toBString (valFormat, value));

}

void DialValue::applyTheme (BStyles::Theme& theme) {applyTheme (theme, name_);}
void DialValue::applyTheme (BStyles::Theme& theme, const std::string& name)
{
	Dial::applyTheme (theme, name);
	valueDisplay.applyTheme (theme, name);
	update ();
}

void DialValue::updateCoords ()
{
	double w = getEffectiveWidth ();
	double h = getEffectiveHeight ();
	dialRadius = (w < h / 1.2 ? w / 2 : h / 2.4);
	dialCenterX = width_ / 2;
	dialCenterY = height_ / 2 - 0.2 * dialRadius;
}

}