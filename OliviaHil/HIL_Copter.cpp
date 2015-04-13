//
//  HIL_Copter.cpp
//  dSim
//
//  Created by Hao Xu on 15/4/13.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#include "HIL_Copter.h"

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#include <sys/time.h>

//#define DEBUG_O

long getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

int hil_copter::open_port(const char* port)
{
    
    fd = open(port, O_RDWR | O_NOCTTY |O_NONBLOCK);
    if (fd == -1)
    {
        /* Could not open the port. */
        return(-1);
    }
    else
    {
        /* Set to blocking mode */
        //fcntl(fd, F_SETFL, 0);
        /* set to non-blocking mode */
        fcntl(fd, F_SETFL, FNDELAY);
    }
    
    return (fd);
}

bool hil_copter::setup_port(int baud, int data_bits, int stop_bits, bool parity, bool hardware_control)
{
    //struct termios options;
    
    struct termios  config;
    if(!isatty(fd))
    {
        fprintf(stderr, "\nERROR: file descriptor %d is NOT a serial port\n", fd);
        return false;
    }
    if(tcgetattr(fd, &config) < 0)
    {
        fprintf(stderr, "\nERROR: could not read configuration of fd %d\n", fd);
        return false;
    }
    //
    // Input flags - Turn off input processing
    // convert break to null byte, no CR to NL translation,
    // no NL to CR translation, don't mark parity errors or breaks
    // no input parity check, don't strip high bit off,
    // no XON/XOFF software flow control
    //
    config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL |
                        INLCR | PARMRK | INPCK | ISTRIP | IXON);
    //
    // Output flags - Turn off output processing
    // no CR to NL translation, no NL to CR-NL translation,
    // no NL to CR translation, no column 0 CR suppression,
    // no Ctrl-D suppression, no fill characters, no case mapping,
    // no local output processing
    //
    config.c_oflag &= ~(OCRNL | ONLCR | ONLRET |
                        ONOCR | OFILL | OPOST);
    
    config.c_cflag &=CLOCAL;
    
#ifdef OLCUC
  		config.c_oflag &= ~OLCUC;
#endif
    
#ifdef ONOEOT
  		config.c_oflag &= ~ONOEOT;
#endif
    
    
    //
    // No line processing:
    // echo off, echo newline off, canonical mode off,
    // extended input processing off, signal chars off
    //
    config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
    //
    // Turn off character processing
    // clear current char size mask, no parity checking,
    // no output processing, force 8 bit input
    //
    config.c_cflag &= ~(CSIZE | PARENB);
    config.c_cflag |= CS8;
    
    /* turn off hardware flow control */
    config.c_cflag &= ~CRTSCTS;
    
    //
    // One input byte is enough to return from read()
    // Inter-character timer off
    //
    config.c_cc[VMIN]  = 1;
    config.c_cc[VTIME] = 10; // was 0
    
    // Get the current options for the port
    //tcgetattr(fd, &options);
    
    switch (baud)
    {
        case 1200:
            if (cfsetispeed(&config, B1200) < 0 || cfsetospeed(&config, B1200) < 0)
            {
                fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
                return false;
            }
            break;
        case 1800:
            cfsetispeed(&config, B1800);
            cfsetospeed(&config, B1800);
            break;
        case 9600:
            cfsetispeed(&config, B9600);
            cfsetospeed(&config, B9600);
            break;
        case 19200:
            cfsetispeed(&config, B19200);
            cfsetospeed(&config, B19200);
            break;
        case 38400:
            if (cfsetispeed(&config, B38400) < 0 || cfsetospeed(&config, B38400) < 0)
            {
                fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
                return false;
            }
            break;
        case 57600:
            if (cfsetispeed(&config, B57600) < 0 || cfsetospeed(&config, B57600) < 0)
            {
                fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
                return false;
            }
            break;
        case 115200:
            if (cfsetispeed(&config, B115200) < 0 || cfsetospeed(&config, B115200) < 0)
            {
                fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
                return false;
            }
            break;
            
            // These two non-standard (by the 70'ties ) rates are fully supported on
            // current Debian and Mac OS versions (tested since 2010).
        case 460800:
            if (cfsetispeed(&config, 460800) < 0 || cfsetospeed(&config, 460800) < 0)
            {
                fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
                return false;
            }
            break;
        case 921600:
            if (cfsetispeed(&config, 921600) < 0 || cfsetospeed(&config, 921600) < 0)
            {
                fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
                return false;
            }
            break;
        default:
            fprintf(stderr, "ERROR: Desired baud rate %d could not be set, aborting.\n", baud);
            return false;
            
            break;
    }
    
    //
    // Finally, apply the configuration
    //
    if(tcsetattr(fd, TCSAFLUSH, &config) < 0)
    {
        fprintf(stderr, "\nERROR: could not set configuration of fd %d\n", fd);
        return false;
    }
    return true;
}


void hil_copter::control()
{
    for(int i = 0;i<motors.size();i++)
    {
        motors[i].set( actuator[i]);
    }
}

float hil_copter::cvtpwm2act(uint16_t pwm)
{
    float tmp = (float)(pwm - 1000) /1000.0f;
    if (tmp<0)
        tmp = 0;
    if(tmp>1)
        tmp = 1;
    return tmp;
}

void hil_copter::handle_msg(mavlink_message_t* msg)
{
    switch (msg->msgid)
    {
        case
        MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:
            mavlink_servo_output_raw_t servos;
        
            mavlink_msg_servo_output_raw_decode(msg,&servos);
        
            
            actuator[0] = cvtpwm2act(servos.servo1_raw);
            actuator[1] = cvtpwm2act(servos.servo2_raw);
            actuator[2] = cvtpwm2act(servos.servo3_raw);
            actuator[3] = cvtpwm2act(servos.servo4_raw);
            actuator[4] = cvtpwm2act(servos.servo5_raw);
            actuator[5] = cvtpwm2act(servos.servo6_raw);
            actuator[6] = cvtpwm2act(servos.servo7_raw);
            actuator[7] = cvtpwm2act(servos.servo8_raw);
        
            for(int i= 0 ;i<6;i++)
            {
                printf("%4.4f,",actuator[i]);
            }
        
            printf("\n");
            
            static long last = 0;
            static int k = 0;
            
            k++;
            
            if(k%100 == 0)
            {
                long now = getCurrentTime() - last;
                last = getCurrentTime();
                printf("%f\n", 100000000.0f/(float)now );
            }
            break;
            
    }
}

int hil_copter::send_att()
{

    static mavlink_hil_state_quaternion_t state;
    
    
    state.alt = pos.z * 100;
    
    state.attitude_quaternion[0] = _quat.w;
    state.attitude_quaternion[1] = _quat.x;
    state.attitude_quaternion[2] = _quat.y;
    state.attitude_quaternion[3] = _quat.z;
    
    
    state.vx = vel.x * 100.0f;
    state.vy = vel.y * 100.0f;
    state.vz = vel.z * 100.0f;
    
    state.x = pos.x * 100.0f;
    state.y = pos.y * 100.0f;
    state.z = pos.z * 100.0f;
    
    static int k = 0;
    if(k++ % 100 == 0)
        printf("%4.4f,%4.4f,%4.4f\n",pos.x,pos.y,pos.z);
    
    printf("yaw speed:%8.4f\n",yaw_rate);
//
    state.pitchspeed = pitch_rate;
    state.rollspeed = roll_rate;
    state.yawspeed = yaw_rate;
   
    static mavlink_message_t msg;
    mavlink_msg_hil_state_quaternion_encode(200, 0, &msg, &state);
    
    if (send_msg(&msg)<=0)
        printf("failed\n");
    
    return 0;
    
}

void hil_copter::run()
{
    base_copter::run();
}

int hil_copter::send_msg(mavlink_message_t * msg)
{
    static uint8_t buffer[1024];
    int len = mavlink_msg_to_send_buffer(buffer, msg);
    int count = (int)  write(fd, buffer, len);
    return count;
}



int hil_copter::serial_wait()
{
    
    mavlink_status_t lastStatus;
    lastStatus.packet_rx_drop_count = 0;
    
    // Blocking wait for new data
    while (1)
    {
        uint8_t cp;
        mavlink_message_t message;
        mavlink_status_t status;
        uint8_t msgReceived = false;
        
        if (read(fd, &cp, 1) > 0)
        {
            // Check if a message could be decoded, return the message in case yes
            msgReceived = mavlink_parse_char(MAVLINK_COMM_1, cp, &message, &status);
            if (lastStatus.packet_rx_drop_count != status.packet_rx_drop_count)
            {
//                fprintf(stderr,"%02x ", v);
            }
            lastStatus = status;
        }
        else
        {
        }
        
        // If a message could be decoded, handle it
        if(msgReceived)
        {
            //if (verbose || debug) std::cout << std::dec << "Received and forwarded serial port message with id " << static_cast<unsigned int>(message.msgid) << " from system " << static_cast<int>(message.sysid) << std::endl;
            
            // Do not send images over serial port
            
            // DEBUG output
#ifdef DEBUG_O
            {
                fprintf(stderr,"Received serial data: ");
                unsigned int i;
                uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
                unsigned int messageLength = mavlink_msg_to_send_buffer(buffer, &message);
                if (messageLength > MAVLINK_MAX_PACKET_LEN)
                {
                    fprintf(stderr, "\nFATAL ERROR: MESSAGE LENGTH IS LARGER THAN BUFFER SIZE\n");
                }
                else
                {
                    for (i=0; i<messageLength; i++)
                    {
                        unsigned char v=buffer[i];
                        fprintf(stderr,"%02x ", v);
                    }
                    fprintf(stderr,"\n");
                }
            }
            
            printf("Received message from serial with ID #%d (sys:%d|comp:%d):\n", message.msgid, message.sysid, message.compid);
            
#endif
            handle_msg(&message);
            
            
        }
    }
    return 0;
}
