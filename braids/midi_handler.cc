// Copyright 2013 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//
// MIDI event handler.

#include "braids/midi_handler.h"
// #include "braids/ui.h"

#include <algorithm>


namespace braids {

using namespace std;

/* static */
MidiHandler::MidiBuffer MidiHandler::input_buffer_; 


/* static */
uint8_t MidiHandler::previous_packet_index_;

/* static */
stmlib_midi::MidiStreamParser<MidiHandler> MidiHandler::parser_;

/* static */
void MidiHandler::Init() {
  input_buffer_.Init();
  previous_packet_index_ = 0;

}

/* static */
MidiHandler::MidiBuffer MidiHandler::output_buffer_;

/* static */
MidiHandler::SmallMidiBuffer MidiHandler::high_priority_output_buffer_;


/* extern */
MidiHandler midi_handler;

}  // namespace braids
