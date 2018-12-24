# INFORMATION
This package provides a software to create new layer for a custom restricted. New layer doesn't effect localization and other layers. `clear_costmap` which can remove obstacle layer, can't remove new layer.

# USAGE
The new layer is requires to add `global_costmap_params.yaml` on your package. Plugin tab in `global_costmap_params.yaml` must be as a following. Second line calls new layer that's called `restricted_layer`.

      plugins:
         - {name: static_layer, type: "costmap_2d::StaticLayer"}
         - {name: restricted_layer, type: "restrict_area::RestrictedLayer"}
         - {name: obstacle_layer, type: "costmap_2d::ObstacleLayer"}
         - {name: inflation_layer, type: "costmap_2d::InflationLayer"}
     
If you starts by using commands of `rviz rosrun rviz rviz` or `rviz` you can see CreateRestrict tool on    rviz tool panel. If you don't see you can add CreateRestrict tool by using add a new tool on rviz tool panel.
According that tell only you can see CreateRestrict plugin rviz and you don't create restrict. For this, you have to starting your slam package. After you started SLAM package, you must click CreateRestrict tool on panel. Left click is using for draw restrict area, and right click remove. Also you can configure drawing size and clear whole map. You can use by rviz tool property panel. 

This project illustrated as a following video:
https://www.youtube.com/watch?v=dJn96LBu2l4
