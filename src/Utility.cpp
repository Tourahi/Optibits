#include <Optibits/Platform.hpp>
#include <Optibits/Utility.hpp>
#include <memory>
#include <stdexcept>
#include <utf8proc.h>


bool Optibits::has_extention(std::string_view filename, std::string_view ext)
{
  if (ext.starts_with('.')) {
    ext.remove_prefix(1);
  }

  std::size_t ext_len = ext.length();
  if (ext_len >= filename.length()){
      return false;
  }

  std::string_view::iterator filename_iter = filename.end();
  std::string_view::iterator ext_iter = ext.end();

  while (ext_len--) {
    --filename_iter;
    --ext_iter;

    if (std::tolower(static_cast<int>(*filename_iter))
      != std::tolower(static_cast<int>(*ext_iter))) {
      return false;
    }
  }
  --filename_iter;

  return *filename_iter == '.';
}