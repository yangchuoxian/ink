#ifndef BUTTONDRIVER_H
#define BUTTONDRIVER_H
#include <QThread>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

class ButtonDriver : public QThread
{
    Q_OBJECT
public:
    ButtonDriver();
    void run();
signals:
    void encoder_turnLeft();            //the encoder has turned left
    void encoder_turnRight();           //the encoder has turned right
    void buttonLastPage_pressed();      //emit the signal to change tab on the main GUI to the next one
    void buttonNextPage_pressed();      //emit the signal to change tab on the main GUI to the last one
    void buttonYes_pressed();           //emit the signal that the yes button has been pressed
    void buttonNo_pressed();            //emit thie signal that the no button has been pressed
};

#endif // BUTTONDRIVER_H
