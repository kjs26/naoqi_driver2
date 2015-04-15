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

/**
* LOCAL includes
*/
#include "string.hpp"

/**
* BOOST includes
*/
#include <boost/foreach.hpp>
#define for_each BOOST_FOREACH

namespace alros
{
namespace converter
{

StringConverter::StringConverter(const std::string& name, const float& frequency, const qi::SessionPtr& session ):
    BaseConverter( name, frequency, session )
  {}

void StringConverter::reset()
{
}

void StringConverter::registerCallback( const message_actions::MessageAction action, Callback_t cb )
{
  callbacks_[action] = cb;
}

void StringConverter::callAll( const std::vector<message_actions::MessageAction>& actions )
{
  static std_msgs::String m;
  m.data = "test_string_data";

  for_each( const message_actions::MessageAction& action, actions )
  {
    callbacks_[action](m);
  }
}

} //publisher
} // alros
