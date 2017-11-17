#include <sstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/NavSatFix.h"
#include "sensor_msgs/LaserScan.h"

#include "subpub_list.h"

using namespace std;
using namespace ros;


//***********   where need to change   ***********
int TotalControlQuad = 5;
// type the address where this file located in
string fileAddress = "/home/dasc/catkin_ws/src/uav_ros_controller/src";
//************************************************

bool is_empty(ifstream& pFile)
{
    return pFile.peek() == ifstream::traits_type::eof();
}


int main(int argc, char **argv)
{
  	std::cout <<"start"<< std::endl;

  	//declear all file address
  	string temp1  = fileAddress + "/data/datainput.txt";
    string temp2  = fileAddress + "/data/vel_input.txt";
    string temp3 = fileAddress + "/data/gps_output.txt";

    const char* datainput_address  = temp1.c_str();
    const char* vel_input_address  = temp2.c_str();
    const char* GPS_output_address = temp3.c_str();


    std::fstream DataInput;
    DataInput.open(datainput_address,ios::out); 
    cout << "DataInput file: " << DataInput <<endl;

    ros::init(argc, argv, "uav_controller");


    const int num_of_quads = 5;
    
    ros::NodeHandle n;
    geometry_msgs::Twist odom_msg[num_of_quads];

    ros::Publisher chatter_pub[num_of_quads];
    ros::Subscriber GPSsub[num_of_quads];  



    UAV_list uav_net;


    // UAV quad[num_of_quads];
    for (int i = 0; i<num_of_quads;i++)
    {
        chatter_pub[i] = n.advertise<geometry_msgs::Twist>(pub(i), 1);

        UAV t(i);
        uav_net.insert(t);
        GPSsub[i] = n.subscribe(sub(i), 1, &UAV::callback,&(uav_net.elts[i]));
    }


    ros::Rate loop_rate(10);

    int count = 0;

    ifstream vel_input(vel_input_address);
    cout << "vel_input file: " << vel_input <<endl;


    while (ros::ok())
    {
        if (!is_empty(vel_input))
        {

            string line;
            vector<double> vel_list;
            getline(vel_input, line);
            istringstream vel_ary(line);

            for (int i = 0; i < 3; i++)
            {
                double current_data;
                vel_ary >> current_data;
                vel_list.push_back(current_data);
            }

            for(int i = 0; i < num_of_quads; i++)
            {

                odom_msg[i].linear.x = vel_list[0];
                odom_msg[i].linear.y = vel_list[1];
                odom_msg[i].linear.z = vel_list[2];
                chatter_pub[i].publish(odom_msg[i]);
            }
  
        }

        FILE* fp_pos = fopen("gps_output.txt", "w");
        fclose(fp_pos);

        ofstream GPS_output(GPS_output_address);  
        // cout << "gps_output file: " << GPS_output <<endl;
        for(int i = 0; i < num_of_quads; i++)
        {
                GPS_output << uav_net.elts[i].latitude <<" "
                      << uav_net.elts[i].longitude <<" "
                            << uav_net.elts[i].altitude <<std::endl;
        }    
        ros::spinOnce();
        loop_rate.sleep();
        
    }


    return 0;
}
