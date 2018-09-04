#pragma once
//------------------------------------------------------------------------------
//
//   Copyright 2018 Fetch.AI Limited
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

#include "core/assert.hpp"
#include "math/shape_less_array.hpp"
#include "vectorise/memory/range.hpp"

#include <cmath>

namespace fetch {
namespace math {
namespace correlation {

template <typename T, std::size_t S = memory::VectorSlice<T>::E_TYPE_SIZE>
inline typename memory::VectorSlice<T, S>::type Eisen(memory::VectorSlice<T, S> const &a,
                                                      memory::VectorSlice<T, S> const &b)
{
  detailed_assert(a.size() == b.size());
  using vector_register_type = typename memory::VectorSlice<T, S>::vector_register_type;
  using type                 = typename memory::VectorSlice<T, S>::type;

  type innerA = a.in_parallel().SumReduce(memory::TrivialRange(0, a.size()),
                                          [](vector_register_type const &x) { return x * x; });

  type innerB = b.in_parallel().SumReduce(memory::TrivialRange(0, b.size()),
                                          [](vector_register_type const &x) { return x * x; });

  type top = a.in_parallel().SumReduce(
      memory::TrivialRange(0, a.size()),
      [](vector_register_type const &x, vector_register_type const &y) { return x * y; }, b);

  type denom = type(sqrt(innerA * innerB));

  if (top < 0)
  {
    top = -top;
  }
  return type(top / denom);
}

template <typename T, typename C>
inline typename ShapeLessArray<T, C>::type Eisen(ShapeLessArray<T, C> const &a,
                                                 ShapeLessArray<T, C> const &b)
{
  return Eisen(a.data(), b.data());
}

}  // namespace correlation
}  // namespace math
}  // namespace fetch
