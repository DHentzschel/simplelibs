#ifndef KEY_H
#define KEY_H

enum class Key {
    /* Mouse */
    MouseLeft = 0x01,
    MouseRight = 0x02,
    MouseCancle = 0x03,
    MouseMiddle = 0x04,
    MouseX1 = 0x05,
    MouseX2 = 0x06,

    /* Reserved = 0x07 */
    Backspace = 0x08,
    Tab = 0x09,
    /* Reserved = 0x0A - 0x0B */
    Clear = 0x0C,
    Return = 0x0D,
    /* Undefined = 0x0E - 0x0F */
    Shift = 0x10,
    Control = 0x11,
    Alt = 0x12,
    Pause = 0x13,
    CapsLock = 0x14,
    ImeKana = 0x15,
    ImeHanguel = 0x15, /* here because of */
    ImeHangul = 0x15,  /* compatibility */
    /* Undefined = 0x16*/
    ImeJunja = 0x17,
    ImeFinal = 0x18,
    ImeHanja = 0x19,
    ImeKanji = 0x19, /* here because of compatibility */
    /* Undefined = 0x1A */
    Escape = 0x1B,
    ImeConvert = 0x1C,
    ImeNonConvert = 0x1D,
    ImeAccept = 0x1E,
    ImeModeChange = 0x1F,
    Space = 0x20,
    PageUp = 0x21,
    PageDown = 0x22,
    End = 0x23,
    Home = 0x24,
    ArrowLeft = 0x25,
    ArrowUp = 0x26,
    ArrowRight = 0x27,
    ArrowDown = 0x28,
    Select = 0x29,
    Print = 0x2A,
    Execute = 0x2B,
    PrintScreen = 0x2C,
    Insert = 0x2D,
    Delete = 0x2E,
    Help = 0x2F,

    /* Numbers */
    Key0 = 0x30,
    Key1 = 0x31,
    Key2 = 0x32,
    Key3 = 0x33,
    Key4 = 0x34,
    Key5 = 0x35,
    Key6 = 0x36,
    Key7 = 0x37,
    Key8 = 0x38,
    Key9 = 0x39,
    /* Undefined = 0x3A - 0x40 */
    /* Letters */
    KeyA = 0x41,
    KeyB = 0x42,
    KeyC = 0x43,
    KeyD = 0x44,
    KeyE = 0x45,
    KeyF = 0x46,
    KeyG = 0x47,
    KeyH = 0x48,
    KeyI = 0x49,
    KeyJ = 0x4A,
    KeyK = 0x4B,
    KeyL = 0x4C,
    KeyM = 0x4D,
    KeyN = 0x4E,
    KeyO = 0x4F,
    KeyP = 0x50,
    KeyQ = 0x51,
    KeyR = 0x52,
    KeyS = 0x53,
    KeyT = 0x54,
    KeyU = 0x55,
    KeyV = 0x56,
    KeyW = 0x57,
    KeyX = 0x58,
    KeyY = 0x59,
    KeyZ = 0x5A,
    WindowsLeft = 0x5B,
    WindowsRight = 0x5C,
    Apps = 0x5D,
    /* Reserved = 0x5E */
    Sleep = 0x5F,
    Numpad0 = 0x60,
    Numpad1 = 0x61,
    Numpad2 = 0x62,
    Numpad3 = 0x63,
    Numpad4 = 0x64,
    Numpad5 = 0x65,
    Numpad6 = 0x66,
    Numpad7 = 0x67,
    Numpad8 = 0x68,
    Numpad9 = 0x69,
    Multiply = 0x6A,
    Add = 0x6B,
    Separator = 0x6C,
    Subtract = 0x6D,
    Decimal = 0x6E,
    Divide = 0x6F,
    F1 = 0x70,
    F2 = 0x71,
    F3 = 0x72,
    F4 = 0x73,
    F5 = 0x74,
    F6 = 0x75,
    F7 = 0x76,
    F8 = 0x77,
    F9 = 0x78,
    F10 = 0x79,
    F11 = 0x7A,
    F12 = 0x7B,
    F13 = 0x7C,
    F14 = 0x7D,
    F15 = 0x7E,
    F16 = 0x7F,
    F17 = 0x80,
    F18 = 0x81,
    F19 = 0x82,
    F20 = 0x83,
    F21 = 0x84,
    F22 = 0x85,
    F23 = 0x86,
    F24 = 0x87,
    /* Undefined = 0x88 - 0x8F */
    NumLock = 0x90,
    Scroll = 0x91,

    /* NEC-PC definition */
    OemNecEqual = 0x92, // '=' key on numpad
    /* Fujitsu definitions */
    OemFjJihso = 0x92, // 'Dictionary' key
    OemFjMasshou = 0x93, // 'Unregister word' key
    OemFjTouroku = 0x94, // 'Register word' key
    OemFjLoya = 0x95, // 'Left OYAYUBI' key
    OemFjRoya = 0x96, // 'Right OYAYUBI' key
    /* Undefined = 0x97 - 0x9F */

    /* Control keys */
    ShiftLeft = 0xA0,
    ShiftRight = 0xA1,
    ControlLeft = 0xA2,
    ControlRight = 0xA3,
    AltLeft = 0xA4,
    AltRight = 0xA5,

    /* Browser */
    BrowserBack = 0xA6,
    BrowserForward = 0xA7,
    BrowserRefresh = 0xA8,
    BrowserStop = 0xA9,
    BrowserSearch = 0xAA,
    BrowserFavorites = 0xAB,
    BrowserHome = 0xAC,

    /* Volume */
    VolumeMute = 0xAD,
    VolumeDown = 0xAE,
    VolumeUp = 0xAF,

    /* Media */
    MediaNextTrack = 0xB0,
    MediaPreviousTrack = 0xB1,
    MediaStop = 0xB2,
    MediaPlayPause = 0xB3,
    /* Launch */
    LaunchMail = 0xB4,
    LaunchMediaSelect = 0xB5,
    LaunchApp1 = 0xB6,
    LaunchApp2 = 0xB7,
    /* Reserved = 0xB8 - 0xB9 */
    Oem1 = 0xBA, // ';:' for US
    OemPlus = 0xBB, // '+' any country
    OemComma = 0xBC, // ',' any country
    OemMinus = 0xBD, // '-' any country
    OemPeriod = 0xBE, // '.' any country
    Oem2 = 0xBF, // '/?' for US
    Oem3 = 0xC0, // '`~' for US
    /* Reserved = 0xC1 - 0xC2 */

    /* Gamepad */
    GamepadA = 0xC3,
    GamepadB = 0xC4,
    GamepadX = 0xC5,
    GamepadY = 0xC6,
    GamepadRightShoulder = 0xC7,
    GamepadLeftShoulder = 0xC8,
    GamepadLeftTrigger = 0xC9,
    GamepadRightTrigger = 0xCA,
    GamepadDPadUp = 0xCB,
    GamepadDPadDown = 0xCC,
    GamepadDPadLeft = 0xCD,
    GamepadDPadRight = 0xCE,
    GamepadMenu = 0xCF,
    GamepadView = 0xD0,
    GamepadLeftThumbstickButton = 0xD1,
    GamepadRightThumbstickButton = 0xD2,
    GamepadLeftThumbstickButtonUp = 0xD3,
    GamepadLeftThumbstickButtonDown = 0xD4,
    GamepadLeftThumbstickButtonRight = 0xD5,
    GamepadLeftThumbstickButtonLeft = 0xD6,
    GamepadRightThumbstickButtonUp = 0xD7,
    GamepadRightThumbstickButtonDown = 0xD8,
    GamepadRightThumbstickButtonRight = 0xD9,
    GamepadRightThumbstickButtonLeft = 0xDA,
    Oem4 = 0xDB, // '[{' for US
    Oem5 = 0xDC, // '\|' for US
    Oem6 = 0xDD, // ']}' for US
    Oem7 = 0xDE, // ''"' for US
    Oem8 = 0xDF,
    /* Reserved = 0xE0 */
     /*
      * Various extended or enhanced keyboards
      */
    OemAx = 0xE1, // 'AX' key on Japanese AX kbd
    Oem102 = 0xE2, // "<>" or "\|" on RT 102-key kbd.
    IcoHelp = 0xE3, // Help key on ICO
    Ico00 = 0xE4, // 00 key on ICO
    ProcessKey = 0xE5,
    IcoClear = 0xE6,
    Packet = 0xE7,
    /* Undefined = 0xE8 */

    /* Nokia/Ericsson definitions */
    OemReset = 0xE9,
    OemJump = 0xEA,
    OemPa1 = 0xEB,
    OemPa2 = 0xEC,
    OemPa3 = 0xED,
    OemWsctrl = 0xEE,
    OemCusel = 0xEF,
    OemAttn = 0xF0,
    OemFinish = 0xF1,
    OemCopy = 0xF2,
    OemAuto = 0xF3,
    OemEnlw = 0xF4,
    OemBacktab = 0xF5,

    Attn = 0xF6,
    Crsel = 0xF7,
    Exsel = 0xF8,
    Ereof = 0xF9,
    Play = 0xFA,
    Zoom = 0xFB,
    NoName = 0xFC,
    Pa1 = 0xFD,
    OemClear = 0xFE

};

#endif // KEY_H
