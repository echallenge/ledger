#pragma once
//------------------------------------------------------------------------------
//
//   Copyright 2018-2020 Fetch.AI Limited
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//
//------------------------------------------------------------------------------

#include <memory>
#include <string>
#include <vector>

namespace fetch {
namespace core {

/**
 * Interface class to represent
 */
class Runnable
{
public:
  // Construction / Destruction
  Runnable()          = default;
  virtual ~Runnable() = default;

  /// @name Runnable Interface
  /// @{
  virtual bool IsReadyToExecute() const
  {
    return true;
  }
  virtual void Execute() = 0;

  virtual std::string GetId() const = 0;

  virtual bool IsExpectedToBlock() const
  {
    return false;
  }

  virtual std::string GetDebug() const
  {
    return std::string("No debug info");
  };
  /// @}

  // Helper operators
  void operator()()
  {
    Execute();
  }
};

using WeakRunnables = std::vector<std::weak_ptr<Runnable>>;
using WeakRunnable  = std::weak_ptr<Runnable>;
using RunnablePtr   = std::shared_ptr<Runnable>;

}  // namespace core
}  // namespace fetch
