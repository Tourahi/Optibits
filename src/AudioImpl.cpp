#include <Optibits/AudioImpl.hpp>
#include <stdexcept>
#include <string>

using namespace std;

#ifdef OPTIBITS_IPHONE
static const unsigned CHANNELS = 32;
#else
static const unsigned CHANNELS = 255;
#endif


static ALCdevice* _device;
static ALCcontext* _context;
static ALuint _sources[CHANNELS];
static int _tokens[CHANNELS];

void Optibits::alInit()
{
  if (_device) return;

  _device = alcOpenDevice(nullptr);
  _context = alcCreateContext(_device, nullptr);
  alcMakeContextCurrent(_context);
  alGenSources(CHANNELS, _sources);
}

bool Optibits::alInited()
{
  return _device != nullptr;
}

bool Optibits::channelExpired(int channel, int token)
{
  return channel < 0 || channel >= CHANNELS || _tokens[channel] != token;
}

ALuint Optibits::alSourceForChannel(int channel)
{
  if (channel < 0 || channel >= CHANNELS) {
    throw invalid_argument("No suc channel: " + to_string(channel)); 
  }
  return _sources[channel];
}

ALuint Optibits::alSourceForSongs()
{
  return _sources[0];
}
