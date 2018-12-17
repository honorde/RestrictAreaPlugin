#include<restricted_layer/restricted_layer.h>
#include <pluginlib/class_list_macros.h>
#include <rviz/visualization_manager.h>
#include <rviz/frame_manager.h>
#include "rviz/display_context.h"

PLUGINLIB_EXPORT_CLASS(restrict_area::RestrictedLayer, costmap_2d::Layer)


using costmap_2d::LETHAL_OBSTACLE;
using costmap_2d::NO_INFORMATION;

namespace restrict_area
{

RestrictedLayer::RestrictedLayer(){mbx=0;mby=0;mkx=0;mky=0;}

RestrictedLayer::~RestrictedLayer(){}


void RestrictedLayer::onInitialize()
{
  ros::NodeHandle nh("~/" + name_);
  default_value_ = NO_INFORMATION;
  matchSize();

  sub_ = nh.subscribe("/mouse_location", 1, &RestrictedLayer::Callback, this);
  sub2_ = nh.subscribe("/restrict_settings",1,&RestrictedLayer::setValue, this);

  dsrv_ = new dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig>(nh);
  dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig>::CallbackType cb = boost::bind(
      &RestrictedLayer::reconfigureCB, this, _1, _2);
  dsrv_->setCallback(cb);
}
void RestrictedLayer::setValue(const geometry_msgs::Point::ConstPtr& data)
{
  settings_.x = data->x; //Size
  settings_.y = data->y; //Clear
  settings_.z = data->z; //Color (NextRelease!!)
}
void RestrictedLayer::Callback(const geometry_msgs::Point::ConstPtr& world)
{
  createCircle(world->x, world->y, settings_.x, world->z);

}

void RestrictedLayer::matchSize()
{
  Costmap2D* master = layered_costmap_->getCostmap();
  resizeMap(master->getSizeInCellsX(), master->getSizeInCellsY(), master->getResolution(),
            master->getOriginX(), master->getOriginY());
}


void RestrictedLayer::reconfigureCB(costmap_2d::GenericPluginConfig &config, uint32_t level)
{
  enabled_ = config.enabled;
}


void RestrictedLayer::updateBounds(double robot_x, double robot_y, double robot_yaw, double* min_x,
                                           double* min_y, double* max_x, double* max_y)
{
  Costmap2D* master = layered_costmap_->getCostmap();

  *min_x = -(master->getSizeInCellsX()/(master->getResolution()));
  *min_y = -(master->getSizeInCellsY()/(master->getResolution()));
  *max_x = (master->getSizeInCellsX()/(master->getResolution()));
  *max_y = (master->getSizeInCellsY()/(master->getResolution()));
}

void RestrictedLayer::updateCosts(costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i,
                                          int max_j)
{
  if (!enabled_)
    return;

  for (int j = min_j; j < max_j; j++)
  {
    for (int i = min_i; i < max_i; i++)
    {
      int index = getIndex(i, j);
      if (costmap_[index] == NO_INFORMATION)
        continue;
      master_grid.setCost(i, j, costmap_[index]);
    }
  }
}

void RestrictedLayer::createCircle(double x_center,double y_center, int r, bool operation)
{
    Costmap2D* master = layered_costmap_->getCostmap();
    if (!settings_.y)
    {
        for (int i=0; i<r; i++)
        {
          for (int j=0; j<r; j++)
            {
              if(worldToMap((x_center+(i*master->getResolution())),(y_center+(master->getResolution()*j)),mx, my))
                 {
                  if (mbx<mx) mbx=mx;
                  if (mkx>mx) mkx=mx;
                  if (mby<my) mby=my;
                  if (mky>my) mky=my;

                  if(!operation)
                      setCost(mx,my,LETHAL_OBSTACLE);
                  else
                      setCost(mx,my,NO_INFORMATION);
                 }
            }
        }
   }
   else
   {
      for (int i=mkx; i<=mbx; i++)
      {
         for (int j=mky; j<=mby; j++)
           setCost(i,j,NO_INFORMATION);
      }
   }
}
} // end namespace
