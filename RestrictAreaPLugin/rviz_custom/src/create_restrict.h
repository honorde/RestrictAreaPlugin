#include "ros/ros.h"
#include <rviz/tool.h>
#include <geometry_msgs/Point.h>
namespace Ogre
{
	class SceneNode;
	class Vector3;
}

namespace rviz
{
	class VectorProperty;
	class VisualizationManager;
	class ViewportMouseEvent;
	class IntProperty;
	class BoolProperty;
}

namespace rviz_custom
{
class Restrict: public rviz::Tool
{
Q_OBJECT
	
public:
	Restrict();
	virtual ~Restrict();

	virtual void initialize();
	virtual int processMouseEvent(rviz::ViewportMouseEvent& event);
	virtual void activate();
	virtual void deactivate();

public Q_SLOTS:
virtual void updateTopic();

private:

	ros::NodeHandle n_;
	ros::Publisher pub_;
	ros::Publisher pub2_;
	geometry_msgs::Point point_;
	geometry_msgs::Point settings_;
	bool operation_;
	rviz::IntProperty* Size_property_;
	rviz::BoolProperty* Remove_all_;
};

}//end_namespace



