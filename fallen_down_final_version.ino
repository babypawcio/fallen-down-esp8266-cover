// PROGMEM - storing constant, big variables in flash instead of RAM (global/functions, not in loops), slower than SRAM
// EEPROM - storing constant (slow, configs etc.)
// SRAM - fast acces to data, small capacity

// selected pins

#define BASS D0
#define MELODY1 D1
#define MELODY2 D2

// notes and their frequency

#define NOTE_D2 73
#define NOTE_E2 82
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_E3 165
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5S 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_A5 880
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109

// used for speeding up / slowing melody
// static means variable exists till the end of the program

const static float songSpeed = 1.5;

// jumping through main melody notes

const static int melodyNotes[] PROGMEM = {

  NOTE_FS5, NOTE_C5S, NOTE_FS5, NOTE_C5S, NOTE_FS5, NOTE_C5S,
  NOTE_FS5, NOTE_C5S, NOTE_FS5, NOTE_C5S, NOTE_FS5, NOTE_C5S,
  NOTE_B4, NOTE_A4, NOTE_C5S,
  NOTE_A4, NOTE_B4, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_FS5, NOTE_DS5,

  NOTE_B4, NOTE_FS5, NOTE_B4, NOTE_FS5, NOTE_B4, NOTE_FS5, NOTE_B4, NOTE_FS5,
  NOTE_AS4, NOTE_FS5, NOTE_AS4, NOTE_G5, NOTE_AS4,
  NOTE_FS5, NOTE_D5, NOTE_FS5, NOTE_D5, NOTE_E5, NOTE_FS5,
  NOTE_E5, NOTE_D5, NOTE_C5S,

  // can be repeated 3 times

  NOTE_D5, NOTE_A4, NOTE_B4, NOTE_C5S, NOTE_D5, NOTE_C5S, NOTE_D5,
  NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_FS4,

  // first chord

  NOTE_D5, NOTE_C5S, NOTE_B4,

  // further melody + one chord

  NOTE_A4, NOTE_B4, NOTE_C5S, NOTE_D5, NOTE_C5S, NOTE_D5, NOTE_D5, NOTE_G5, NOTE_FS5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_C5S,

  // continuation without repetition

  NOTE_A4, NOTE_A5, NOTE_E5,
  NOTE_D5, NOTE_A5, NOTE_A4,
  NOTE_A4, NOTE_D5, NOTE_A5,
  NOTE_B5, NOTE_A5, NOTE_E5, NOTE_D5,           // B5 is shorter than the other notes

  // can also be repeated

  NOTE_A4, NOTE_A5, NOTE_FS5, NOTE_E5, NOTE_D5, NOTE_C5S, NOTE_D5, NOTE_E5,
  NOTE_CS6, NOTE_C6, NOTE_B5, NOTE_A5,
  NOTE_B4, NOTE_A5, NOTE_FS5, NOTE_E5, NOTE_D5, NOTE_C5S, NOTE_E5, NOTE_FS5,
  NOTE_C5S, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_C5S, NOTE_D5, NOTE_A4,

  // can also be repeated

  // last 30 secs of melody

  NOTE_D4, NOTE_E4, NOTE_D4, NOTE_GS3,
  NOTE_D4, NOTE_E4, NOTE_D4, NOTE_G3,
  NOTE_D4, NOTE_E4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_D4, NOTE_A3, NOTE_A4,

  NOTE_D4, NOTE_E4, NOTE_D4, NOTE_GS3,
  NOTE_D4, NOTE_E4, NOTE_D4, NOTE_G3,
  NOTE_D4, NOTE_E4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_D4, NOTE_A3, NOTE_A4,

  NOTE_D4, NOTE_E4, NOTE_D4, NOTE_A3, NOTE_D4, NOTE_E4, NOTE_FS4, NOTE_E4, NOTE_D4

};

// we can use only one duration table, because all the other notes are passing by in the same time,
// to prolong, for example, the sound of bass notes, we simply place them behind the melodic notes a few times
// and we do not need to create the new duration table for them

const static int melodyDurations[] PROGMEM = {

  545, 545, 545, 545, 545, 545,
  545, 545, 545, 545, 545, 545,
  545, 545, 1045,
  545, 545, 545, 545, 545, 545, 545,

  545, 545, 545, 545, 545, 545, 545, 545,
  545, 545, 545, 545, 545,
  545, 545, 545, 545, 545, 545,
  1045, 1045, 1045,

  // can be repeated 3 times

  1045, 545, 545, 545, 1045, 545, 545,
  1045, 545, 545, 545, 1045,

  // first chord

  1045, 1045, 1045,

  // further melody + one chord

  545, 545, 545, 1045, 1045, 1045, 1045, 545, 545, 545, 1045, 1045, 1045,

  // continuation without repetition

  1545, 1545, 1545,
  1545, 1545, 1545,
  1545, 1545, 1545,
  545, 1545, 1545, 1545,           // B5 is shorter than the other notes

  // can also be repeated
              
  1545, 1045, 545, 1045, 545, 1045, 545, 1045,
  545, 545, 545, 1545,                   
  1545, 1045, 545, 1045, 545, 1045, 545, 545,                   
  1545, 1045, 1045, 545, 1045, 545, 545,

  // can also be repeated

  // last 30 secs of melody
  
  545, 1045, 545, 1045,
  545, 1045, 545, 1045,
  545, 1045, 545, 1045, 545, 1045, 545, 1045,

  545, 1045, 545, 1045,
  545, 1045, 545, 1045,
  545, 1045, 545, 1045, 545, 1045, 545, 1045,

  545, 1045, 545, 1045, 545, 1045, 545, 545, 2045

};

// 0 - means no notes are playing (no chord)
// other option - note playing in the same time as the note in a main melody

const static int chords[] PROGMEM = {

  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0,
  0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0,

  // can be repeated 3 times

  0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0,

  // first chord

  NOTE_FS5, NOTE_E5, NOTE_D5,

  // further melody + one chord

  0, 0, 0, 0, 0, 0, NOTE_FS5, 0, 0, 0, 0, 0, 0,

  // continuation without repetition

  0, 0, 0,
  0, 0, 0,
  0, 0, 0,
  0, 0, 0, 0,

  // can also be repeated

  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0,

  // can also be repeated

  // last 30 secs of melody

  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0
  
};

// bass notes, several playing at the same time as the notes from the main melody
// so we dont need to create new duration table for them

const static int bass[] PROGMEM = {

  NOTE_D3, NOTE_D3, NOTE_D3, NOTE_D3, NOTE_D3, NOTE_D3,
  NOTE_D3, NOTE_D3, NOTE_D3, NOTE_D3, NOTE_D3, NOTE_D3,
  NOTE_B2, NOTE_B2, NOTE_B2,
  NOTE_B2, NOTE_B2, NOTE_B2, NOTE_B2, NOTE_B2, NOTE_B2, NOTE_B2,

  NOTE_B2, NOTE_G2, NOTE_G2, NOTE_G2, NOTE_G2, NOTE_G2, NOTE_G2, NOTE_G2,
  NOTE_G2, NOTE_G2, NOTE_G2, NOTE_G2, NOTE_G2,
  NOTE_D3, NOTE_D3, NOTE_D3, NOTE_D3, NOTE_D3, NOTE_D3,
  NOTE_CS3, NOTE_CS3, NOTE_CS3,

  // can be repeated 3 times

  NOTE_G3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_A3, NOTE_A3,
  NOTE_D3, NOTE_D3, NOTE_D3, NOTE_D3, NOTE_D2,

  // first chord

  NOTE_E2, NOTE_FS2, NOTE_G2,

  // further melody + one chord

  NOTE_G2, NOTE_G2, NOTE_G2, NOTE_A2, NOTE_A2, NOTE_AS2, NOTE_B2, NOTE_B2, NOTE_B2, NOTE_B2, NOTE_A2, NOTE_A2, NOTE_A2,

  // continuation without repetition

  NOTE_D3, NOTE_D3, NOTE_CS3,
  NOTE_B2, NOTE_B2, NOTE_A2,
  NOTE_G2, NOTE_G2, NOTE_FS2,
  NOTE_FS2, NOTE_E2, NOTE_E2, NOTE_A2,           // B5 is shorther than the other notes

  // can also be repeated

  NOTE_G3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_FS3,
  NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_FS3,
  NOTE_E3, NOTE_E3, NOTE_E3, NOTE_A3, NOTE_A3, NOTE_A3, NOTE_A3, NOTE_A3,
  NOTE_AS3, NOTE_AS3, NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3, NOTE_G3,

  // can also be repeated

  // last 30 secs of melody

  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, NOTE_D3,

  NOTE_D3, NOTE_D3, NOTE_D3, 0,
  0, 0, 0, 0,
  0, 0, 0, NOTE_D2, NOTE_D2, NOTE_D2, NOTE_G2, NOTE_G2,

  NOTE_G2, NOTE_G2, NOTE_G2, 0, 0, 0, 0, 0, NOTE_D3
 
};

void setup() {

  // setuping our buzzers as an output

  pinMode(BASS, OUTPUT);
  pinMode(MELODY1, OUTPUT);
  pinMode(MELODY2, OUTPUT);

  // calculating length of the notes' table

  unsigned const static int totalNotes PROGMEM = sizeof(melodyNotes) / sizeof(int);

  // jumping throught notes

  for (int i = 0; i < totalNotes; i++)
  {
    const int currentNote = melodyNotes[i];
    const float melodyDelay = melodyDurations[i] / songSpeed;

    // play tone if currentNote is not 0 frequency, otherwise pause (noTone)
    if (currentNote != 0)
    {

      // tone(buzzer, note/frequency, duration)  -- > duration is optional, works without it too,
      // but at the end, the last note is still playing 

      tone(MELODY1, melodyNotes[i], melodyDelay);
      tone(MELODY2, chords[i], melodyDelay);
      tone(BASS, bass[i], melodyDelay);
    }

    else
    {

      // noTone(buzzer we want to turn off)

      noTone(MELODY1);
      noTone(MELODY2);
      noTone(BASS);
    }

    // delay is used to wait for tone to finish playing before moving to next loop
    delay(melodyDelay);

  }

}


void loop() {

  // we can copy paste our setup function if we want to play it all the time

}
