#include "ros/ros.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include "goinghome_host_controller/infoRequest.h"
#define MAXINFO 500

std::vector<std::string> tokenize_getline(const std::string& data, const char delimiter = ' ')
{
	std::vector<std::string> result;
	std::string token;
	std::stringstream ss(data);

	while (getline(ss, token, delimiter))
    {
		result.push_back(token);
	}

	return result;
}
// src: https://psychoria.tistory.com/666

typedef struct location
{
    float px;
    float py;
    float ow;
} Location;

Location sector[20]; // 0 ~ 20
Location personList[MAXINFO];   // 0 ~ 499

bool infoRequest_location(goinghome_host_controller::infoRequest::Request &req, goinghome_host_controller::infoRequest::Response &res)
{
    int id = (int)req.id;
    ROS_INFO("received request for Location id: %d", id);
    res.px = sector[id].px;
    res.py = sector[id].py;
    res.ow = sector[id].ow;

    return true;
}

bool infoRequest_person(goinghome_host_controller::infoRequest::Request &req, goinghome_host_controller::infoRequest::Response &res)
{
    int id = (int)req.id;
    ROS_INFO("received request for Person id: %d", id);
    res.px = personList[id].px;
    res.py = personList[id].py;
    res.ow = personList[id].ow;

    return true;
}

int main(int argc, char **argv)
{
    // rosrun goinghome_host_controller file_server _sector:=/home/jetson/work/sector.txt _personal:=/home/jetson/work/person.txt
    ros::init(argc, argv, "file_server");

    if (argc != 3)
    {
        ROS_INFO("ARGUMENT REQUIREMENT: ARG0: sectorfile, ARG1: personfile");
        return 1;   
    }

    ros::NodeHandle nh;
    ros::ServiceServer location_Callback = nh.advertiseService("request_location_info", infoRequest_location);
    ros::ServiceServer person_Callback = nh.advertiseService("request_personal_info", infoRequest_person);
    std::string sector_path, personal_path;
    int sector_count = 0, person_count = 0;

    ROS_INFO("read: %s, %s", argv[1], argv[2]);

    std::ifstream sectorfile(argv[1]);
	if(sectorfile.is_open())
    {
		std::string line;
		while(getline(sectorfile, line))
        {
			std::cout << line << std::endl;
            sector_count++;
            std::vector<std::string> info = tokenize_getline(line, '/');
            int idx = std::atoi(info[0].c_str());
            sector[idx].px = std::stof(info[1].c_str());
            sector[idx].py = std::stof(info[2].c_str());
            sector[idx].ow = std::stof(info[3].c_str());
		}

		sectorfile.close();
	}

    std::ifstream personalfile(argv[2]);
	if(personalfile.is_open())
    {
		std::string line;
		while(getline(personalfile, line))
        {
			std::cout << line << std::endl;
            person_count++;
            std::vector<std::string> info = tokenize_getline(line, '/');
            int idx = std::atoi(info[0].c_str());
            personList[idx].px = std::stof(info[1].c_str());
            personList[idx].py = std::stof(info[2].c_str());
            personList[idx].ow = std::stof(info[3].c_str());
		}

		personalfile.close();
	}
    
    for (int i = 0; i < sector_count; i++)
    {
        ROS_INFO("Loaded %d sector: %lf %lf %lf", i, sector[i].px, sector[i].py, sector[i].ow);
    }

    for (int i = 0; i < person_count; i++)
    {
        ROS_INFO("Loaded %d personal: %lf %lf %lf", i, personList[i].px, personList[i].py, personList[i].ow);
    }

    ROS_INFO("Ready to serve File System!");
    ros::spin();

    return 0;
}