#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

; SpotifyController.ahk:
; AutoHotkey script to control Spotify with global keyboard shortcuts

DetectHiddenWindows, On

; Get the HWND of the Spotify main window.
getSpotifyHwnd() {
	WinGet, spotifyHwnd, ID, ahk_exe spotify.exe
	Return spotifyHwnd
}

; Send a key to Spotify.
spotifyKey(key) {

	if WinActive("ahk_exe spotify.exe")   ; If spotify is the active window send appropriate keystroke
		Send %key%
	
	spotifyHwnd := getSpotifyHwnd()
	; Chromium ignores keys when it isn't focused.
	; Focus the document window without bringing the app to the foreground.
	ControlFocus, Chrome_RenderWidgetHostHWND1, ahk_id %spotifyHwnd%
	ControlSend, , %key%, ahk_id %spotifyHwnd%
	Return
}

; Shift+alt+p: Play/Pause
+!p::
{
	spotifyKey("{Space}")
	Return
}

; Shift+alt+up_arrow: Next
+!Up::
{
	spotifyKey("^{Right}")
	Return
}

; Shift+alt+down_arrow: Previous
+!Down::
{
	spotifyKey("^{Left}")
	Return
}

; Shift+alt+right_arrow: Seek forward
+!Right::
{
	spotifyKey("+{Right}")
	Return
}

; Shift+alt+left_arrow: Seek backward
+!Left::
{
	spotifyKey("+{Left}")
	Return
}

; shift+volumeUp: Volume up
+Volume_Up::
{
	spotifyKey("^{Up}")
	Return
}

; shift+volumeDown: Volume down
+Volume_Down::
{
	spotifyKey("^{Down}")
	Return
}

; shift+alt+L: Like Current Song
+!l::
{
	spotifyKey("+!{b}")
	Return
}

; Shift+alt+o: Show Spotify
+!o::
{
	spotifyHwnd := getSpotifyHwnd()
	WinGet, style, Style, ahk_id %spotifyHwnd%
	if (style & 0x10000000) { ; WS_VISIBLE
		WinHide, ahk_id %spotifyHwnd%
	} Else {
		WinShow, ahk_id %spotifyHwnd%
		WinActivate, ahk_id %spotifyHwnd%
	}
	Return
}