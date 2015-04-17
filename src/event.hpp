/*
 * Copyright 2015 Aldebaran
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef EVENT_REGISTER_HPP
#define EVENT_REGISTER_HPP

#include <string>

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include <qi/session.hpp>

#include <ros/ros.h>

#include <alrosbridge/tools.hpp>
#include <alrosbridge/recorder/globalrecorder.hpp>

namespace alros
{

/**
* @brief GlobalRecorder concept interface
* @note this defines an private concept struct,
* which each instance has to implement
* @note a type erasure pattern in implemented here to avoid strict inheritance,
* thus each possible publisher instance has to implement the virtual functions mentioned in the concept
*/
template <typename Converter, typename Publisher, typename Recorder>
class EventRegister
{

public:

  /**
  * @brief Constructor for recorder interface
  */
  EventRegister();
  EventRegister( const std::string& key, const qi::SessionPtr& session );
  ~EventRegister();

  void reset( ros::NodeHandle& nh, boost::shared_ptr<alros::recorder::GlobalRecorder> gr );

  void startProcess();
  void stopProcess();

  void isRecording(bool state);
  void isPublishing(bool state);

private:
  void registerCallback();
  void unregisterCallback();
  void onEvent();

private:
  boost::shared_ptr<Converter> converter_;
  boost::shared_ptr<Publisher> publisher_;
  boost::shared_ptr<Recorder> recorder_;

  qi::AnyObject p_memory_;
  qi::AnyObject signal_;
  qi::SignalLink signalID_;
  std::string key_;

  bool isLooping_;
  bool isPublishing_;
  bool isRecording_;

}; // class globalrecorder
} //alros
#include "event.hxx"

#endif
