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

#include <cstdint>
#include <functional>
#include <string>

namespace fetch {
namespace vm {

struct Token
{
  enum class Kind : uint16_t
  {
    EndOfInput = 0,
    Integer32,
    UnsignedInteger32,
    Integer64,
    UnsignedInteger64,
    SinglePrecisionNumber,
    DoublePrecisionNumber,
    String,
    BadString,
    True,
    False,
    Null,
    Function,
    EndFunction,
    While,
    EndWhile,
    For,
    In,
    EndFor,
    If,
    ElseIf,
    Else,
    EndIf,
    Var,
    Return,
    Break,
    Continue,
    Identifier,
    Comma,
    Dot,
    Colon,
    SemiColon,
    LeftRoundBracket,
    RightRoundBracket,
    LeftSquareBracket,
    RightSquareBracket,
    Plus,
    Minus,
    Multiply,
    Divide,
    AddAssign,
    SubtractAssign,
    MultiplyAssign,
    DivideAssign,
    Assign,
    Equal,
    NotEqual,
    LessThan,
    LessThanOrEqual,
    GreaterThan,
    GreaterThanOrEqual,
    And,
    Or,
    Not,
    Inc,
    Dec,
    Unknown
  };
  class Hasher
  {
  public:
    size_t operator()(const Kind &key) const
    {
      return std::hash<uint16_t>{}((uint16_t)key);
    }
  };
  Kind        kind;
  uint32_t    offset;
  uint16_t    line;
  uint16_t    length;
  std::string text;
};

struct Location
{
  Location()
  {
    offset = 0;
    line   = 1;
  }
  uint32_t offset;
  uint16_t line;
};

}  // namespace vm
}  // namespace fetch
