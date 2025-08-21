#ifndef ACTIVITYMANAGER_H
#define ACTIVITYMANAGER_H
#include <memory>
#include <vector>
#include <string_view>
#include <iostream>
#include <functional>
#include "CourseActivity.h"
namespace activity{

class ActivityManager{
    std::vector<std::unique_ptr<CourseActivity>>m_activities;    
public:
    //as we see here we can add activities and list them and findtem with title with this class which takes the resposnisiblity
    //for doing the activity responsibilities later i will use also ungradable activities here
    void addActivity(std::unique_ptr<CourseActivity>activity);
    void listActivities(std::ostream&os = std::cout)const;
    CourseActivity* findActivityByTitle(std::string_view title);
};




}


#endif // ACTIVITYMANAGER_H
