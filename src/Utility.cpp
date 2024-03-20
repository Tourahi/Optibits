#include <Optibits/Platform.hpp>
#include <Optibits/Utility.hpp>
#include <memory>
#include <stdexcept>
#include <utf8proc.h>


bool Optibits::hasExtension(std::string_view filename, std::string_view ext)
{
  if (ext.starts_with('.')) {
    ext.remove_prefix(1);
  }

  std::size_t extLen = ext.length();
  if (extLen >= filename.length()){
      return false;
  }

  std::string_view::iterator filenameIter = filename.end();
  std::string_view::iterator extIter = ext.end();

  while (extLen--) {
    --filenameIter;
    --extIter;

    if (std::tolower(static_cast<int>(*filenameIter))
      != std::tolower(static_cast<int>(*extIter))) {
      return false;
    }
  }
  --filenameIter;

  return *filenameIter == '.';
}


#ifdef OPTIBITS_IPHONE
#import <Foundation/Foundation.h>
#include <regex>

std::vector<std::string> Optibits::userLanguages()
{
  static const std::regex languageRegex("([a-z]{2})-([A-Z]{2})([^A-Z].*)?");

  std::vector<std::string> userLanguages;

  @autoreleasepool {
    for (NSString* language in [NSLocale preferredLanguages]) {
      std::string languageStr = language.UTF8String;
      std::smatch match;
      if (std::regex_match(languageStr, match, languageRegex)) {
        userLanguages.push_back(match.str(1) + "_" + match.str(2));
      }
    }
  }

  return userLanguages;
}

#else
#include <SDL.h>
#if SDL_VERSION_ATLEAST(2, 0, 14)

std::vector<std::string> Optibits::userLanguages()
{
  std::vector<std::string> userLangs;

  std::unique_ptr<SDL_Locale, decltype(SDL_free)*> locales(SDL_GetPreferredLocales(), SDL_free);

  if (!locales) {
    return userLangs;
  }

  for (const SDL_Locale* locale = locales.get(); locale->language != nullptr; ++locale) {
    std::string lang = locale->language;
    if (locale->country) {

    }
    userLangs.emplace_back(std::move(lang));
  }

  return userLangs;
}

#else

std::vector<std::string> Optibits::userLanguages()
{
  static const std::regex languageRegex("[a-z]{2}_[A-Z]{2}([^A-Z].*)?");

  const char* locale = std::getenv("LANG");

  if (locale && std::regex_match(locale, languageRegex)) {
    // Trim off anything after the language code.
    return { std::string(locale, locale + 5) };
  }

  return {};
}

#endif
#endif



std::u32string Optibits::utf8ToComposedUtc4(std::string_view utf8)
{
  std::u32string utc4;
  utc4.reserve(utf8.size());

  const auto* currentByte = reinterpret_cast<const utf8proc_uint8_t*>(utf8.data());
  auto remainingLength = static_cast<utf8proc_ssize_t>(utf8.length());

  utf8proc_int32_t codepoint;
  while (remainingLength) {
    auto bytesRead = utf8proc_iterate(currentByte, remainingLength, &codepoint);
    if (bytesRead < 0) {
      // Not looking good, skip this byte and retry.
      currentByte += 1;
      remainingLength -= 1;
    }
    else {
      utc4.push_back(codepoint);
      currentByte += bytesRead;
      remainingLength -= bytesRead;
    }
  }

  // Now compose characters in-place.
  auto* utc4Data = reinterpret_cast<utf8proc_int32_t*>(utc4.data());
  auto utc4Length = static_cast<utf8proc_ssize_t>(utc4.length());
  auto options = static_cast<utf8proc_option_t>(UTF8PROC_NLF2LF | UTF8PROC_COMPOSE);
  auto newLength = utf8proc_normalize_utf32(utc4Data, utc4Length, options);
  // GCOV_EXCL_START: No code path in utf8proc_normalize_utf32 currently returns an error.
  if (newLength < 0) {
    throw std::runtime_error("Could not normalize '" + std::string(utf8)
      + "': " + utf8proc_errmsg(newLength));
  }
  // GCOV_EXCL_END
  utc4.resize(newLength);

  return utc4;

}

bool Optibits::Rect::overlaps(const Rect& other) const
{
  return x < other.right() && other.x < right() && y < other.bottom() && other.y < bottom();
}

bool Optibits::Rect::contains(const Rect& other) const
{
  return x <= other.x && other.right() <= right() && y <= other.y && other.bottom() <= bottom();
}

void Optibits::Rect::clipTo(const Rect& boundingBox, int*  adjustX, int*  adjustY)
{

  const int extraPixelsLeft = boundingBox.x - x;
  if (extraPixelsLeft) {
    x += extraPixelsLeft;
    width -= extraPixelsLeft;
    if (adjustX) {
      *adjustX += extraPixelsLeft;
    }
  }

  const int extraPixelsRight = right() - boundingBox.right();
  if (extraPixelsRight) {
    width -= extraPixelsRight;
  }

  const int extraPixelsTop = boundingBox.y - y;
  if (extraPixelsTop) {
    y += extraPixelsTop;
    height -= extraPixelsTop;
    if (adjustY) {
      *adjustY += extraPixelsTop;
    }
  }

  const int extraPixelsBottom = bottom() - boundingBox.bottom();
  if (extraPixelsBottom) {
    height -= extraPixelsBottom;
  }

  if (width < 0) { width = 0; }
  if (height < 0) { height = 0; }
}


