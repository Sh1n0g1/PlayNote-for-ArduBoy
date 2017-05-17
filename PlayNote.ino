#include <Arduboy2.h>
#include <ArduboyPlaytune.h>

Arduboy2 arduboy;
ArduboyPlaytune tunes(arduboy.audio.enabled);
int FORM_WIDTH=12;
int FORM_HEIGHT=10;
int MASS_WIDTH=6;
int MASS_HEIGHT=6;
int x;
int y;
const float TONEUP=1.059463094359; //http://www.phy.mtu.edu/~suits/NoteFreqCalcs.html
const float C0 = 16.351; //http://www.liutaiomottola.com/formulae/freqtab.htm
const int NOTE_LENGTH=200; //millisec
float note[]={0,0,0,0,0,0,0,0};

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(10);

  //audio setup
  tunes.initChannel(PIN_SPEAKER_1);
  tunes.initChannel(PIN_SPEAKER_2);
    
  
  x=0;
  y=4;
}


void saveNote(float newnote){
  for(int i=7; i > 0; i--){
    note[i]=note[i-1];
  }
  note[0]=newnote;
}

void loop() {
  arduboy.clear();
  if (!(arduboy.nextFrame()))
    return;
 if(arduboy.everyXFrames(1)){
  if(arduboy.pressed(UP_BUTTON)){
    y = (y + FORM_HEIGHT -1) % FORM_HEIGHT;    
  }
  if(arduboy.pressed(DOWN_BUTTON)){
   y = (y + FORM_HEIGHT + 1) % FORM_HEIGHT;
  }
  if(arduboy.pressed(LEFT_BUTTON)){
   x = (x + FORM_WIDTH - 1) % FORM_WIDTH;
   if(x % FORM_WIDTH == FORM_WIDTH - 1 ){
       y = (y + FORM_HEIGHT - 1) % FORM_HEIGHT; 
   }
  }
  if(arduboy.pressed(RIGHT_BUTTON)){
   x = (x + FORM_WIDTH + 1) % FORM_WIDTH;
   if(x==0){
       y = (y + FORM_HEIGHT + 1) % FORM_HEIGHT; 
   }    
  }
  if(arduboy.pressed(B_BUTTON)){
     float newnote=C0;
     for(int i=1; i <= y * FORM_WIDTH + x ; i++){
        newnote *= TONEUP;
     }
     saveNote(newnote);
     tunes.tone(note[0],NOTE_LENGTH);
  }
 }
  int MARGIN_X=128 - (MASS_WIDTH * FORM_WIDTH);
  int MARGIN_Y=(64 - MASS_HEIGHT * FORM_HEIGHT)/2;
  for(int i=0; i < FORM_WIDTH; i++){
    for(int j=0; j < FORM_HEIGHT; j++){
      if(i == 1 || i==3 || i==6 || i==8 || i==10){
         arduboy.drawRect(
          i * MASS_WIDTH + MARGIN_X,
          j * MASS_HEIGHT + MARGIN_Y,
          MASS_WIDTH +1,
          MASS_HEIGHT +1
        );  
      }else{
        arduboy.fillRect(
          i * MASS_WIDTH + MARGIN_X,
          j * MASS_HEIGHT + MARGIN_Y,
          MASS_WIDTH +1,
          MASS_HEIGHT +1
        );  
      }
      
      if(x==i && y==j){
        arduboy.drawRect(
          x * MASS_WIDTH + MARGIN_X + 1,
          y * MASS_HEIGHT + MARGIN_Y + 1,
          MASS_WIDTH - 1,
          MASS_HEIGHT - 1
        );
        arduboy.drawRect(
          x * MASS_WIDTH + MARGIN_X + 2,
          y * MASS_HEIGHT + MARGIN_Y + 2,
          MASS_WIDTH - 2,
          MASS_HEIGHT - 2,
          BLACK
        );
      }
    }
  }
  for(int i=0; i < 8; i++){
    arduboy.print(note[i]);
    arduboy.print('\n');
  }
  arduboy.display();
}

