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
#include "braids/midi.h"

// #include "braids/drivers/display.h"
// #include "braids/settings.h"
// #include "stmlib/ui/event_queue.h"

// #include "BRAIDS/multi.h"

namespace braids {

extern uint16_t midi_rx;
extern bool midi_trigger_detected_flag;

//  Display display1_;

const size_t kSysexMaxChunkSize = 64;
const size_t kSysexRxBufferSize = kSysexMaxChunkSize * 2 + 16;

class MidiHandler {
 public:
  typedef stmlib::RingBuffer<uint8_t, 128> MidiBuffer;
  typedef stmlib::RingBuffer<uint8_t, 32> SmallMidiBuffer;
   
  MidiHandler() { }
  ~MidiHandler() { }
  
  static void Init();
  

  

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


  static void NoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
//    if (multi.NoteOn(channel, note, velocity) && !multi.direct_thru()) {
      Send3(0x90 | channel, note, velocity);
	braids::midi_trigger_detected_flag = true;
	braids::midi_rx = note;

    }

//  static inline void NoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
//    channel = (channel - base_channel()) & 0xf;
//    if (velocity == 0) {
//      NoteOff(channel, note, 0);
//    }

   
  static inline MidiBuffer* mutable_output_buffer() { return &output_buffer_; }
  static inline SmallMidiBuffer* mutable_high_priority_output_buffer() {
    return &high_priority_output_buffer_;
  }

  static inline void Send3(uint8_t byte_1, uint8_t byte_2, uint8_t byte_3) {
    output_buffer_.Overwrite(byte_1);
    output_buffer_.Overwrite(byte_2);
    output_buffer_.Overwrite(byte_3);
//	braids::midi_trigger_detected_flag = true;
//	braids::midi_rx = note;

  }

  static inline void Send1(uint8_t byte) {
    output_buffer_.Overwrite(byte);
  }
  
//  static inline void SendBlocking(uint8_t byte) {
//    output_buffer_.Write(byte);
//  }

  static inline void SendNow(uint8_t byte) {
    high_priority_output_buffer_.Overwrite(byte);
  }
  
  static void RawByte(uint8_t byte) {
      if (byte != 0xfa && byte != 0xf8 && byte != 0xfc) {
        output_buffer_.Overwrite(byte);
    }
  }  

  static void RawMidiData(
      uint8_t status,
      uint8_t* data,
      uint8_t data_size,
      uint8_t accepted_channel) {

  }

private:
  

  static MidiBuffer input_buffer_; 
  static MidiBuffer output_buffer_; 
  static SmallMidiBuffer high_priority_output_buffer_;

  static stmlib_midi::MidiStreamParser<MidiHandler> parser_;
  
  
  static uint8_t previous_packet_index_;
  
   

   
  DISALLOW_COPY_AND_ASSIGN(MidiHandler);
};

extern MidiHandler midi_handler;

}  // namespace braids

#endif // BRAIDS_MIDI_HANDLER_H_
