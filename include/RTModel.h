/**************************************************
A model is a geometry with material.
*****************************************************/
#include "RTGeometry.h"
#include "Material.h"

#ifndef __RTMODEL_H__
#define __RTMODEL_H__

struct RTModel {
    RTGeometry* RTgeometry;
    Material* material;
};

#endif 
