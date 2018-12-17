#ifndef GRID_LAYER_H_
#define GRID_LAYER_H_
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#include <costmap_2d/layer.h>
#include <costmap_2d/layered_costmap.h>
#include <costmap_2d/GenericPluginConfig.h>
#include <dynamic_reconfigure/server.h>

#endif
namespace rviz
{
	class DisplayContext;
	class IntProperty;
	class BoolProperty;
}

namespace restrict_area
{

class RestrictedLayer : public costmap_2d::Layer, public costmap_2d::Costmap2D
{

public:
	RestrictedLayer();
	virtual ~RestrictedLayer();

	virtual void onInitialize();
	virtual void updateBounds(double robot_x, double robot_y, double robot_yaw, double* min_x, double* min_y, double* max_x,
		             double* max_y);
	virtual void matchSize();	
	void Callback(const geometry_msgs::Point::ConstPtr& world);
	void updateCosts(costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i, int max_j);
	
	void createCircle(double x_center, double y_center, int r, bool operation);
	void setValue(const geometry_msgs::Point::ConstPtr& data);

private:
	geometry_msgs::Point settings_;
	void reconfigureCB(costmap_2d::GenericPluginConfig &config, uint32_t level);
	dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig> *dsrv_;
	unsigned int mx;
	unsigned int my;
	unsigned int mbx;
	unsigned int mkx;
	unsigned int mby;
	unsigned int mky;
protected:
	ros::Subscriber sub_;
	ros::Subscriber sub2_;
};
}
#endif

