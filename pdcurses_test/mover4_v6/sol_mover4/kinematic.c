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

static	kin_f	angles;

double to_radians(double degrees) {//converts angles from degrees to radians
	double radian;
	radian = degrees * (PI / 180.0);
	return radian;
}

double to_degrees(double radians) {//converts angles from radians to degrees .
	double degree;
	degree = radians * (180.0 / PI);
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

	base_angle = to_degrees(atan2(y, x));

	r = sqrt(pow(x, 2) + pow(y, 2));

	grip_off_z = -1 * sin(to_radians(grip_angle)) * GRIPPER;
	grip_off_r = cos(to_radians(grip_angle)) * GRIPPER;

	z_ = (z - grip_off_z) - BASE_HGT;
	r_ = r - grip_off_r;

	twoH = sqrt(pow(z_, 2) + pow(r_, 2));

	a1 = to_degrees(atan2(z_, r_));
	a2 = to_degrees(acos((pow(HUMERUS, 2) - pow(ULNA, 2) + pow(twoH, 2)) / (2 * HUMERUS * twoH)));
	
	shld_angle_ = a1 + a2;
	elb_angle_ = to_degrees(acos((pow(HUMERUS, 2) + pow(ULNA, 2) - pow(twoH, 2)) / (2 * HUMERUS * ULNA)));
	wri_angle_ = 360 - grip_angle - elb_angle_ - shld_angle_;

	shld_angle_ = 90 - shld_angle_;
	elb_angle_ = 180 - elb_angle_;
	wri_angle_ = 180 - wri_angle_;

	angles.data[0] = base_angle;
	angles.data[1] = shld_angle_;
	angles.data[2] = elb_angle_;
	angles.data[3] = wri_angle_;

	return angles;
}






//kin_i to_cart(double base_angle, double shld_angle, double elb_angle, double wri_angle) {//converts from angles to x - y - z(forward kinematics).The angles parameters are : base_angle, shld_angle’, elb_angle’and wri_angle’
//
//	static	kin_i	cart;
//
//
//	double z, r, z_, r_;
//	double x, y;
//
//	r = HUMERUS * cos(to_radians(90 - wri_angle - shld_angle)) + ULNA * cos(to_radians(90 - shld_angle - elb_angle)) + GRIPPER * cos(to_radians(90 - wri_angle - shld_angle - elb_angle - wri_angle));
//	z_ = HUMERUS * sin(to_radians(90 - shld_angle)) + ULNA * sin(to_radians(90 - shld_angle - elb_angle));
//	z = z_ + GRIPPER * sin(to_radians(90 - shld_angle - elb_angle - wri_angle)) + BASE_HGT;
//	y = r * sin(to_radians(base_angle));
//	x = r * cos(to_radians(base_angle));
//
//	cart.data[0] = x;
//	cart.data[1] = y;
//	cart.data[2] = z;
//
//
//	return cart;
//}



void circle_yz_plane(void) {

	kin_f angles;

	double r, z_, r_;
	double grip_off_z, grip_off_r;
	double twoH;
	double a1, a2;
	double shld_angle, elb_angle, wri_angle, base_angle;
	double shld_angle_, elb_angle_, wri_angle_, base_angle_;
	double test;
	double y, z;

the while loop belongs to the thread. Don't implement it here!
	
	while (1) {





		for (double ang45 = 0; ang45 <= to_radians(315); ang45 = +45) {

					/* Sets x,y,z angles and grip angle. */
		  	//        z_ = HUMERUS * sin(to_radians(angles.data[1]) + ULNA * sin(angles.data[1] - angles.data[2]));
					//z = z_ + OFFSET_Z + BASE_HGT;
					z = (RADIUS * cos(to_radians(ang45))) + OFFSET_Y;
					y = (RADIUS * sin(to_radians(ang45))) + OFFSET_Y;

					angles = to_angle(X0, y, z, to_radians(ang45));
					move_until(angles.data[0], angles.data[1], angles.data[2], angles.data[3]);
					delay_ms(100);

					

				

					//angles = to_angle(X0, OFFSET_Y, OFFSET_Z, 45);
					//move_until(angles.data[0], angles.data[1], angles.data[2], angles.data[3]);

					//angles = to_angle(X0, OFFSET_Y, OFFSET_Z, 90);
					//move_until(angles.data[0], angles.data[1], angles.data[2], angles.data[3]);

					//angles = to_angle(X0, OFFSET_Y, OFFSET_Z, 135);
					//move_until(angles.data[0], angles.data[1], angles.data[2], angles.data[3]);

					//angles = to_angle(X0, OFFSET_Y, OFFSET_Z, 180);
					//move_until(angles.data[0], angles.data[1], angles.data[2], angles.data[3]);

					//angles = to_angle(X0, OFFSET_Y, OFFSET_Z, 225);
					//move_until(angles.data[0], angles.data[1], angles.data[2], angles.data[3]);

					//angles = to_angle(X0, OFFSET_Y, OFFSET_Z, 270);
					//move_until(angles.data[0], angles.data[1], angles.data[2], angles.data[3]);

					//angles = to_angle(X0, OFFSET_Y, OFFSET_Z, 315);
					//move_until(angles.data[0], angles.data[1], angles.data[2], angles.data[3]);

	}
	
	}





}
