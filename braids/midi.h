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
// Decoding of MIDI messages.

#ifndef STMLIB_MIDI_H_
#define STMLIB_MIDI_H_

#include "braids/drivers/display.h"

namespace stmlib_midi {


template<typename Handler>
class MidiStreamParser {
 public:
  MidiStreamParser() {
    running_status_ = 0;
    data_size_ = 0;
    expected_data_size_ = 0;
  }
  void PushByte(uint8_t byte) {
//    ui.StepMarquee();
    // Active sensing messages are filtered at the source, the hard way...
    if (byte == 0xfe) {
      return;
    }
    Handler::RawByte(byte);
    // Realtime messages are immediately passed-through, and do not modify the
    // state of the parser.
    if (byte >= 0xf8) {
      MessageReceived(byte);
    } else {
      if (byte >= 0x80) {
        uint8_t hi = byte & 0xf0;
        uint8_t lo = byte & 0x0f;
        data_size_ = 0;
        expected_data_size_ = 1;
        switch (hi) {
          case 0x80:
          case 0x90:
          case 0xa0:
          case 0xb0:
            expected_data_size_ = 2;
            break;
          case 0xc0:
          case 0xd0:
            break;  // default data size of 1.
          case 0xe0:
            expected_data_size_ = 2;
            break;
          case 0xf0:
            if (lo > 0 && lo < 3) {
              expected_data_size_ = 2;
            } else if (lo >= 4) {
              expected_data_size_ = 0;
            }
            break;
        }
}
      if (data_size_ >= expected_data_size_) {
        MessageReceived(running_status_);
        data_size_ = 0;
        if (running_status_ > 0xf0) {
          expected_data_size_ = 0;
          running_status_ = 0;
        }
      }
    }
  }

 private:
  void MessageReceived(uint8_t status) {
    if (!status) {
          Handler::NoteOn(1, 1, 1);

      Handler::BozoByte(data_[0]);
    }

    uint8_t hi = status & 0xf0;
    uint8_t lo = status & 0x0f;

    // If this is a channel-specific message, check first that the receiver is
    // tuned to this channel.
    if (hi != 0xf0) {
      Handler::RawMidiData(status, data_, data_size_, 0);
      return;
    }
    if (status != 0xf0 && status != 0xf7) {
      Handler::RawMidiData(status, data_, data_size_, 1);
    }
    switch (hi) {

      case 0x90:
        if (data_[1]) {
          Handler::NoteOn(lo, data_[0], data_[1]);
        } else {
        }
        break;


      case 0xb0:
        switch (data_[0]) {
          default:
//            Handler::ControlChange(lo, data_[0], data_[1]);
            break;
        }
        break;

      case 0xc0:
//        Handler::ProgramChange(lo, data_[0]);
        break;


      case 0xe0:
//        Handler::PitchBend(lo, (static_cast<uint16_t>(data_[1]) << 7) + data_[0]);
        break;

    }
  }
 
  uint8_t running_status_;
  uint8_t data_[3];
  uint8_t data_size_;  // Number of non-status byte received.
  uint8_t expected_data_size_;  // Expected number of non-status bytes.

  DISALLOW_COPY_AND_ASSIGN(MidiStreamParser);
};




}  // namespace stmlib_midi

#endif // STMLIB_MIDI_H_
