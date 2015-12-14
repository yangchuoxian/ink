#include "batterydriver.h"
#include <QDebug>
BatteryDriver::BatteryDriver() : QThread()
{
}
void BatteryDriver::run()
{
    int fdForBattery;
    char battery_status[5] = {1, 1, 1, 1, 1};
    fdForBattery = open("/dev/inkps_battery", 0);
    if(fdForBattery < 0){
        printf("Open Battery Device Faild!\n");
        exit(1);
    }
    while(1){
        int ret;
        fd_set rds;
        FD_ZERO(&rds);
        FD_SET(fdForBattery, &rds);
        //for buttons driver
        //应用程序进行轮询，查询是否可对设备进行访问
        ret = select(fdForBattery + 1, &rds, NULL, NULL, NULL);
        if(ret < 0){
            printf("Read Battery Device Failed!\n");
            exit(1);
        }

        if(ret == 0){
            printf("Read Battery Device Timeout!\n");
        }
        else if(FD_ISSET(fdForBattery, &rds)){
            //读设备
            ret = read(fdForBattery, battery_status, sizeof(battery_status));
            if(ret != sizeof(battery_status)){
                if(errno != EAGAIN){
                    printf("Read Battery Device Failed!\n");
                }

                continue;
            }
            else{
qDebug() << "GPF2:" << battery_status[0] << " GPF1:" << battery_status[1]  << " GPF4:" << battery_status[2] << " GPF0:" << battery_status[3] << " GPF12" << battery_status[4];
                if (battery_status[4] == '1') {
                    emit chargingStatus(true);
                }
                else{
                    emit chargingStatus(false);
                }
                if ((battery_status[0] == '0') &&
                    (battery_status[1] == '0') &&
                    (battery_status[2] == '0') &&
                    (battery_status[3] == '0')){
                    emit batteryPercentage(0);
                }
                if ((battery_status[0] == '1') &&
                    (battery_status[1] == '0') &&
                    (battery_status[2] == '0') &&
                    (battery_status[3] == '0')){
                    qDebug() << "now at 25%";
                    emit batteryPercentage(25);
                }
                if ((battery_status[0] == '1') &&
                    (battery_status[1] == '1') &&
                    (battery_status[2] == '0') &&
                    (battery_status[3] == '0')){
                    qDebug() << "now at 50%";
                    emit batteryPercentage(50);
                }
                if ((battery_status[0] == '1') &&
                    (battery_status[1] == '1') &&
                    (battery_status[2] == '1') &&
                    (battery_status[3] == '0')){
                    qDebug() << "now at 75%";
                    emit batteryPercentage(75);
                }
                if ((battery_status[0] == '1') &&
                    (battery_status[1] == '1') &&
                    (battery_status[2] == '1') &&
                    (battery_status[3] == '1')){
                    qDebug() << "now at 100%";
                    emit batteryPercentage(100);
                }
            }
        }
    }
    close(fdForBattery);
}
