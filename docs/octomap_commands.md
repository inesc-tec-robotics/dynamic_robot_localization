## Save 3D occupancy map
```
rosrun octomap_server octomap_saver ~/catkin_ws/src/dynamic_robot_localization_tests/maps/ship_interior/tridimensional/ship_interior_10mm_dynamic.bt
```

## Save 3D occupancy map with probability information
```
rosrun octomap_server octomap_saver -f ~/catkin_ws/src/dynamic_robot_localization_tests/maps/ship_interior/tridimensional/ship_interior_10mm_dynamic.ot
```

## Save 2D occupancy map 
```
rosrun map_server map_saver -f ~/catkin_ws/src/dynamic_robot_localization_tests/maps/ship_interior/planar/ship_interior_dynamic map:=projected_map
```
