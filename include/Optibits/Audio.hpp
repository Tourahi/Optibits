#pragma once



namespace Optibits
{
  /// Channel class
  class Channel
  {

    mutable int mChannel, mToken;

  public:

    Channel();

    Channel(int channel, int token);

    int currentChannel() const;

    bool playing() const;
    bool paused() const;

    void pause();
    void resume();

    void stop();

    void setVolume(double volume);
    void setPan(double pan);
    void setSpeed(double speed);

  };



}
