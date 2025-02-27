
#pragma once

#include "AudioTools/AudioCodecs/AudioCodecsBase.h"
#include "AudioTools/CoreAudio/AudioBasic/StrView.h"
#include "AudioTools/CoreAudio/MimeDetector.h"

namespace audio_tools {

/**
 * @brief Manage multiple decoders: the actual decoder is only opened when it
 * has been selected. The relevant decoder is determined dynamically at the
 * first write from the determined mime type. You can add your own custom mime
 * type determination logic.
 * @ingroup codecs
 * @ingroup decoder
 * @author Phil Schatzmann
 * @copyright GPLv3
 */
class MultiDecoder : public AudioDecoder {
 public:
  /// Enables the automatic mime type determination
  bool begin() override {
    mime_detector.begin();
    is_first = true;
    return true;
  }

  /// closes the actual decoder
  void end() override {
    if (actual_decoder.decoder != nullptr && actual_decoder.is_open) {
      actual_decoder.decoder->end();
    }
    actual_decoder.is_open = false;
    actual_decoder.decoder = nullptr;
    actual_decoder.mime = nullptr;
    is_first = true;
  }

  /// Adds a decoder that will be selected by it's mime type
  void addDecoder(AudioDecoder& decoder, const char* mime) {
    DecoderInfo info{mime, &decoder};
    decoder.addNotifyAudioChange(*this);
    decoders.push_back(info);
  }

  virtual void setOutput(Print &out_stream) override { 
    p_print = &out_stream; 
    for (int j = 0; j < decoders.size(); j++) {
      decoders[j].decoder->setOutput(out_stream);
    }
  }
 
  /// selects the actual decoder by mime type - this is usually called
  /// automatically from the determined mime type
  bool selectDecoder(const char* mime) {
    bool result = false;
    // do nothing if no change
    if (StrView(mime).equals(actual_decoder.mime)) {
      return true;
    }
    // close actual decoder
    end();

    // find the corresponding decoder
    for (int j = 0; j < decoders.size(); j++) {
      DecoderInfo info = decoders[j];
      if (StrView(info.mime).equals(mime)) {
        LOGI("New decoder found for %s (%s)", info.mime, mime);
        actual_decoder = info;
        // define output if it has not been defined
        if (p_print!=nullptr 
        && actual_decoder.decoder->getOutput()==nullptr){
          actual_decoder.decoder->setOutput(*p_print);
        }
        actual_decoder.decoder->begin();
        result = true;
      }
    }
    return result;
  }

  size_t write(const uint8_t* data, size_t len) override {
    if (is_first) {
      // select the decoder based on the detemined mime type
      mime_detector.write((uint8_t*)data, len);
      const char* mime = mime_detector.mime();
      if (mime != nullptr) {
        if (!selectDecoder(mime)) {
          LOGE("The decoder could not be found for %s", mime);
          actual_decoder.decoder = &nop;
          actual_decoder.is_open = true;
        }
      }
      is_first = false;
    }
    // check if we have a decoder
    if (actual_decoder.decoder == nullptr) return 0;
    // decode the data
    return actual_decoder.decoder->write(data, len);
  }
  /// Define your own custom mime detector
  void setMimeDetector(const char* (*mimeDetectCallback)(uint8_t* data,
                                                         size_t len)) {
    mime_detector.setMimeDetector(mimeDetectCallback);
  }

  virtual operator bool() { 
    if (actual_decoder.decoder == &nop) return false;
    return is_first || actual_decoder.is_open; 
  };

 protected:
  struct DecoderInfo {
    const char* mime = nullptr;
    AudioDecoder* decoder = nullptr;
    bool is_open = false;
    DecoderInfo() = default;
    DecoderInfo(const char* mime, AudioDecoder* decoder){
      this->mime = mime;
      this->decoder = decoder;
    }
  } actual_decoder;
  Vector<DecoderInfo> decoders{0};
  MimeDetector mime_detector;
  CodecNOP nop;
  bool is_first = true;
};

}  // namespace audio_tools