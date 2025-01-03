// -*- C++ -*- generated by wxGlade 0.6.3 on Thu Mar 12 19:52:16 2009
/*
  Copyright 2009 Ronald S. Burkey <info@sandroid.org>
  
  This file is part of yaAGC.

  yaAGC is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  yaAGC is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with yaAGC; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
  
  Filename:	yaDEDA2.h
  Contact:	Ron Burkey <info@sandroid.org>
  Reference:	http://www.ibiblio.org/apollo/index.html
  Mods:		2009-03-12 RSB	Began.
  
  The yaDEDA2 program is intended to be a completely identical drop-in
  replacement for the yaDEDA program as it exists at 2009-03-12.  
  yaDEDA works well, but it suffers from the basic problem that GTK+
  support for Mac OS X (and even to some extent for Win32) is not 
  where I want it to be.  Furthermore, newer GUI programs for yaAGC
  are based on wxWidgets, where I have been having better luck with 
  Win32/Mac support.  So in other words, yaDEDA2 is a wxWidgets port
  of the GTK+ based yaDEDA program.
*/

#include <wx/wx.h>
#include <wx/image.h>
// begin wxGlade: ::dependencies
// end wxGlade


#ifndef YADEDA2_H
#define YADEDA2_H

#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#include <sys/time.h>
struct tms {
  clock_t tms_utime;  /* user time */
  clock_t tms_stime;  /* system time */
  clock_t tms_cutime; /* user time of children */
  clock_t tms_cstime; /* system time of children */
};
#define _SC_CLK_TCK (1000)
#define sysconf(x) (x)
#else
#include <time.h>
#include <sys/times.h>
#endif
#define WHEN_IN_EXPIRED (sysconf(_SC_CLK_TCK) / 1)	// Length of timeout for incoming data.
#define WHEN_OUT_EXPIRED (sysconf(_SC_CLK_TCK) / 1)	// Length of timeout for outgoing data.

// Unique numerical IDs for widgets with event-handlers.
enum {
  ID_0, ID_1, ID_2, ID_3, ID_4, ID_5, ID_6, ID_7, ID_8, ID_9,
  ID_PLUS, ID_MINUS, ID_HOLD, ID_CLR, ID_READOUT, ID_ENTR
};


// begin wxGlade: ::extracode
// end wxGlade


class TimerClass: public wxTimer {
public:
    int IoErrorCount;

private:
    virtual void Notify();
    void ActOnIncomingIO (unsigned char *Packet);
};


class MainFrame: public wxFrame {
public:
    // begin wxGlade: MainFrame::ids
    // end wxGlade

    MainFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);
    TimerClass *Timer;
    void ImageSet (wxStaticBitmap *StaticBitmap, wxString &Filename);
    void ImageSet (wxStaticBitmap *StaticBigmap, char *Filename);
    void ImageSet (wxStaticBitmap *StaticBigmap, const char *Filename);
    void ImageSet (wxBitmapButton *BitmapButton, wxString &Filename);
    void ImageSet (wxBitmapButton *BitmapButton, char *Filename);
    void ImageSet (wxBitmapButton *BitmapButton, const char *Filename);
    wxTimer *PulseTimer;
    bool HalfSize;
    void HalveTheWindow (void);
    void ActOnIncomingIO (unsigned char *Packet);

private:
    // begin wxGlade: MainFrame::methods
    void set_properties();
    void do_layout();
    // end wxGlade

    void OutputData (int Type, int Data);
    void ClearTheDisplay (void);
    void OperatorError (int On);
    int OprErr;
    int NumOutPacket;
    int NumInPacket; 
    int LastReadout;  
    int ShiftingOut;
    int ShiftBufferSize;
    unsigned char ShiftBuffer[9];
    unsigned char OutPacket[9];
    int ShiftBufferPtr; 
    unsigned char InPacket[9];
    void ProcessDigit (int Condition, int Num);
    void ReadyForShift (void);
    clock_t WhenInPacket;
    clock_t WhenOutPacket;

public:
    // begin wxGlade: MainFrame::attributes
    wxStaticBitmap* bitmap_10;
    wxStaticBitmap* bitmap_5;
    wxStaticBitmap* DigitTop1;
    wxStaticBitmap* DigitTop2;
    wxStaticBitmap* DigitTop3;
    wxStaticBitmap* bitmap_5_copy;
    wxStaticBitmap* bitmap_11;
    wxStaticBitmap* OprErrBarTop;
    wxStaticBitmap* OprErrBarLeft;
    wxStaticBitmap* IndicatorOprErr;
    wxStaticBitmap* OprErrBarRight;
    wxStaticBitmap* OprErrBarBottom;
    wxStaticBitmap* bitmap_13;
    wxStaticBitmap* bitmap_7;
    wxStaticBitmap* Sign;
    wxStaticBitmap* DigitBottom1;
    wxStaticBitmap* DigitBottom2;
    wxStaticBitmap* DigitBottom3;
    wxStaticBitmap* DigitBottom4;
    wxStaticBitmap* DigitBottom5;
    wxStaticBitmap* bitmap_7_copy;
    wxStaticBitmap* bitmap_14;
    wxBitmapButton* KeyPlus;
    wxBitmapButton* Key7;
    wxBitmapButton* Key8;
    wxBitmapButton* Key9;
    wxBitmapButton* KeyClr;
    wxBitmapButton* KeyMinus;
    wxBitmapButton* Key4;
    wxBitmapButton* Key5;
    wxBitmapButton* Key6;
    wxBitmapButton* KeyReadOut;
    wxBitmapButton* Key0;
    wxBitmapButton* Key1;
    wxBitmapButton* Key2;
    wxBitmapButton* Key3;
    wxBitmapButton* KeyEntr;
    wxBitmapButton* KeyHold;
    // end wxGlade

    DECLARE_EVENT_TABLE()

public:
    virtual void on_KeyPlus_pressed(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void on_Key7_pressed(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void on_Key8_pressed(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void on_Key9_pressed(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void on_KeyClr_pressed(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void on_KeyMinus_pressed(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void on_Key4_pressed(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void on_Key5_pressed(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void on_Key6_pressed(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void on_KeyReadOut_pressed(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void on_Key0_pressed(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void on_Key1_pressed(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void on_Key2_pressed(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void on_Key3_pressed(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void on_KeyEntr_pressed(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void on_KeyHold_pressed(wxCommandEvent &event); // wxGlade: <event_handler>
}; // wxGlade: end class

#endif // YADEDA2_H
