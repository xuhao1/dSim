#ifndef __base_heil_phys_H__
#define __base_heil_phys_H__

#include <math.h>

class base_heli_phys
{
public:
    float v = 0 ;
    float p = 0 ;
    float phi = 0 ;
    float b = 0 ;
    float d = 0 ;
    float u = 0 ;
    float q = 0 ;
    float theta = 0 ;
    float a = 0 ;
    float c = 0 ;
    float Olon = 0 ;
    float Olat = 0 ;
    float T = 0 ;
    float Omega = 0 ;
    float h = 0.2481 ;
    float kb = 23.4 ;
    float Ixx = 0.2882 ;
    float Iyy = 0.6833 ;
    float gb = 0.276249 ;
    float Ibetab = 0.2818 ;
    float Rb = 0.78 ;
    float rb = 0.15 ;
    float cb = 0.06 ;
    float Cab = 3.12 ;
    float Dv = 1.723 ;
    float Du = 1.516 ;
    float Kl3 = 1.0848 ;
    float Kl1 = 0.4684 ;
    float Kl2 = 2.2727 ;
    float g = 9.8 ;
    float m = 6.89 ;
    float rho = 1.125 ;
    float dv = 0 ;
    float dp = 0 ;
    float dphi = 0 ;
    float db = 0 ;
    float dd = 0 ;
    float du = 0 ;
    float dq = 0 ;
    float dtheta = 0 ;
    float da = 0 ;
    float dc = 0 ;

void iter_equs(float dt) {

//\brief:make iteration for vector{v, p, phi, b, d}
dv = b*g + g*phi - (Dv*v)/m+0;
dp = (b*(kb + h*T))/Ixx+0;
dphi = p+0;
db = -(b*gb*Omega)/16. + (d*gb*Kl3*Omega)/16. - p+(gb*Kl1*Olon*Omega)/16.;
dd = -(d*gb*Omega)/16. - p+(gb*Kl2*Olon*Omega)/16.;
    v += dv* dt;
    p += dp* dt;
    phi += dphi* dt;
    b += db* dt;
    d += dd* dt;

//\brief:make iteration for vector{u, q, theta, a, c}
du = -(a*g) - g*theta - (Du*u)/m+0;
dq = (a*(kb + h*T))/Iyy+0;
dtheta = q+0;
da = -(a*gb*Omega)/16. + (c*gb*Kl3*Omega)/16. - q+(gb*Kl1*Olat*Omega)/16.;
dc = -(c*gb*Omega)/16. - q+(gb*Kl2*Olat*Omega)/16.;
    u += du* dt;
    q += dq* dt;
    theta += dtheta* dt;
    a += da* dt;
    c += dc* dt;


}
};
#endif