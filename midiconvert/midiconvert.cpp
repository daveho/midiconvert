#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include "MidiFile.h"
#include "Options.h"

// scale velocity to signal amplitude
const double SCALE_VELOCITY = 1.0f;

using namespace std;
using namespace smf;

int main(int argc, char** argv) {
  Options options;
  options.process(argc, argv);
  MidiFile midifile;
  if (options.getArgCount() == 0) midifile.read(cin);
  else midifile.read(options.getArg(1));
  midifile.doTimeAnalysis();
  midifile.linkNotePairs();

  midifile.joinTracks();
  assert(midifile.getTrackCount() == 1);

  // figure out timing
  int totalTicks = midifile.getFileDurationInTicks();
  double totalSeconds = midifile.getFileDurationInSeconds();

  double totalSamples = ceil(totalSeconds * 44100.0);

  cout << long(totalSamples) << endl;

  int tracks = midifile.getTrackCount();
//  cout << "TPQ: " << midifile.getTicksPerQuarterNote() << endl;
//  if (tracks > 1) cout << "TRACKS: " << tracks << endl;
//  for (int track=0; track<tracks; track++) {
    int track = 0;
//    if (tracks > 1) cout << "\nTrack " << track << endl;
//    cout << "Tick\tSeconds\tDur\tMessage" << endl;
    for (int event=0; event<midifile[track].size(); event++) {
/*
      cout << dec << midifile[track][event].tick;
      cout << '\t' << dec << midifile[track][event].seconds;
      cout << '\t';
      if (midifile[track][event].isNoteOn())
        cout << midifile[track][event].getDurationInSeconds();
      cout << '\t' << hex;
      for (int i=0; i<midifile[track][event].size(); i++)
        cout << (int)midifile[track][event][i] << ' ';
      cout << endl;
*/

      MidiEvent &ev = midifile[track][event];

      if (ev.isNoteOn()) {
        int channel = ev.getChannel();
#if 0
        int startTick = ev.tick;
        int duration = ev.getTickDuration();
#endif
        int noteNumber = ev.getKeyNumber();
        int velocity = ev.getVelocity();

#if 0
        cout << "startTick=" << startTick
             << ", duration=" << duration
             << ", noteNumber=" << noteNumber
             << ", velocity=" << velocity
             << ", channel=" << channel
             << endl;
        long startSample = long(startTick * samplesPerTick);
        long endSample = long(startSample + (duration * samplesPerTick));
#endif
        double startTimeSec = midifile.getTimeInSeconds(ev.tick);
        double durationSec = ev.getDurationInSeconds();
#if 0
        cout << "startTimeSec=" << startTimeSec
             << ", durationSec=" << durationSec << endl;
#endif

        unsigned startSample = unsigned(startTimeSec * 44100.0);
        unsigned endSample = startSample + unsigned(durationSec * 44100.0);

        double amplitude = (velocity / 127.0) * SCALE_VELOCITY;
        cout << "N " << channel
             << " " << startSample
             << " " << endSample
             << " " << noteNumber
             << " " << amplitude
             << endl;
      }
    }
  //}

  return 0;
}
