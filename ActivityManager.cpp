#include "ActivityManager.h"

namespace activity{
void ActivityManager:: addActivity(std::unique_ptr<CourseActivity>activity){
    m_activities.push_back(std::move(activity));//that is a unique pointer we cant copy it
}
void ActivityManager:: listActivities(std::ostream&os )const{
    for(size_t i=0;i<m_activities.size();i++){
        os<<m_activities[i]->getTitle()<<'\n';
    }
}

CourseActivity* ActivityManager::findActivityByTitle(std::string_view title) {
    for (const auto& act : m_activities) {
        if (act->getTitle() == title) {
            return act.get();
        }
    }
    return nullptr;
}

}
