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
// Midi event handler.

#ifndef BRAIDS_MIDI_HANDLER_H_
#define BRAIDS_MIDI_HANDLER_H_

#include "stmlib/stmlib.h"

#include "stmlib/utils/ring_buffer.h"
#include "stmlib/midi/midi.h"

// #include "BRAIDS/multi.h"

namespace braids {

const size_t kSysexMaxChunkSize = 64;
const size_t kSysexRxBufferSize = kSysexMaxChunkSize * 2 + 16;

class MidiHandler {
 public:
  typedef stmlib::RingBuffer<uint8_t, 128> MidiBuffer;
  typedef stmlib::RingBuffer<uint8_t, 32> SmallMidiBuffer;
   
  MidiHandler() { }
  ~MidiHandler() { }
  
  static void Init();
  

  
  static MidiBuffer input_buffer_; 
  static SmallMidiBuffer high_priority_output_buffer_;
  static stmlib_midi::MidiStreamParser<MidiHandler> parser_;
  
  
  static uint8_t previous_packet_index_;

  static void PushByte(uint8_t byte) {
    input_buffer_.Overwrite(byte);
  }
    
  static void ProcessInput() {
    while (input_buffer_.readable()) {
      parser_.PushByte(input_buffer_.ImmediateRead());
    }
  }


  static void BozoByte(uint8_t bozo_byte) { }


  static bool CheckChannel(uint8_t channel) { return true; }

  static inline void NoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
    if (velocity != 0) {
    
//      pitch_[channel] = note << 7;
    }
   }
   

  static void RawByte(uint8_t byte) {
      if (byte != 0xfa && byte != 0xf8 && byte != 0xfc) {
//        output_buffer_.Overwrite(byte);
    }
  }  

  static void RawMidiData(
      uint8_t status,
      uint8_t* data,
      uint8_t data_size,
      uint8_t accepted_channel) {

  }

   
  DISALLOW_COPY_AND_ASSIGN(MidiHandler);
};

extern MidiHandler midi_handler;

}  // namespace braids

#endif // BRAIDS_MIDI_HANDLER_H_
