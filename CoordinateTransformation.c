//  Created by Songwen Ding on 2017/6/23.
//  Copyright © 2017年 DingSoung. All rights reserved.

#include "CoordinateTransformation.h"
#include <math.h>

const double x_pi = 3.14159265358979324 * 3000.0 / 180.0;

void GCJ02toBD09(double *lat, double *lon) {
    double x = *lon, y = *lat;
    double z = sqrt(x * x + y * y) + 0.00002 * sin(y * x_pi);
    double theta = atan2(y, x) + 0.000003 * cos(x * x_pi);
    *lon = z * cos(theta) + 0.0065;
    *lat = z * sin(theta) + 0.006;
}

void BD09toGCJ02(double *lat, double *lon) {
    double x = *lon - 0.0065, y = *lat - 0.006;
    double z = sqrt(x * x + y * y) - 0.00002 * sin(y * x_pi);
    double theta = atan2(y, x) - 0.000003 * cos(x * x_pi);
    *lon = z * cos(theta);
    *lat = z * sin(theta);
}


const double pi = M_PI;
const double ee = 0.00669342162296594323;
const double a = 6378245.0;

double transformlat(double lat, double lng) {
    double ret = -100.0 + 2.0 * lat + 3.0 * lng + 0.2 * lng * lng + 0.1 * lat * lng + 0.2 * sqrt(fabs(lat));
    ret += (20.0 * sin(6.0 * lat * pi) + 20.0 * sin(2.0 * lat * pi)) * 2.0 / 3.0;
    ret += (20.0 * sin(lng * pi) + 40.0 * sin(lng / 3.0 * pi)) * 2.0 / 3.0;
    ret += (160.0 * sin(lng / 12.0 * pi) + 320 * sin(lng * pi / 30.0)) * 2.0 / 3.0;
    return ret;
}

double transformlng(double lat, double lng) {
    double ret = 300.0 + lat + 2.0 * lng + 0.1 * lat * lat + 0.1 * lat * lng + 0.1 * sqrt(fabs(lat));
    ret += (20.0 * sin(6.0 * lat * pi) + 20.0 * sin(2.0 * lat * pi)) * 2.0 / 3.0;
    ret += (20.0 * sin(lat * pi) + 40.0 * sin(lat / 3.0 * pi)) * 2.0 / 3.0;
    ret += (150.0 * sin(lat / 12.0 * pi) + 300.0 * sin(lat / 30.0 * pi)) * 2.0 / 3.0;
    return ret;
}

_Bool out_of_china(double lat, double lng) {
    if (lng < 72.004 || lng > 137.8347) {
        return 1;
    } else if (lat < 0.8293 || lat > 55.8271) {
        return 1;
    }
    return 0;
}

void WGS84toGCJ02(double *lat, double *lng) {
    if (out_of_china(*lat, *lng)) {
        return;
    }
    double dlat = transformlat(*lat - 35.0, *lng - 105.0);
    double dlng = transformlng(*lat - 35.0, *lng - 105.0);
    double radlat = *lat / 180.0 * pi;
    double magic = sin(radlat);
    magic = 1 - ee * magic * magic;
    double sqrtmagic = sqrt(magic);
    dlat = (dlat * 180.0) / ((a * (1 - ee)) / (magic * sqrtmagic) * pi);
    dlng = (dlng * 180.0) / (a / sqrtmagic * cos(radlat) * pi);
    *lat = *lat + dlat;
    *lng = *lng + dlng;
}

void GCJ02toWGS84(double *lat, double *lng) {
    if (out_of_china(*lat, *lng)) {
        return;
    }
    double dlat = transformlat(*lat - 35.0, *lng - 105.0);
    double dlng = transformlng(*lat - 35.0, *lng - 105.0);
    double radlat = *lat / 180.0 * pi;
    double magic = sin(radlat);
    magic = 1 - ee * magic * magic;
    double sqrtmagic = sqrt(magic);
    dlat = (dlat * 180.0) / ((a * (1 - ee)) / (magic * sqrtmagic) * pi);
    dlng = (dlng * 180.0) / (a / sqrtmagic * cos(radlat) * pi);
    *lat = *lat + dlat;
    *lng = *lng + dlng;
}

