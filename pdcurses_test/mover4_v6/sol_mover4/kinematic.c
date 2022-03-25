#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <ncurses.h>
#include <sys/ioctl.h>
//#include <sys/time.h>
//#include <libgen.h>
#endif
#include "../header/can.h"
#include "../header/task_controller.h"
#include "../header/ncurses_init.h"
#include "../header/kinematic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <stdint.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include "../header/public.h"
#include <math.h>
#ifdef _WIN32
#define HAVE_STRUCT_TIMESPEC  // for win32 only. Because TIMESPEC is re-defined inside pthread.h
#endif
#include <pthread.h>





// (radian/pi)=(degree/180)

static	kin_f	angles;
static	kin_i	cart;

double to_radians(double degrees);
double to_degrees(double radians);
kin_f to_angle(double x, double y, double z, double grip_angle);
kin_i to_cart(double base_angle, double shld_angle, double elb_angle, double wri_angle);



double to_radians(double degrees) {//converts angles from degrees to radians
	double radian;
	radian = degrees * (PI / 180);
	return radian;
}

double to_degrees(double radians) {//converts angles from radians to degrees .
	double degree;
	degree =  radians * (180 / PI);
	return degree;
}

kin_f to_angle(double x, double y, double z, double grip_angle) {//converts from  x - y - z - grip_angle to angles(inverse kinematics).The returned angles are : base_angle, shld_angle’, elb_angle’and wri_angle’
	
	double r, z_, r_;
	double grip_off_z, grip_off_r;
	double twoH;
	double a1, a2;
	double shld_angle, elb_angle, wri_angle, base_angle;
	double shld_angle_, elb_angle_, wri_angle_, base_angle_;
	double test;

	test = - sin(to_radians(grip_angle));
	grip_off_z = to_degrees(-sin(grip_angle)) * GRIPPER;
	grip_off_r = cos(to_radians(grip_angle)) * GRIPPER;

	r = sqrt(pow(x,2)+pow(y,2));

	z_ = (z - grip_off_z) - BASE_HGT;
	r_ = r - grip_off_r;

	twoH = sqrt(pow(z_, 2) + pow(r_, 2));
	
	
	a1 = to_degrees(atan2(z_ , r_));
	a2 = acos(to_radians((pow(HUMERUS,2) -pow(ULNA,2) + pow(twoH,2)) / (2 * HUMERUS *twoH)));

	shld_angle = a1 + a2;
	elb_angle = acos(to_radians((pow(HUMERUS, 2) - pow(ULNA, 2) - pow(twoH, 2)) / (2 * HUMERUS * ULNA)));
	wri_angle = 360 - grip_angle - elb_angle - shld_angle;
	base_angle = to_degrees(atan2(y, x));

	//Angle corrections

	shld_angle_ = 90 - shld_angle;
	elb_angle_ = 180 - elb_angle;
	wri_angle_ = 180 - wri_angle;

	angles.data[0] = base_angle;
	angles.data[1] = shld_angle_;
	angles.data[2] = elb_angle_;
	angles.data[3] = wri_angle_;


	return angles;
}
 
kin_i to_cart(double base_angle, double shld_angle, double elb_angle, double wri_angle) {//converts from angles to x - y - z(forward kinematics).The angles parameters are : base_angle, shld_angle’, elb_angle’and wri_angle’
	
	double z, r, z_, r_;
	double x, y;
	
	r = HUMERUS * to_degrees(cos(wri_angle - shld_angle) + ULNA * cos(wri_angle - shld_angle - elb_angle) + GRIPPER * cos(wri_angle - shld_angle - elb_angle - wri_angle));
	z_ = HUMERUS * to_degrees(cos(wri_angle - shld_angle) + ULNA * cos(wri_angle - shld_angle - elb_angle));
	z = z_ + GRIPPER * to_degrees(cos(wri_angle - shld_angle - elb_angle - wri_angle));
	y = r * to_degrees(sin(base_angle));
	x = r * to_degrees(cos(base_angle));

	cart.data[0] = x;
	cart.data[1] = y;
	cart.data[2] = z;


	return cart;

}
