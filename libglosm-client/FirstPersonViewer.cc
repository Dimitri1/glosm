/*
 * Copyright (C) 2010-2012 Dmitry Marakasov
 *
 * This file is part of glosm.
 *
 * glosm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * glosm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with glosm.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <glosm/FirstPersonViewer.hh>

#include <glosm/Math.hh>
#include <glosm/Projection.hh>
#include <glosm/HeightmapDatasource.hh>
#include <glosm/geomath.h>



#include "mglu.h"
#include "glosm/util/gl.h"
#include <stdio.h>
#include "mglu.h"






FirstPersonViewer::FirstPersonViewer(): heightmap_(NULL), pos_(), landscape_height_(0), yaw_(0), pitch_(0), fov_(90.0), aspect_(1.0) {
}

FirstPersonViewer::FirstPersonViewer(const Vector3i& pos): heightmap_(NULL), pos_(pos), landscape_height_(0), yaw_(0), pitch_(0), fov_(90.0), aspect_(1.0) {
}


/*DIMITRI :  Modification de la valeur initiale de landscape_heigh*/
FirstPersonViewer::FirstPersonViewer(const Vector3i& pos, float yaw, float pitch): heightmap_(NULL), pos_(pos), landscape_height_(0), yaw_(yaw), pitch_(pitch), fov_(90.0), aspect_(1.0) {

}
//FirstPersonViewer::FirstPersonViewer(const Vector3i& pos, float yaw, float pitch): heightmap_(NULL), pos_(pos), landscape_height_//(0), yaw_(yaw), pitch_(pitch), fov_(90.0), aspect_(1.0) {
//}

void FirstPersonViewer::SetupViewerMatrix(const Projection& projection) const {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* length of a meter in local units */
	float meterlen = projection.Project(pos_.Flattened() + Vector3i(0, 0, GEOM_UNITSINMETER), pos_.Flattened()).z;



	//fprintf(stderr,"1metre : %f\n",(float)meterlen) ;
	//fprintf(stderr,"1metre autre : %f\n",(float)GEOM_UNITSINMETER) ;
	 	
	/* viewer height in meters */
	float height = pos_.z / (float)GEOM_UNITSINMETER;
	if (height < 100.0f)
		height = 100.0f;

	/* viewing distances is [1meter..100km] at under 100m height
	 * and increases linearly with going higher */
	
	float znear = 0.01f  *  height * meterlen;

	//float znear = 0.0001f  * meterlen;
	
	float zfar = 1000.0f  *  height * meterlen;

	mgluPerspective(fov_ / M_PI * 180.0f, aspect_, znear, zfar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Vector3f dir = GetDirection();
	Vector3f up = Vector3f(0.0f, 0.0f,1.0f);

	
/*DIMITRI : Les trois premiers arguments Fixent la limite de la camera*/

	   mgluLookAt(0.0f, 0.0f, 0.0f, dir.x, dir.y, dir.z, up.x, up.y, up.z );

}

Vector3i FirstPersonViewer::GetPos(const Projection& /* unused*/) const {
	return pos_;
}

void FirstPersonViewer::SetFov(float fov) {
	fov_ = fov;
}

void FirstPersonViewer::SetAspect(float aspect) {
	aspect_ = aspect;
}

Vector3f FirstPersonViewer::GetDirection() const {
	return Vector3f::FromYawPitch(yaw_, pitch_);
}

void FirstPersonViewer::SetPos(Vector3i pos) {
	pos_ = pos;
	FixPosition();
}

//void FirstPersonViewer::Move(int flags, float speed, float time, GPXWriter *g) {
void FirstPersonViewer::Move(int flags, float speed, float time) {

	/* 1 meter direction-collinear vector in OSM coordinate space */






	Vector3f dirbasis = Vector3f(
			GEOM_LONSPAN / WGS84_EARTH_EQ_LENGTH / cos(pos_.y * GEOM_DEG_TO_RAD),
			GEOM_LONSPAN / WGS84_EARTH_EQ_LENGTH,
			GEOM_UNITSINMETER
		);

	Vector3f dir = GetDirection();
	Vector3f worldup = Vector3f(0.0f, 0.0f, 1.0f);
	Vector3f right = dir.CrossProduct(worldup).Normalized();
	Vector3f relup = right.CrossProduct(dir).Normalized();
    



   //DIMITRI: Test GPX writer 
   //fprintf(stderr,"Coord : X : %.1f, Y : %.1f \n",pos_.x/100,pos_.y/100) ;
   // if (writemode == true )			
   //		g.WritePoint((float)pos_.x,(float)pos_.y) ; 	
	//g.Init() ; 


/*DIMITRI : C'est ici qu'on doit implémenter l'appel au code de contrôle du Player de Maxim 
	    :: Au lieu de modifier dirrectement mouvement flags, on va agir sur les commander du 
	       Player de Maxim . 		
*/

//	void incrAccel();
//	void decrAccel();
//	void goLeft();
//	void goRight();

	if (flags & FORWARD)
		pos_ += dirbasis * dir * speed * time;
	if (flags & BACKWARD)
		pos_ -= dirbasis * dir * speed * time;
	if (flags & LEFT)
		pos_ -= dirbasis * right * speed * time;
	if (flags & RIGHT)
		pos_ += dirbasis * right * speed * time;
	if (flags & UP)
		pos_ += dirbasis * relup * speed * time;
	if (flags & DOWN)
		pos_ -= dirbasis * relup * speed * time;
	if (flags & HIGHER)
		pos_ += dirbasis * worldup * speed * time;
	if (flags & LOWER)
		pos_ -= dirbasis * worldup * speed * time;



	        FixPosition();
}

void FirstPersonViewer::FixPosition() {
	/* Update landscape height */
	if (heightmap_)
		landscape_height_ = heightmap_->GetHeight(Vector2d(pos_.x, pos_.y));

	/* Wrap around */
	if (pos_.x > GEOM_MAXLON)
		pos_.x -= GEOM_LONSPAN;
	if (pos_.x < GEOM_MINLON)
		pos_.x += GEOM_LONSPAN;

	/* Limit poles */
	if (pos_.y > GEOM_MERCATOR_MAXLAT)
		pos_.y = GEOM_MERCATOR_MAXLAT;
	if (pos_.y < GEOM_MERCATOR_MINLAT)
		pos_.y = GEOM_MERCATOR_MINLAT;

	/* Limit height */
	if (pos_.z < landscape_height_ + 1)
		pos_.z = landscape_height_ + 1;
	if (pos_.z > std::numeric_limits<osmint_t>::max())
		pos_.z = std::numeric_limits<osmint_t>::max();
}

void FirstPersonViewer::FixRotation() {
	static const float PitchLimit = M_PI/2.0*0.9;

	if (pitch_ > PitchLimit)
		pitch_ = PitchLimit;
	if (pitch_ < -PitchLimit)
		pitch_ = -PitchLimit;
	if (yaw_ > M_PI)
		yaw_ -= M_PI*2.0;
	if (yaw_ < -M_PI)
		yaw_ += M_PI*2.0;
}

void FirstPersonViewer::SetRotation(float yaw, float pitch) {
	yaw_ = yaw;
	pitch_ = pitch;

	FixRotation();
}

void FirstPersonViewer::Rotate(float yawspeed, float pitchspeed, float time) {
	yaw_ += yawspeed * time;
	pitch_ += pitchspeed * time;

	FixRotation();
}

float FirstPersonViewer::GetYaw() const {
	return yaw_;
}

float FirstPersonViewer::GetPitch() const {
	return pitch_;
}

float FirstPersonViewer::GetFov() const {
	return fov_;
}

float FirstPersonViewer::GetAspect() const {
	return aspect_;
}

Vector3d& FirstPersonViewer::MutablePos() {
	return pos_;
}

void FirstPersonViewer::SetHeightmapDatasource(const HeightmapDatasource* heightmap) {
	heightmap_ = heightmap;
}
