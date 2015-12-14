#include "buttondriver.h"

ButtonDriver::ButtonDriver() : QThread()
{
}
void ButtonDriver::run()
{
    int fdForKeys;
    char key_status[6] = {1, 1, 1, 1, 1, 1};
    //char battery_status[5] = {1, 1, 1, 1, 1};
    //以阻塞方式打开设备文件，非阻塞时flags=O_NONBLOCK
    fdForKeys = open("/dev/inkps_keys", 0);
    if(fdForKeys < 0){
        printf("Open Buttons Device Faild!\n");
        exit(1);
    }

    while(1){
        int i;
        int ret;
        fd_set rds;
        FD_ZERO(&rds);
        FD_SET(fdForKeys, &rds);
        //for buttons driver
        //应用程序进行轮询，查询是否可对设备进行访问
        ret = select(fdForKeys + 1, &rds, NULL, NULL, NULL);
        if(ret < 0){
            printf("Read Buttons Device Failed!\n");
            exit(1);
        }

        if(ret == 0){
            printf("Read Buttons Device Timeout!\n");
        }
        else if(FD_ISSET(fdForKeys, &rds)){
            //读设备
            ret = read(fdForKeys, key_status, sizeof(key_status));
            if(ret != sizeof(key_status)){
                if(errno != EAGAIN){
                    printf("Read Button Device Failed!\n");
                }

                continue;
            }
            else{
                for(i = 0; i < 6; i++){
                    //对应驱动中按键的状态，为0即按键被按下
                    if(key_status[i] != '0'){
                        switch(i){
                        case 0:
                            emit this->encoder_turnLeft();;
                            break;
                        case 1:
                            emit this->encoder_turnRight();
                            break;
                        case 2:
                            emit this->buttonLastPage_pressed();
                            break;
                        case 3:
                            emit this->buttonNextPage_pressed();
                            break;
                        case 4:
                            emit this->buttonYes_pressed();
                            break;
                        case 5:
                            emit this->buttonNo_pressed();
                        default:
                            break;
                        }
                    }
                }
            }
        }

    }
    close(fdForKeys);
}
