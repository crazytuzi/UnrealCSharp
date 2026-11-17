#include "Binding/Class/TBindingClassBuilder.inl"
#include "Macro/NamespaceMacro.h"
#include "UEVersion.h"

BINDING_CLASS(EKeys)

namespace
{
	struct FRegisterKeys
	{
		FRegisterKeys()
		{
			TBindingClassBuilder<EKeys>(NAMESPACE_BINDING)
				.Property("AnyKey", BINDING_READONLY_PROPERTY(&EKeys::AnyKey))
				.Property("MouseX", BINDING_READONLY_PROPERTY(&EKeys::MouseX))
				.Property("MouseY", BINDING_READONLY_PROPERTY(&EKeys::MouseY))
				.Property("Mouse2D", BINDING_READONLY_PROPERTY(&EKeys::Mouse2D))
				.Property("MouseScrollUp", BINDING_READONLY_PROPERTY(&EKeys::MouseScrollUp))
				.Property("MouseScrollDown", BINDING_READONLY_PROPERTY(&EKeys::MouseScrollDown))
				.Property("MouseWheelAxis", BINDING_READONLY_PROPERTY(&EKeys::MouseWheelAxis))
				.Property("LeftMouseButton", BINDING_READONLY_PROPERTY(&EKeys::LeftMouseButton))
				.Property("RightMouseButton", BINDING_READONLY_PROPERTY(&EKeys::RightMouseButton))
				.Property("MiddleMouseButton", BINDING_READONLY_PROPERTY(&EKeys::MiddleMouseButton))
				.Property("ThumbMouseButton", BINDING_READONLY_PROPERTY(&EKeys::ThumbMouseButton))
				.Property("ThumbMouseButton2", BINDING_READONLY_PROPERTY(&EKeys::ThumbMouseButton2))
				.Property("BackSpace", BINDING_READONLY_PROPERTY(&EKeys::BackSpace))
				.Property("Tab", BINDING_READONLY_PROPERTY(&EKeys::Tab))
				.Property("Enter", BINDING_READONLY_PROPERTY(&EKeys::Enter))
				.Property("Pause", BINDING_READONLY_PROPERTY(&EKeys::Pause))
				.Property("CapsLock", BINDING_READONLY_PROPERTY(&EKeys::CapsLock))
				.Property("Escape", BINDING_READONLY_PROPERTY(&EKeys::Escape))
				.Property("SpaceBar", BINDING_READONLY_PROPERTY(&EKeys::SpaceBar))
				.Property("PageUp", BINDING_READONLY_PROPERTY(&EKeys::PageUp))
				.Property("PageDown", BINDING_READONLY_PROPERTY(&EKeys::PageDown))
				.Property("End", BINDING_READONLY_PROPERTY(&EKeys::End))
				.Property("Home", BINDING_READONLY_PROPERTY(&EKeys::Home))
				.Property("Left", BINDING_READONLY_PROPERTY(&EKeys::Left))
				.Property("Up", BINDING_READONLY_PROPERTY(&EKeys::Up))
				.Property("Right", BINDING_READONLY_PROPERTY(&EKeys::Right))
				.Property("Down", BINDING_READONLY_PROPERTY(&EKeys::Down))
				.Property("Insert", BINDING_READONLY_PROPERTY(&EKeys::Insert))
				.Property("Delete", BINDING_READONLY_PROPERTY(&EKeys::Delete))
				.Property("Zero", BINDING_READONLY_PROPERTY(&EKeys::Zero))
				.Property("One", BINDING_READONLY_PROPERTY(&EKeys::One))
				.Property("Two", BINDING_READONLY_PROPERTY(&EKeys::Two))
				.Property("Three", BINDING_READONLY_PROPERTY(&EKeys::Three))
				.Property("Four", BINDING_READONLY_PROPERTY(&EKeys::Four))
				.Property("Five", BINDING_READONLY_PROPERTY(&EKeys::Five))
				.Property("Six", BINDING_READONLY_PROPERTY(&EKeys::Six))
				.Property("Seven", BINDING_READONLY_PROPERTY(&EKeys::Seven))
				.Property("Eight", BINDING_READONLY_PROPERTY(&EKeys::Eight))
				.Property("Nine", BINDING_READONLY_PROPERTY(&EKeys::Nine))
				.Property("A", BINDING_READONLY_PROPERTY(&EKeys::A))
				.Property("B", BINDING_READONLY_PROPERTY(&EKeys::B))
				.Property("C", BINDING_READONLY_PROPERTY(&EKeys::C))
				.Property("D", BINDING_READONLY_PROPERTY(&EKeys::D))
				.Property("E", BINDING_READONLY_PROPERTY(&EKeys::E))
				.Property("F", BINDING_READONLY_PROPERTY(&EKeys::F))
				.Property("G", BINDING_READONLY_PROPERTY(&EKeys::G))
				.Property("H", BINDING_READONLY_PROPERTY(&EKeys::H))
				.Property("I", BINDING_READONLY_PROPERTY(&EKeys::I))
				.Property("J", BINDING_READONLY_PROPERTY(&EKeys::J))
				.Property("K", BINDING_READONLY_PROPERTY(&EKeys::K))
				.Property("L", BINDING_READONLY_PROPERTY(&EKeys::L))
				.Property("M", BINDING_READONLY_PROPERTY(&EKeys::M))
				.Property("N", BINDING_READONLY_PROPERTY(&EKeys::N))
				.Property("O", BINDING_READONLY_PROPERTY(&EKeys::O))
				.Property("P", BINDING_READONLY_PROPERTY(&EKeys::P))
				.Property("Q", BINDING_READONLY_PROPERTY(&EKeys::Q))
				.Property("R", BINDING_READONLY_PROPERTY(&EKeys::R))
				.Property("S", BINDING_READONLY_PROPERTY(&EKeys::S))
				.Property("T", BINDING_READONLY_PROPERTY(&EKeys::T))
				.Property("U", BINDING_READONLY_PROPERTY(&EKeys::U))
				.Property("V", BINDING_READONLY_PROPERTY(&EKeys::V))
				.Property("W", BINDING_READONLY_PROPERTY(&EKeys::W))
				.Property("X", BINDING_READONLY_PROPERTY(&EKeys::X))
				.Property("Y", BINDING_READONLY_PROPERTY(&EKeys::Y))
				.Property("Z", BINDING_READONLY_PROPERTY(&EKeys::Z))
				.Property("NumPadZero", BINDING_READONLY_PROPERTY(&EKeys::NumPadZero))
				.Property("NumPadOne", BINDING_READONLY_PROPERTY(&EKeys::NumPadOne))
				.Property("NumPadTwo", BINDING_READONLY_PROPERTY(&EKeys::NumPadTwo))
				.Property("NumPadThree", BINDING_READONLY_PROPERTY(&EKeys::NumPadThree))
				.Property("NumPadFour", BINDING_READONLY_PROPERTY(&EKeys::NumPadFour))
				.Property("NumPadFive", BINDING_READONLY_PROPERTY(&EKeys::NumPadFive))
				.Property("NumPadSix", BINDING_READONLY_PROPERTY(&EKeys::NumPadSix))
				.Property("NumPadSeven", BINDING_READONLY_PROPERTY(&EKeys::NumPadSeven))
				.Property("NumPadEight", BINDING_READONLY_PROPERTY(&EKeys::NumPadEight))
				.Property("NumPadNine", BINDING_READONLY_PROPERTY(&EKeys::NumPadNine))
				.Property("Multiply", BINDING_READONLY_PROPERTY(&EKeys::Multiply))
				.Property("Add", BINDING_READONLY_PROPERTY(&EKeys::Add))
				.Property("Subtract", BINDING_READONLY_PROPERTY(&EKeys::Subtract))
				.Property("Decimal", BINDING_READONLY_PROPERTY(&EKeys::Decimal))
				.Property("Divide", BINDING_READONLY_PROPERTY(&EKeys::Divide))
				.Property("F1", BINDING_READONLY_PROPERTY(&EKeys::F1))
				.Property("F2", BINDING_READONLY_PROPERTY(&EKeys::F2))
				.Property("F3", BINDING_READONLY_PROPERTY(&EKeys::F3))
				.Property("F4", BINDING_READONLY_PROPERTY(&EKeys::F4))
				.Property("F5", BINDING_READONLY_PROPERTY(&EKeys::F5))
				.Property("F6", BINDING_READONLY_PROPERTY(&EKeys::F6))
				.Property("F7", BINDING_READONLY_PROPERTY(&EKeys::F7))
				.Property("F8", BINDING_READONLY_PROPERTY(&EKeys::F8))
				.Property("F9", BINDING_READONLY_PROPERTY(&EKeys::F9))
				.Property("F10", BINDING_READONLY_PROPERTY(&EKeys::F10))
				.Property("F11", BINDING_READONLY_PROPERTY(&EKeys::F11))
				.Property("F12", BINDING_READONLY_PROPERTY(&EKeys::F12))
				.Property("NumLock", BINDING_READONLY_PROPERTY(&EKeys::NumLock))
				.Property("ScrollLock", BINDING_READONLY_PROPERTY(&EKeys::ScrollLock))
				.Property("LeftShift", BINDING_READONLY_PROPERTY(&EKeys::LeftShift))
				.Property("RightShift", BINDING_READONLY_PROPERTY(&EKeys::RightShift))
				.Property("LeftControl", BINDING_READONLY_PROPERTY(&EKeys::LeftControl))
				.Property("RightControl", BINDING_READONLY_PROPERTY(&EKeys::RightControl))
				.Property("LeftAlt", BINDING_READONLY_PROPERTY(&EKeys::LeftAlt))
				.Property("RightAlt", BINDING_READONLY_PROPERTY(&EKeys::RightAlt))
				.Property("LeftCommand", BINDING_READONLY_PROPERTY(&EKeys::LeftCommand))
				.Property("RightCommand", BINDING_READONLY_PROPERTY(&EKeys::RightCommand))
				.Property("Semicolon", BINDING_READONLY_PROPERTY(&EKeys::Semicolon))
				.Property("Equals", BINDING_READONLY_PROPERTY(&EKeys::Equals, EPropertyInteract::New))
				.Property("Comma", BINDING_READONLY_PROPERTY(&EKeys::Comma))
				.Property("Underscore", BINDING_READONLY_PROPERTY(&EKeys::Underscore))
				.Property("Hyphen", BINDING_READONLY_PROPERTY(&EKeys::Hyphen))
				.Property("Period", BINDING_READONLY_PROPERTY(&EKeys::Period))
				.Property("Slash", BINDING_READONLY_PROPERTY(&EKeys::Slash))
				.Property("Tilde", BINDING_READONLY_PROPERTY(&EKeys::Tilde))
				.Property("LeftBracket", BINDING_READONLY_PROPERTY(&EKeys::LeftBracket))
				.Property("LeftParantheses", BINDING_READONLY_PROPERTY(&EKeys::LeftParantheses))
				.Property("Backslash", BINDING_READONLY_PROPERTY(&EKeys::Backslash))
				.Property("RightBracket", BINDING_READONLY_PROPERTY(&EKeys::RightBracket))
				.Property("RightParantheses", BINDING_READONLY_PROPERTY(&EKeys::RightParantheses))
				.Property("Apostrophe", BINDING_READONLY_PROPERTY(&EKeys::Apostrophe))
				.Property("Quote", BINDING_READONLY_PROPERTY(&EKeys::Quote))
				.Property("Asterix", BINDING_READONLY_PROPERTY(&EKeys::Asterix))
				.Property("Ampersand", BINDING_READONLY_PROPERTY(&EKeys::Ampersand))
				.Property("Caret", BINDING_READONLY_PROPERTY(&EKeys::Caret))
				.Property("Dollar", BINDING_READONLY_PROPERTY(&EKeys::Dollar))
				.Property("Exclamation", BINDING_READONLY_PROPERTY(&EKeys::Exclamation))
				.Property("Colon", BINDING_READONLY_PROPERTY(&EKeys::Colon))
				.Property("A_AccentGrave", BINDING_READONLY_PROPERTY(&EKeys::A_AccentGrave))
				.Property("E_AccentGrave", BINDING_READONLY_PROPERTY(&EKeys::E_AccentGrave))
				.Property("E_AccentAigu", BINDING_READONLY_PROPERTY(&EKeys::E_AccentAigu))
				.Property("C_Cedille", BINDING_READONLY_PROPERTY(&EKeys::C_Cedille))
				.Property("Section", BINDING_READONLY_PROPERTY(&EKeys::Section))
				.Property("Platform_Delete", BINDING_READONLY_PROPERTY(&EKeys::Platform_Delete))
				.Property("Gamepad_Left2D", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_Left2D))
				.Property("Gamepad_LeftX", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_LeftX))
				.Property("Gamepad_LeftY", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_LeftY))
				.Property("Gamepad_Right2D", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_Right2D))
				.Property("Gamepad_RightX", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_RightX))
				.Property("Gamepad_RightY", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_RightY))
				.Property("Gamepad_LeftTriggerAxis", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_LeftTriggerAxis))
				.Property("Gamepad_RightTriggerAxis", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_RightTriggerAxis))
				.Property("Gamepad_LeftThumbstick", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_LeftThumbstick))
				.Property("Gamepad_RightThumbstick", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_RightThumbstick))
				.Property("Gamepad_Special_Left", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_Special_Left))
				.Property("Gamepad_Special_Left_X", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_Special_Left_X))
				.Property("Gamepad_Special_Left_Y", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_Special_Left_Y))
#if UE_E_KEYS_GAMEPAD_SPECIAL_LEFT_TOUCHED
				.Property("Gamepad_Special_Left_Touched",
				          BINDING_READONLY_PROPERTY(&EKeys::Gamepad_Special_Left_Touched))
#endif
				.Property("Gamepad_Special_Right", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_Special_Right))
				.Property("Gamepad_FaceButton_Bottom", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_FaceButton_Bottom))
				.Property("Gamepad_FaceButton_Right", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_FaceButton_Right))
				.Property("Gamepad_FaceButton_Left", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_FaceButton_Left))
				.Property("Gamepad_FaceButton_Top", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_FaceButton_Top))
				.Property("Gamepad_LeftShoulder", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_LeftShoulder))
				.Property("Gamepad_RightShoulder", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_RightShoulder))
				.Property("Gamepad_LeftTrigger", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_LeftTrigger))
				.Property("Gamepad_RightTrigger", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_RightTrigger))
				.Property("Gamepad_DPad_Up", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_DPad_Up))
				.Property("Gamepad_DPad_Down", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_DPad_Down))
				.Property("Gamepad_DPad_Right", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_DPad_Right))
				.Property("Gamepad_DPad_Left", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_DPad_Left))
				.Property("Gamepad_LeftStick_Up", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_LeftStick_Up))
				.Property("Gamepad_LeftStick_Down", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_LeftStick_Down))
				.Property("Gamepad_LeftStick_Right", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_LeftStick_Right))
				.Property("Gamepad_LeftStick_Left", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_LeftStick_Left))
				.Property("Gamepad_RightStick_Up", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_RightStick_Up))
				.Property("Gamepad_RightStick_Down", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_RightStick_Down))
				.Property("Gamepad_RightStick_Right", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_RightStick_Right))
				.Property("Gamepad_RightStick_Left", BINDING_READONLY_PROPERTY(&EKeys::Gamepad_RightStick_Left))
				.Property("Tilt", BINDING_READONLY_PROPERTY(&EKeys::Tilt))
				.Property("RotationRate", BINDING_READONLY_PROPERTY(&EKeys::RotationRate))
				.Property("Gravity", BINDING_READONLY_PROPERTY(&EKeys::Gravity))
				.Property("Acceleration", BINDING_READONLY_PROPERTY(&EKeys::Acceleration))
				.Property("Gesture_Pinch", BINDING_READONLY_PROPERTY(&EKeys::Gesture_Pinch))
				.Property("Gesture_Flick", BINDING_READONLY_PROPERTY(&EKeys::Gesture_Flick))
				.Property("Gesture_Rotate", BINDING_READONLY_PROPERTY(&EKeys::Gesture_Rotate))
				.Property("Steam_Touch_0", BINDING_READONLY_PROPERTY(&EKeys::Steam_Touch_0))
				.Property("Steam_Touch_1", BINDING_READONLY_PROPERTY(&EKeys::Steam_Touch_1))
				.Property("Steam_Touch_2", BINDING_READONLY_PROPERTY(&EKeys::Steam_Touch_2))
				.Property("Steam_Touch_3", BINDING_READONLY_PROPERTY(&EKeys::Steam_Touch_3))
				.Property("Steam_Back_Left", BINDING_READONLY_PROPERTY(&EKeys::Steam_Back_Left))
				.Property("Steam_Back_Right", BINDING_READONLY_PROPERTY(&EKeys::Steam_Back_Right))
				.Property("Global_Menu", BINDING_READONLY_PROPERTY(&EKeys::Global_Menu))
				.Property("Global_View", BINDING_READONLY_PROPERTY(&EKeys::Global_View))
				.Property("Global_Pause", BINDING_READONLY_PROPERTY(&EKeys::Global_Pause))
				.Property("Global_Play", BINDING_READONLY_PROPERTY(&EKeys::Global_Play))
				.Property("Android_Back", BINDING_READONLY_PROPERTY(&EKeys::Android_Back))
				.Property("Android_Volume_Up", BINDING_READONLY_PROPERTY(&EKeys::Android_Volume_Up))
				.Property("Android_Volume_Down", BINDING_READONLY_PROPERTY(&EKeys::Android_Volume_Down))
				.Property("Android_Menu", BINDING_READONLY_PROPERTY(&EKeys::Android_Menu))
#if UE_E_KEYS_VIVE_LEFT_SYSTEM_CLICK
				.Property("Vive_Left_System_Click", BINDING_READONLY_PROPERTY(&EKeys::Vive_Left_System_Click))
#endif
				.Property("Vive_Left_Grip_Click", BINDING_READONLY_PROPERTY(&EKeys::Vive_Left_Grip_Click))
				.Property("Vive_Left_Menu_Click", BINDING_READONLY_PROPERTY(&EKeys::Vive_Left_Menu_Click))
				.Property("Vive_Left_Trigger_Click", BINDING_READONLY_PROPERTY(&EKeys::Vive_Left_Trigger_Click))
				.Property("Vive_Left_Trigger_Axis", BINDING_READONLY_PROPERTY(&EKeys::Vive_Left_Trigger_Axis))
				.Property("Vive_Left_Trackpad_X", BINDING_READONLY_PROPERTY(&EKeys::Vive_Left_Trackpad_X))
				.Property("Vive_Left_Trackpad_Y", BINDING_READONLY_PROPERTY(&EKeys::Vive_Left_Trackpad_Y))
				.Property("Vive_Left_Trackpad_Click", BINDING_READONLY_PROPERTY(&EKeys::Vive_Left_Trackpad_Click))
				.Property("Vive_Left_Trackpad_Touch", BINDING_READONLY_PROPERTY(&EKeys::Vive_Left_Trackpad_Touch))
				.Property("Vive_Left_Trackpad_Up", BINDING_READONLY_PROPERTY(&EKeys::Vive_Left_Trackpad_Up))
				.Property("Vive_Left_Trackpad_Down", BINDING_READONLY_PROPERTY(&EKeys::Vive_Left_Trackpad_Down))
				.Property("Vive_Left_Trackpad_Left", BINDING_READONLY_PROPERTY(&EKeys::Vive_Left_Trackpad_Left))
				.Property("Vive_Left_Trackpad_Right", BINDING_READONLY_PROPERTY(&EKeys::Vive_Left_Trackpad_Right))
#if UE_E_KEYS_VIVE_RIGHT_SYSTEM_CLICK
				.Property("Vive_Right_System_Click", BINDING_READONLY_PROPERTY(&EKeys::Vive_Right_System_Click))
#endif
				.Property("Vive_Right_Grip_Click", BINDING_READONLY_PROPERTY(&EKeys::Vive_Right_Grip_Click))
				.Property("Vive_Right_Menu_Click", BINDING_READONLY_PROPERTY(&EKeys::Vive_Right_Menu_Click))
				.Property("Vive_Right_Trigger_Click", BINDING_READONLY_PROPERTY(&EKeys::Vive_Right_Trigger_Click))
				.Property("Vive_Right_Trigger_Axis", BINDING_READONLY_PROPERTY(&EKeys::Vive_Right_Trigger_Axis))
				.Property("Vive_Right_Trackpad_X", BINDING_READONLY_PROPERTY(&EKeys::Vive_Right_Trackpad_X))
				.Property("Vive_Right_Trackpad_Y", BINDING_READONLY_PROPERTY(&EKeys::Vive_Right_Trackpad_Y))
				.Property("Vive_Right_Trackpad_Click", BINDING_READONLY_PROPERTY(&EKeys::Vive_Right_Trackpad_Click))
				.Property("Vive_Right_Trackpad_Touch", BINDING_READONLY_PROPERTY(&EKeys::Vive_Right_Trackpad_Touch))
				.Property("Vive_Right_Trackpad_Up", BINDING_READONLY_PROPERTY(&EKeys::Vive_Right_Trackpad_Up))
				.Property("Vive_Right_Trackpad_Down", BINDING_READONLY_PROPERTY(&EKeys::Vive_Right_Trackpad_Down))
				.Property("Vive_Right_Trackpad_Left", BINDING_READONLY_PROPERTY(&EKeys::Vive_Right_Trackpad_Left))
				.Property("Vive_Right_Trackpad_Right", BINDING_READONLY_PROPERTY(&EKeys::Vive_Right_Trackpad_Right))
				.Property("MixedReality_Left_Menu_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Menu_Click))
				.Property("MixedReality_Left_Grip_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Grip_Click))
				.Property("MixedReality_Left_Trigger_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Trigger_Click))
				.Property("MixedReality_Left_Trigger_Axis",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Trigger_Axis))
				.Property("MixedReality_Left_Thumbstick_X",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Thumbstick_X))
				.Property("MixedReality_Left_Thumbstick_Y",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Thumbstick_Y))
				.Property("MixedReality_Left_Thumbstick_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Thumbstick_Click))
				.Property("MixedReality_Left_Thumbstick_Up",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Thumbstick_Up))
				.Property("MixedReality_Left_Thumbstick_Down",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Thumbstick_Down))
				.Property("MixedReality_Left_Thumbstick_Left",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Thumbstick_Left))
				.Property("MixedReality_Left_Thumbstick_Right",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Thumbstick_Right))
				.Property("MixedReality_Left_Trackpad_X",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Trackpad_X))
				.Property("MixedReality_Left_Trackpad_Y",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Trackpad_Y))
				.Property("MixedReality_Left_Trackpad_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Trackpad_Click))
				.Property("MixedReality_Left_Trackpad_Touch",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Trackpad_Touch))
				.Property("MixedReality_Left_Trackpad_Up",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Trackpad_Up))
				.Property("MixedReality_Left_Trackpad_Down",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Trackpad_Down))
				.Property("MixedReality_Left_Trackpad_Left",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Trackpad_Left))
				.Property("MixedReality_Left_Trackpad_Right",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Left_Trackpad_Right))
				.Property("MixedReality_Right_Menu_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Menu_Click))
				.Property("MixedReality_Right_Grip_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Grip_Click))
				.Property("MixedReality_Right_Trigger_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Trigger_Click))
				.Property("MixedReality_Right_Trigger_Axis",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Trigger_Axis))
				.Property("MixedReality_Right_Thumbstick_X",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Thumbstick_X))
				.Property("MixedReality_Right_Thumbstick_Y",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Thumbstick_Y))
				.Property("MixedReality_Right_Thumbstick_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Thumbstick_Click))
				.Property("MixedReality_Right_Thumbstick_Up",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Thumbstick_Up))
				.Property("MixedReality_Right_Thumbstick_Down",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Thumbstick_Down))
				.Property("MixedReality_Right_Thumbstick_Left",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Thumbstick_Left))
				.Property("MixedReality_Right_Thumbstick_Right",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Thumbstick_Right))
				.Property("MixedReality_Right_Trackpad_X",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Trackpad_X))
				.Property("MixedReality_Right_Trackpad_Y",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Trackpad_Y))
				.Property("MixedReality_Right_Trackpad_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Trackpad_Click))
				.Property("MixedReality_Right_Trackpad_Touch",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Trackpad_Touch))
				.Property("MixedReality_Right_Trackpad_Up",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Trackpad_Up))
				.Property("MixedReality_Right_Trackpad_Down",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Trackpad_Down))
				.Property("MixedReality_Right_Trackpad_Left",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Trackpad_Left))
				.Property("MixedReality_Right_Trackpad_Right",
				          BINDING_READONLY_PROPERTY(&EKeys::MixedReality_Right_Trackpad_Right))
				.Property("OculusTouch_Left_X_Click", BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_X_Click))
				.Property("OculusTouch_Left_Y_Click", BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_Y_Click))
				.Property("OculusTouch_Left_X_Touch", BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_X_Touch))
				.Property("OculusTouch_Left_Y_Touch", BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_Y_Touch))
				.Property("OculusTouch_Left_Menu_Click", BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_Menu_Click))
				.Property("OculusTouch_Left_Grip_Click", BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_Grip_Click))
				.Property("OculusTouch_Left_Grip_Axis", BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_Grip_Axis))
				.Property("OculusTouch_Left_Trigger_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_Trigger_Click))
				.Property("OculusTouch_Left_Trigger_Axis",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_Trigger_Axis))
				.Property("OculusTouch_Left_Trigger_Touch",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_Trigger_Touch))
				.Property("OculusTouch_Left_Thumbstick_X",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_Thumbstick_X))
				.Property("OculusTouch_Left_Thumbstick_Y",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_Thumbstick_Y))
				.Property("OculusTouch_Left_Thumbstick_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_Thumbstick_Click))
				.Property("OculusTouch_Left_Thumbstick_Touch",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_Thumbstick_Touch))
				.Property("OculusTouch_Left_Thumbstick_Up",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_Thumbstick_Up))
				.Property("OculusTouch_Left_Thumbstick_Down",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_Thumbstick_Down))
				.Property("OculusTouch_Left_Thumbstick_Left",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_Thumbstick_Left))
				.Property("OculusTouch_Left_Thumbstick_Right",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Left_Thumbstick_Right))
				.Property("OculusTouch_Right_A_Click", BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_A_Click))
				.Property("OculusTouch_Right_B_Click", BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_B_Click))
				.Property("OculusTouch_Right_A_Touch", BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_A_Touch))
				.Property("OculusTouch_Right_B_Touch", BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_B_Touch))
#if UE_E_KEYS_OCULUS_TOUCH_RIGHT_SYSTEM_CLICK
				.Property("OculusTouch_Right_System_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_System_Click))
#endif
				.Property("OculusTouch_Right_Grip_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_Grip_Click))
				.Property("OculusTouch_Right_Grip_Axis", BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_Grip_Axis))
				.Property("OculusTouch_Right_Trigger_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_Trigger_Click))
				.Property("OculusTouch_Right_Trigger_Axis",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_Trigger_Axis))
				.Property("OculusTouch_Right_Trigger_Touch",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_Trigger_Touch))
				.Property("OculusTouch_Right_Thumbstick_X",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_Thumbstick_X))
				.Property("OculusTouch_Right_Thumbstick_Y",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_Thumbstick_Y))
				.Property("OculusTouch_Right_Thumbstick_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_Thumbstick_Click))
				.Property("OculusTouch_Right_Thumbstick_Touch",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_Thumbstick_Touch))
				.Property("OculusTouch_Right_Thumbstick_Up",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_Thumbstick_Up))
				.Property("OculusTouch_Right_Thumbstick_Down",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_Thumbstick_Down))
				.Property("OculusTouch_Right_Thumbstick_Left",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_Thumbstick_Left))
				.Property("OculusTouch_Right_Thumbstick_Right",
				          BINDING_READONLY_PROPERTY(&EKeys::OculusTouch_Right_Thumbstick_Right))
				.Property("ValveIndex_Left_A_Click", BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_A_Click))
				.Property("ValveIndex_Left_B_Click", BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_B_Click))
				.Property("ValveIndex_Left_A_Touch", BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_A_Touch))
				.Property("ValveIndex_Left_B_Touch", BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_B_Touch))
#if UE_E_KEYS_VALVE_INDEX_LEFT_SYSTEM_CLICK
				.Property("ValveIndex_Left_System_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_System_Click))
#endif
#if UE_E_KEYS_VALVE_INDEX_LEFT_SYSTEM_TOUCH
				.Property("ValveIndex_Left_System_Touch",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_System_Touch))
#endif
				.Property("ValveIndex_Left_Grip_Axis", BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Grip_Axis))
				.Property("ValveIndex_Left_Grip_Force", BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Grip_Force))
				.Property("ValveIndex_Left_Trigger_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Trigger_Click))
				.Property("ValveIndex_Left_Trigger_Axis",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Trigger_Axis))
				.Property("ValveIndex_Left_Trigger_Touch",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Trigger_Touch))
				.Property("ValveIndex_Left_Thumbstick_X",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Thumbstick_X))
				.Property("ValveIndex_Left_Thumbstick_Y",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Thumbstick_Y))
				.Property("ValveIndex_Left_Thumbstick_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Thumbstick_Click))
				.Property("ValveIndex_Left_Thumbstick_Touch",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Thumbstick_Touch))
				.Property("ValveIndex_Left_Thumbstick_Up",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Thumbstick_Up))
				.Property("ValveIndex_Left_Thumbstick_Down",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Thumbstick_Down))
				.Property("ValveIndex_Left_Thumbstick_Left",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Thumbstick_Left))
				.Property("ValveIndex_Left_Thumbstick_Right",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Thumbstick_Right))
				.Property("ValveIndex_Left_Trackpad_X", BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Trackpad_X))
				.Property("ValveIndex_Left_Trackpad_Y", BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Trackpad_Y))
				.Property("ValveIndex_Left_Trackpad_Force",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Trackpad_Force))
				.Property("ValveIndex_Left_Trackpad_Touch",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Trackpad_Touch))
				.Property("ValveIndex_Left_Trackpad_Up", BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Trackpad_Up))
				.Property("ValveIndex_Left_Trackpad_Down",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Trackpad_Down))
				.Property("ValveIndex_Left_Trackpad_Left",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Trackpad_Left))
				.Property("ValveIndex_Left_Trackpad_Right",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Left_Trackpad_Right))
				.Property("ValveIndex_Right_A_Click", BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_A_Click))
				.Property("ValveIndex_Right_B_Click", BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_B_Click))
				.Property("ValveIndex_Right_A_Touch", BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_A_Touch))
				.Property("ValveIndex_Right_B_Touch", BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_B_Touch))
#if UE_E_KEYS_VALVE_INDEX_RIGHT_SYSTEM_CLICK
				.Property("ValveIndex_Right_System_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_System_Click))
#endif
#if UE_E_KEYS_VALVE_INDEX_RIGHT_SYSTEM_TOUCH
				.Property("ValveIndex_Right_System_Touch",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_System_Touch))
#endif
				.Property("ValveIndex_Right_Grip_Axis", BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Grip_Axis))
				.Property("ValveIndex_Right_Grip_Force", BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Grip_Force))
				.Property("ValveIndex_Right_Trigger_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Trigger_Click))
				.Property("ValveIndex_Right_Trigger_Axis",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Trigger_Axis))
				.Property("ValveIndex_Right_Trigger_Touch",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Trigger_Touch))
				.Property("ValveIndex_Right_Thumbstick_X",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Thumbstick_X))
				.Property("ValveIndex_Right_Thumbstick_Y",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Thumbstick_Y))
				.Property("ValveIndex_Right_Thumbstick_Click",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Thumbstick_Click))
				.Property("ValveIndex_Right_Thumbstick_Touch",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Thumbstick_Touch))
				.Property("ValveIndex_Right_Thumbstick_Up",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Thumbstick_Up))
				.Property("ValveIndex_Right_Thumbstick_Down",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Thumbstick_Down))
				.Property("ValveIndex_Right_Thumbstick_Left",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Thumbstick_Left))
				.Property("ValveIndex_Right_Thumbstick_Right",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Thumbstick_Right))
				.Property("ValveIndex_Right_Trackpad_X", BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Trackpad_X))
				.Property("ValveIndex_Right_Trackpad_Y", BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Trackpad_Y))
				.Property("ValveIndex_Right_Trackpad_Force",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Trackpad_Force))
				.Property("ValveIndex_Right_Trackpad_Touch",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Trackpad_Touch))
				.Property("ValveIndex_Right_Trackpad_Up",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Trackpad_Up))
				.Property("ValveIndex_Right_Trackpad_Down",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Trackpad_Down))
				.Property("ValveIndex_Right_Trackpad_Left",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Trackpad_Left))
				.Property("ValveIndex_Right_Trackpad_Right",
				          BINDING_READONLY_PROPERTY(&EKeys::ValveIndex_Right_Trackpad_Right))
#if UE_E_KEYS_VIRTUAL_ACCEPT
				.Property("Virtual_Accept", BINDING_READONLY_PROPERTY(&EKeys::Virtual_Accept))
#endif
#if UE_E_KEYS_VIRTUAL_BACK
				.Property("Virtual_Back", BINDING_READONLY_PROPERTY(&EKeys::Virtual_Back))
#endif
				.Property("Invalid", BINDING_READONLY_PROPERTY(&EKeys::Invalid));
		}
	};

	[[maybe_unused]] FRegisterKeys RegisterKeys;
}
