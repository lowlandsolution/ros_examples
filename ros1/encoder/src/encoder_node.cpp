#include <ros/ros.h>

#include <encoder_msgs/EncoderFeedback.h>

int main(int argc, char** argv, char** envp)
{
    ros::init(argc, argv, "encoder");

    ros::NodeHandle nh;
    ros::NodeHandle pn("~");

    int cycle_rate;

    pn.param<int>("cycle_rate", cycle_rate, 1);

    ros::Publisher encoder_pub =
        nh.advertise<encoder_msgs::EncoderFeedback>("encoder_feedback", 1);

    unsigned int ticks = 0;
    unsigned int maxTicks = 4096;

    ros::Rate cycle(cycle_rate);
    while (ros::ok()) {
        // Publish linearly increasing encoder feedback
        encoder_msgs::EncoderFeedback msg;
        ticks = (ticks + 1) % maxTicks;
        msg.ticks = ticks;
        msg.angle = ticks * 2 * M_PI / maxTicks;
        encoder_pub.publish(msg); 
        cycle.sleep();
    }
}
