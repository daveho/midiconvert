# midiconvert

Convert a MIDI file to a `render_song` input file for the
[Spring 2021 JHU Intermediate Programming midterm project](https://jhu-ip.github.io/cs220-sp21/docs/assignments/midterm/).

Uses the amazingly great [midifile](https://github.com/craigsapp/midifile)
library by Craig Sapp.  `midifile` is open source, see its
[README.md](midifile/README.md) and [LICENSE.txt](midifile/LICENSE.txt).

To build:

```
cd midiconvert
make
```

To convert a MIDI file:

```
./midiconvert song.mid > song.txt
```
