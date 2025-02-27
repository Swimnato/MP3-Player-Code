#include "AudioTools.h"
#include "AudioTools/AudioLibs/AudioRealFFT.h" // using RealFFT
#include "AudioTools/AudioLibs/MiniAudioStream.h"

AudioInfo info(44100, 2, 16);
AudioRealFFT afft; // or AudioKissFFT
Hann hann;
BufferedWindow buffered(&hann);
SineWaveGenerator<int16_t> sineWave(32000);
GeneratedSoundStream<int16_t> in(sineWave);
StreamCopy copier(afft, in);
//CsvOutput<int16_t> out(Serial);
MiniAudioStream out;
StreamCopy copierIFFT(out, afft);

// process fft result
void fftResult(AudioFFTBase &fft) {
  // copy ifft result to output
  while (copierIFFT.copy());
}

void setup() {
  AudioToolsLogger.begin(Serial, AudioToolsLogLevel::Warning);

  // set the frequency
  sineWave.setFrequency(N_B4);

  // Setup sine wave
  auto cfg = in.defaultConfig();
  cfg.copyFrom(info);
  in.begin(cfg);

  // Setup FFT
  auto tcfg = afft.defaultConfig(RXTX_MODE);
  tcfg.copyFrom(info);
  tcfg.length = 1024;
  tcfg.window_function = &buffered;
  tcfg.stride = 512;
  tcfg.callback = fftResult;
  afft.begin(tcfg);

  // setup output
  auto ocfg = out.defaultConfig(TX_MODE);
  ocfg.copyFrom(info);
  out.begin(ocfg);
}

void loop() { copier.copy(); }