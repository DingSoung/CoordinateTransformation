//  Created by Songwen Ding on 2017/6/23.
//  Copyright © 2017年 DingSoung. All rights reserved.

#ifndef CoordinateTransformation_h
#define CoordinateTransformation_h

#include <stdio.h>

void GCJ02toBD09(double *lat, double *lon);
void BD09toGCJ02(double *lat, double *lon);

void WGS84toGCJ02(double *lng, double *lat);
void GCJ02toWGS84(double *lng, double *lat);
#endif
