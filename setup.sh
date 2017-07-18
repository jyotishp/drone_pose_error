cd src
git clone https://github.com/AutonomyLab/bebop_autonomy -b indigo-devel
cd bebop_autonomy
git reset --hard adc1afe7c4f037caf62458a0bcfee4dc5c07ddaa
rosdep install --from-paths --ignore-src
cd ..
git clone https://github.com/RIVeR-Lab/apriltags_ros -b indigo-devel
cd apriltags_ros
rosdep install --from-paths --ignore-src
cd ../..
catkin_make
