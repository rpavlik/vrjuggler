/* Generated by Together */

#ifndef ISOUNDINTERFACE_H
#define ISOUNDINTERFACE_H
#include "SoundFactory.h"

/** @interface */
class ISoundInterface {

public:

    ISoundInterface();

    ~ISoundInterface();

    /**
     * @input alias of the sound to trigger, and number of times to play
     * @preconditions alias does not have to be associated with a loaded sound.
     * @postconditions if it is, then the loaded sound is triggered.  if it isn't then nothing happens.
     * @semantics Triggers a sound
     */
    virtual void trigger(const std::string & alias, const unsigned int & looping = 0) = 0;

    /**
     * @semantics stop the sound
     * @input alias of the sound to be stopped
     */
    virtual void stop(const std::string & name) = 0;

    /**
     * @semantics call once per sound frame (doesn't have to be same as your graphics frame)
     * @input time elapsed since last frame
     */
    virtual void step(const float & timeElapsed) = 0;


    /**
     * @preconditions provide an alias and a filename
     * @postconditions alias will point to loaded sound data
     * @semantics associate an alias to sound data.  later this alias can be used to operate on this sound data.
     */
    virtual void associate(const std::string & alias, const std::string & filename) = 0;


    virtual void remove(const std::string alias) = 0;
    virtual void setPosition( const std::string& alias, float x, float y, float z ) = 0;
private:    

    /** @link dependency */
    /*#  SoundFactory lnkSoundFactory; */
};
#endif  //ISOUNDINTERFACE_H