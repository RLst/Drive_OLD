#pragma once

#define PI 3.1415926535897932384626433832795f
#define GRAVITY 9.81302f;
//#define RHO 1.225f;

const float RHO = 1.225f;

const float GravityMtEverest = 9.77015f;
const float GravityMelbourne = 9.81302f;
const float GravityBrisbane = 9.79695f;
const float GravityHouston = 9.79998f;
const float GravityVietnam = 9.78055f;
const float GravityPeru = 9.76835f;

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}