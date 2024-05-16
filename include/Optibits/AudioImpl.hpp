#pragma once

#include "Audio.hpp"
#include <Optibits/Audio.hpp>
#include <Optibits/Platform.hpp>

#ifdef OPTIBITS_IPHONE
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <al.h>
#include <alc.h>
#endif


namespace Optibits
{

  void alInit();
  bool alInited();

  ALCcontext* alContext();

  const int NO_CHANNEL = -1;

  Channel allocateChannel();

  bool channelExpired(int channel, int token);

  ALuint alSourceForChannel(int channel);
  ALuint alSourceForSongs();
}