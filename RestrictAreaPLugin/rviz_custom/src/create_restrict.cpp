#include "create_restrict.h"
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreEntity.h>
#include <ros/console.h>
#include <rviz/viewport_mouse_event.h>
#include <rviz/visualization_manager.h>
#include <rviz/mesh_loader.h>
#include <rviz/geometry.h>
#include <rviz/properties/vector_property.h>
#include "rviz/display_context.h"
#include "rviz/properties/int_property.h"
#include "rviz/properties/bool_property.h"
#include <pluginlib/class_list_macros.h>

PLUGINLIB_EXPORT_CLASS(rviz_custom::Restrict, rviz::Tool)

namespace rviz_custom {

Restrict::Restrict() {

    shortcut_key_ = 'g';

    Size_property_ = new rviz::IntProperty("Size", 5,"Size of drawing",
                                          getPropertyContainer(), SLOT(updateTopic()), this);

    Remove_all_ = new rviz::BoolProperty("Clear All", false, "State of Clear or Draw ",
                                         getPropertyContainer(), SLOT(updateTopic()), this);
}

Restrict::~Restrict() {}

void Restrict::updateTopic()
{
    settings_.x = Size_property_->getInt();
    settings_.y = Remove_all_->getBool(); //clear
    settings_.z = 1; //color
}

void Restrict::initialize()
{
    pub_ = n_.advertise<geometry_msgs::Point>("/mouse_location",1);
    pub2_ = n_.advertise<geometry_msgs::Point>("/restrict_settings",1);

}
void Restrict::activate()
{
    initialize();
    ROS_INFO("Initialize is starting!");
    operation_=false;
}

void Restrict::deactivate(){}

int Restrict::processMouseEvent(rviz::ViewportMouseEvent& event){
    int flag = 0;
    Ogre::Vector3 intersection;
    Ogre::Plane ground_plane( Ogre::Vector3::UNIT_Z, 0.0f );
    try
    {
        if( rviz::getPointOnPlaneFromWindowXY( event.viewport, ground_plane, event.x, event.y, intersection ))
            {
                point_.x = intersection.x;
                point_.y = intersection.y;
                point_.z = operation_;
                pub_.publish(point_);
                pub2_.publish(settings_);
            }
    }
    catch (int a)
       {
        ROS_ERROR("Error Occured!!");
        return 0;
       }

    if (event.rightUp())
        operation_=true;

    else if( event.leftDown() )
        flag |= Finished;

    return flag;
}
}//end namespace

