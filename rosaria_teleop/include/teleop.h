#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

#include "termios.h"
#include "boost/thread/mutex.hpp"

#define KEYCODE_A 0x61
#define KEYCODE_D 0x64
#define KEYCODE_S 0x73
#define KEYCODE_W 0x77

#define KEYCODE_SPACE 0x20

class RosAriaTeleop
{
  public:
    RosAriaTeleop( struct termios &cooked, struct termios &raw, int &kfd );
    ~RosAriaTeleop();
    
  private:
    ros::NodeHandle n_;
    ros::Publisher cmd_vel_pub_;
    ros::Time first_publish_, last_publish_;

    geometry_msgs::Twist cmd_vel_msg_;

    double vel_x;
    double vel_omega;

    struct termios cooked_, raw_;
    int kfd_;

    boost::mutex publish_mutex_;

    void publish( double vel_x, double vel_omega );

  public:
     void spin();
     void watchdog();

};
