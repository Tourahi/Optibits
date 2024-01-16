#include <Optibits/Platform.hpp>
#include <Optibits/Utility.hpp>
#include <memory>
#include <stdexcept>
#include <utf8proc.h>


bool Optibits::has_extension(std::string_view filename, std::string_view ext)
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


#ifdef OPTIBITS_IPHONE
// TODO
#else
#include <SDL.h>
#if SDL_VERSION_ATLEAST(2, 0, 14)

std::vector<std::string> Optibits::user_languages()
{
  std::vector<std::string> user_langs;

  std::unique_ptr<SDL_Locale, decltype(SDL_free)*> locales(SDL_GetPreferredLocales(), SDL_free);

  if (!locales) {
    return user_langs;
  }

  for (const SDL_Locale* locale = locales.get(); locale->language != nullptr; ++locale) {
    std::string lang = locale->language;
    if (locale->country) {

    }
    user_langs.emplace_back(std::move(lang));
  }

  return user_langs;
}

#else
// TODO
#endif
#endif
