"screen_basic.res"
{
	"Background"
	{
		"ControlName"	"MaterialImage"
		"fieldName"		"Background"
		"xpos"			"0"
		"ypos"			"0"
		"zpos"			"-2"
		"wide"			"480"
		"tall"			"240"

		"material"		"vgui/screens/vgui_bg"
	}

	"StartButton"
	{
		"ControlName"	"MaterialButton"
		"fieldName"		"StartButton"
		"xpos"			"78"
		"ypos"			"100"
		"wide"			"324"
		"tall"			"48"
		"autoResize"	"0"
		"pinCorner"		"0"
		"visible"		"1"
		"enabled"		"1"
		"tabPosition"	"2"
		"labelText"		"Start"
		"textAlignment"	"center"
		"dulltext"		"0"
		"brighttext"	"0"
		"Default"		"0"
		"command"		"out1"
		"paintborder"	"0"

		"enabledImage"
		{
			"material"	"vgui/screens/vgui_button_enabled"
			"color" "255 255 255 255"
		}

		"mouseOverImage"
		{
			"material"	"vgui/screens/vgui_button_hover"
			"color" "255 255 255 255"
		}

		"pressedImage"
		{
			"material"	"vgui/screens/vgui_button_pushed"
			"color" "255 255 255 255"
		}

		"disabledImage"
		{
			"material"	"vgui/screens/vgui_button_disabled"
			"color" "255 255 255 255"
		}
	}

	"StopButton"
	{
		"ControlName"	"MaterialButton"
		"fieldName"		"StopButton"
		"xpos"			"78"
		"ypos"			"160"
		"wide"			"324"
		"tall"			"48"
		"autoResize"	"0"
		"pinCorner"		"0"
		"visible"		"1"
		"enabled"		"1"
		"tabPosition"	"2"
		"labelText"		"Stop"
		"textAlignment"	"center"
		"dulltext"		"0"
		"brighttext"	"0"
		"Default"		"0"
		"command"		"out2"
		"paintborder"	"0"

		"enabledImage"
		{
			"material"	"vgui/screens/vgui_button_enabled"
			"color" "255 255 255 255"
		}

		"mouseOverImage"
		{
			"material"	"vgui/screens/vgui_button_hover"
			"color" "255 255 255 255"
		}

		"pressedImage"
		{
			"material"	"vgui/screens/vgui_button_pushed"
			"color" "255 255 255 255"
		}

		"disabledImage"
		{
			"material"	"vgui/screens/vgui_button_disabled"
			"color" "255 255 255 255"
		}
	}
}
