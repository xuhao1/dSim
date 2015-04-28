//
//  mavlink_unreal.cpp
//  dSim
//
//  Created by Hao Xu on 15/4/26.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#include "mavlink_unreal.h"

void mavlink_unreal::init_network(std::string ip, int port)
{
     //create a UDP socket
    if ((socket_s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        printf("Socket Create failed");
    }
    
    
    if ((socket_s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
        printf("Failed");
    
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(port);
    if (inet_aton(ip.c_str(), &si_other.sin_addr)==0) {
        fprintf(stderr, "inet_aton() failed\n");
    }
    
    printf("build udp 2 %s via port %d\n",ip.c_str(),port);
}


int mavlink_unreal::write(const char * s, int len)
{
    const char * buf = s;
    int slen=sizeof(si_other);
    if (sendto(socket_s, buf, len
               , 0 , (sockaddr *)&si_other, slen)==-1)
    {
        printf("failed:len %d\n",len);
        return -1;
    }
    
    return 0;
}

void mavlink_unreal::send()
{
    mavlink_attitude_quaternion_t att;
    mavlink_local_position_ned_t pos;
    mavlink_message_t msg;
    
    att.q1 = phys_body->_quat.w;
    att.q2 = phys_body->_quat.x;
    att.q3 = phys_body->_quat.y;
    att.q4 = phys_body->_quat.z;
    
    att.pitchspeed = phys_body-> pitch_rate;
    att.rollspeed = phys_body -> roll_rate;
    att.yawspeed = phys_body -> yaw_rate;
    
    pos.x = phys_body->pos.x;
    pos.y = phys_body->pos.y;
    pos.z = phys_body->pos.z;
    
    pos.vx = phys_body->vel.x;
    pos.vy = phys_body->vel.y;
    pos.vz = phys_body->vel.z;
    
    
    mavlink_msg_attitude_quaternion_encode(0,200,&msg, &att);
    send_msg(&msg);
    mavlink_msg_local_position_ned_encode(0, 200, &msg, &pos);
    send_msg(&msg);
    
}

int mavlink_unreal::send_msg(mavlink_message_t * msg)
{
    
    int len = mavlink_msg_to_send_buffer((uint8_t * )  buffer, msg);
    write(buffer, len);
    return 0;
}

mavlink_unreal::mavlink_unreal(std::string ip,int port, xmodel * bd)
{
    init_network(ip, port);
    this -> phys_body = bd;
}