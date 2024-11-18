#include "commons/stringtools.hh"

bool contains(const std::string& input, const std::string& searchToken)
{
  return input.find(searchToken) != std::string::npos;
}

bool startsWith(const std::string& input, const std::string& searchToken)
{
  for(size_t i = 0; i < searchToken.length(); i++) if(input[i] != searchToken[i]) return false;
  return true;
}

bool endsWith(const std::string& input, const std::string& searchToken)
{
  if(searchToken.length() > input.length()) return false;
  size_t j = searchToken.length() - 1;
  for(size_t i = input.length() - 1; i > input.length() - searchToken.length(); i--)
  {
    if(input[i] != searchToken[j]) return false;
    j--;
  }
  return true;
}

std::string subString(const std::string& input, const uint32_t distFromStart, const uint32_t distFromEnd)
{
  return std::string{input.begin() + distFromStart, input.end() - distFromEnd};
}

std::string trim(const std::string& input)
{
  std::string::const_iterator begin = input.begin(), end = input.end();
  while(*begin == ' ') (void)begin++;
  while(*end == ' ') (void)end--;
  return std::string{begin, end};
}

std::string remove(const std::string& input, const char remove)
{
  std::string out = input;
  size_t loc = 0;
  while((loc = out.find(remove)) != std::string::npos) out.replace(loc, 1, "");
  return out;
}

std::string removeMult(const std::string& input, const std::vector<char>& remove)
{
  std::string out = input;
  size_t loc = 0;
  for(const auto& token : remove)
  {
    while((loc = out.find(token)) != std::string::npos)
    {
      out.replace(loc, 1, "");
    }
  }
  return out;
}

std::vector<std::string> split(const std::string& input, const char splitOn, const bool removeMatches)
{
  std::vector<std::string> out;
  if(input.begin() == input.end()) return out;
  std::string::const_iterator iEnd = input.begin(), iBegin = iEnd;
  while(iEnd < input.end())
  {
    if(*iEnd == splitOn)
    {
      if(iBegin != iEnd) out.emplace_back(iBegin, removeMatches ? iEnd : iEnd + 1);
      iBegin = ++iEnd;
      continue;
    }
    (void)iEnd++;
  }
  if(*iEnd == splitOn && iEnd != iBegin) out.emplace_back(iBegin, removeMatches ? iEnd : iEnd + 1);
  else if(iBegin != iEnd) out.emplace_back(iBegin, iEnd);
  return out;
}

std::vector<std::string> splitMult(const std::string& input, const std::vector<char>& splitOn, const bool removeMatches)
{
  std::vector<std::string> out{};
  if(input.empty())
  {
    return out;
  }
  
  std::string::const_iterator iBegin = input.begin(), iEnd = iBegin;
  if(iEnd == input.end())
  {
    return out;
  }
  
  bool matchFound = false;
  do
  {
    matchFound = false;
    for(const auto& token : splitOn)
    {
      if(*iEnd == token)
      {
        if(iBegin != iEnd)
        {
          out.emplace_back(iBegin, removeMatches ? iEnd : iEnd + 1);
        }
        iBegin = ++iEnd;
        if(iEnd >= input.end())
        {
          break;
        }
        matchFound = true;
        break;
      }
    }
    if(!matchFound)
    {
      iEnd++;
    }
  }
  while(iEnd < input.end());
  
  matchFound = false;
  if(iBegin != iEnd)
  {
    for(const auto& token : splitOn)
    {
      if(*iEnd == token)
      {
        matchFound = true;
        out.emplace_back(iBegin, removeMatches ? iEnd : iEnd + 1);
        break;
      }
    }
    if(!matchFound)
    {
      out.emplace_back(iBegin, iEnd);
    }
  }
  return out;
}

std::vector<std::string> splitSeq(const std::string& input, const std::string& splitOn, bool const removeMatches)
{
  std::vector<std::string> out{};
  if(input.begin() == input.end()) return out;
  std::string::const_iterator iEnd = input.begin(), iBegin = iEnd;
  while(iEnd < input.end())
  {
    for(size_t i = 0; i < splitOn.length(); i++)
    {
      if(*iEnd != splitOn[i]) break;
      if(i == splitOn.length() - 1)
      {
        out.emplace_back(iBegin, iEnd + 1 - (removeMatches ? splitOn.size() : 0));
        iBegin = ++iEnd;
        break;
      }
      (void)iEnd++;
    }
    (void)iEnd++;
  }
  if(iBegin != iEnd) out.emplace_back(iBegin, iEnd);
  return out;
}

std::vector<std::string> splitSeqMult(const std::string& input, const std::vector<std::string>& splitOn, bool const removeMatches)
{
  std::vector<std::string> out{};
  if(input.begin() == input.end()) return out;
  std::string::const_iterator iEnd = input.begin(), iBegin = iEnd;
  while(iEnd < input.end())
  {
    for(const auto& token : splitOn) //for each word to split on
    {
      if(iEnd + token.length() > input.end()) continue; //if what we have left is longer than the length of the word we're checking it can't be a match, go to the next word
      for(size_t i = 0; i < token.length(); i++)        //for each letter of the word
      {
        if(*iEnd != token[i]) break; //if the current letters don't match, break out of the loop
        if(i == token.length() - 1)  //if we made it to the end of the word, it's a match, adjust for i starting at 0
        {
          out.emplace_back(iBegin, iEnd + 1 - (removeMatches ? splitOn.size() : 0)); //add the word to the list
          iBegin = ++iEnd;                                                           //and set the iterators to one letter after the word
          break;                                                                     //then end the current loop
        }
        (void)iEnd++; //advance one letter in the input string
      }
    }
    (void)iEnd++;
  }
  if(iBegin != iEnd) out.emplace_back(iBegin, iEnd); //Add any leftover letters to the list
  return out;
}

std::string replaceAll(const std::string& input, const char searchFor, const char replaceWith)
{
  std::string out;
  for(auto &character : input)
  {
    if(character == searchFor) out.push_back(replaceWith);
    else out.push_back(character);
  }
  return out;
}

std::string replaceSeq(const std::string& input, const std::string& search, const std::string& replace)
{
  std::string out;
  for(size_t i = 0; i < input.length(); i++)
  {
    const char& c = input[i];
    if(c != search[0])
    {
      out += c;
    }
    else
    {
      bool match = true;
      for(size_t j = 1; j < search.length(); j++) //See if there's a match
      {
        if(input[i + j] != search[j])
        {
          match = false;
          break;
        }
      }
      if(match)
      {
        out += replace;
        i += search.length() - 1;
      }
      else
      {
        out += c;
      }
    }
  }
  return out;
}
