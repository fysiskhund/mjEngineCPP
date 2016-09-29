#ifndef MJINPUT_H
#define MJINPUT_H

namespace mjEngine{

class mjInput{
public:
    int controllerNum;

    mjVector3 mainStick; // left stick
    mjVector3 secStick; // right stick

    bool button1_pressed;

private:

};


}
#endif
