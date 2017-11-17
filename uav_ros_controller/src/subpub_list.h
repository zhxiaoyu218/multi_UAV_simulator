#include "geometry_msgs/Twist.h"
#include "sensor_msgs/NavSatFix.h"
#include "ros/ros.h"
using namespace std;

string pub(int i)
{
	stringstream ss;
	ss<<i;
	string PubChannel ="quad" + ss.str() +"/cmd_vel";
	return PubChannel;
}

string sub(int i)
{
	stringstream ss;
	ss<<i;
	string SubChannel ="quad" + ss.str() +"/fix";
	return SubChannel;
}


class UAV
{
	public:
		int ID;
        float longitude,latitude,altitude;

    UAV()
    {
    	ID = -1;
    }
    UAV(int index)
    {
    	ID = index;
    }
    void callback(const sensor_msgs::NavSatFix& msg)
    {
    	 longitude = msg.longitude;
    	  latitude = msg.latitude;
    	  altitude = msg.altitude;
	}
};


class UAV_list
{
	public:
	static const int ELTS_CAPACITY = 30;
	UAV elts[ELTS_CAPACITY]; 
	int size;

	UAV_list() {size=0;};

	void insert(UAV v)
	{
		assert(size < ELTS_CAPACITY); //REQUIRES!
		elts[size] = v;
		size++;
        ROS_INFO("quad %d inserted",v.ID);
	}
};





