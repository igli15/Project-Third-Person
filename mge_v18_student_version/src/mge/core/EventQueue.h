//
// Created by Igli milaqi on 13/12/2018.
//

#ifndef LUAASSIGNMENT_EVENTQUEUE_H
#define LUAASSIGNMENT_EVENTQUEUE_H


#include <vector>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <iostream>
#include <unordered_map>
#include "EventType.h"
#include <functional>

    class EventQueue {

    private:

        std::vector<EventType *> m_eventTypes;
        std::map< std::type_index, std::vector<std::function<void(EventType*)>> *> m_eventMap;

    public:
        void HandleEvents();
        void QueueEventType(EventType* eventType)
		{
            m_eventTypes.push_back(eventType);
        }

        /** Register events is used once to register a handler(function) To a specific Event Type
         * @tparam T EventType
         * @param functionToAdd functionHandler
         */
        template<typename T>
        void RegisterEvent(const std::function<void(EventType*)> &functionToAdd)
        {
            auto it = m_eventMap.find(std::type_index(typeid(T)));

            if (it != m_eventMap.end())
            {
                it->second->push_back(functionToAdd);
            } else
                {
                auto vec = new std::vector<std::function<void(EventType*)>>();
                vec->push_back(functionToAdd);
                m_eventMap[std::type_index(typeid(T))] = vec;
            }

        }
    };


#endif //LUAASSIGNMENT_EVENTQUEUE_H
