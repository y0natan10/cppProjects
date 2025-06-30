# Guitar Trainer

## Overview
Guitar Trainer is a C++ application to help guitar players learn and practice chords. It can display chord diagrams, show note locations on the fretboard, and process chord progressions.

## Features
- Processes chord progressions like `C Am F G E7`
- If you enter a single token, prompts to display a chord diagram or note locations
- Chord diagrams are shown vertically, with string names at the top and fret numbers on the left
- Prints a fretboard diagram showing where a note occurs on each string (frets 0–12)
- Handles enharmonic inputs (e.g., `B#` is treated as `C`, `E#` as `F`)
- Suggests chords that fit a set of notes

## File Structure
```
GuitarTrainer/
├── GuitarTrainer.cpp   # Main application source file
├── GuitarTrainer.exe   # Compiled executable (ignored by git)
├── README.md           # This documentation
```

## Usage
1. Compile `GuitarTrainer.cpp` using your C++ compiler:
   ```sh
   g++ GuitarTrainer.cpp -o GuitarTrainer.exe
   ```
2. Run the application:
   ```sh
   ./GuitarTrainer.exe
   ```
3. Follow the prompts to input chords or note names.
