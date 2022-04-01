#pragma once
#define BASE_HGT_A 	8.11//8.625      //base height   
#define HUMERUS_A 	7.48//7.375      //shoulder-to-elbow "bone" 
#define ULNA_A		8.66//8.625      //elbow-to-wrist "bone" 
#define GRIPPER_A		5.51//6           //gripper

#define PI 3.14159265358979323846

double to_radians(double degrees);
double to_degrees(double radians);
kin_f to_angle(double x, double y, double z, double grip_angle);
kin_i to_cart(double base_angle, double shld_angle, double elb_angle, double wri_angle);
void circle_yz_plane(void);