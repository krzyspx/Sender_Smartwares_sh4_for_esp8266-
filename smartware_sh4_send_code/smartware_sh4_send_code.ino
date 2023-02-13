
const static int _pulseLength = 190;
const static long _beginPulses = 14, _shortPulses = 2, _longPulses = 7, _waitPulses = 55, _maxPulses = 400;
const static int _min_packets = 2;
const static int _error = 25;
const static int _numBits = 32;


const int remoteId = 25134;
unsigned long commandon = 1251672081;  //my pilot;s code - on
unsigned long commandoff = 1251672065;  //my pilot;s code - off


void setup() {
  pinMode(14, OUTPUT);

}

void loop() {

  sendRaw(commandon, 4);

  //wait 2 seconds
  delay(3 * 1000);
  sendRaw(commandoff, 4);

  //wait 2 seconds
  delay(3 * 1000);
/*  
  int button = 1; // up to 15 buttons (4 bits)
  boolean onOff = true; // true or false

  remote.sendCommand(remoteId, button , onOff);

  //wait 2 seconds
  delay(2 * 1000);

  button = 2;
  int repeat = 6;
  remote.sendCommand(remoteId, button , onOff, repeat);

  //wait 2 seconds
  delay(2 * 1000);

  // Tou can also create a packet and send it!
  Sf501Packet packet;
  packet.remoteId = remoteId;
  packet.state = onOff;
  packet.channel = 3;

  remote.sendPacket(packet);

  //wait 2 seconds
  delay(2 * 1000);

  //You can also send a raw command, usefull when implementing a learning mechanism
  long command = 556793876; // remote id 25134, channel 4, button ON
  remote.sendRaw(command);

  //wait 2 seconds
  delay(2 * 1000);

  //turn everything off
  int numberOfChannels = 4;
  onOff = false;

  remote.switchAll(remoteId, numberOfChannels , onOff);

  //wait 6 seconds
  delay(6 * 1000);
*/
}


void sendPacket(int remoteId, int channel, int state, int repeat) {
  sendCommand(remoteId, channel, state, repeat);
};

void sendCommand(int remoteId, int channel, int onOff, int repeat)
{
  long command = 0;
  command += remoteId;
  command <<= 16;
  command |= onOff << 4;
  command |= constrain(channel, 1, 15);
  sendRaw(command, repeat);
}

void switchAll(int remoteId, int numChannels, int onOff, int repeat) {

  for (int i = 1; i <= constrain(numChannels, 1, 15); i++)
  {
    sendCommand(remoteId, i, onOff, repeat);
  }

}

void sendRaw(unsigned long command, int repeat) {

  while (repeat) {
    _pulseStart();

    for (int i = 31; i >= 0 ; i--) {
      if ((command >> i) & 1 ) {
        _pulseLong();
        _pulseShort();
      } else {
        _pulseShort();
        _pulseLong();
      }
    }
    //end pulse
    _pulse();

    if (repeat > 1) delayMicroseconds(_pulseLength * (_waitPulses - 1));
    repeat--;
  }
}


void _pulse()
{
  digitalWrite(14, HIGH);
  delayMicroseconds(_pulseLength);
  digitalWrite(14, LOW);
}
void _pulseStart()
{
  _pulse();
  delayMicroseconds(_pulseLength * 14);
}
void _pulseShort()
{
  _pulse();
  delayMicroseconds(_pulseLength * 2);
}

void _pulseLong()
{
  _pulse();
  delayMicroseconds(_pulseLength * 7);
}
