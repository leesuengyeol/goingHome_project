#include "eventhandler.h"

// name: goinghome_host_eventhandler

int main(int argc, char **argv)
{
    ros::init(argc, argv, "main_control");
    // ros::NodeHandle nh;

    ROS_INFO("Hello World!\n");

    initialize_control();

    do
    {
        printf("command: ");
        char menu;
        bool isExit = false;
        std::cin >> menu;

        if (menu >= '1' && menu <= '4')
        {
            switch(menu)
            {
                case '1':
                    printf("Set destination and command service\n");
                    destination_menu();
                    break;

                case '2':
                    printf("Call robot: return to base\n");
                    gobase(0);
                    break;

                case '3':
                    printf("Surveilance mode\n");
                    goSurveilancemode();
                    break;

                case '4':
                    printf("Exit\n");
                    isExit = true;
                    break;
            }

            if (isExit)
                break;
        }
    }while(true);

    return 0;
}