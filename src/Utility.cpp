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



std::u32string Optibits::utf8_to_composed_utc4(std::string_view utf8)
{
  std::u32string utc4;
  utc4.reserve(utf8.size());

  const auto* current_byte = reinterpret_cast<const utf8proc_uint8_t*>(utf8.data());
  auto remaining_length = static_cast<utf8proc_ssize_t>(utf8.length());

  utf8proc_int32_t codepoint;
  while (remaining_length) {
    auto bytes_read = utf8proc_iterate(current_byte, remaining_length, &codepoint);
    if (bytes_read < 0) {
      // Not looking good, skip this byte and retry.
      current_byte += 1;
      remaining_length -= 1;
    }
    else {
      utc4.push_back(codepoint);
      current_byte += bytes_read;
      remaining_length -= bytes_read;
    }
  }

  // Now compose characters in-place.
  auto* utc4_data = reinterpret_cast<utf8proc_int32_t*>(utc4.data());
  auto utc4_length = static_cast<utf8proc_ssize_t>(utc4.length());
  auto options = static_cast<utf8proc_option_t>(UTF8PROC_NLF2LF | UTF8PROC_COMPOSE);
  auto new_length = utf8proc_normalize_utf32(utc4_data, utc4_length, options);
  // GCOV_EXCL_START: No code path in utf8proc_normalize_utf32 currently returns an error.
  if (new_length < 0) {
    throw std::runtime_error("Could not normalize '" + std::string(utf8)
      + "': " + utf8proc_errmsg(new_length));
  }
  // GCOV_EXCL_END
  utc4.resize(new_length);

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

void Optibits::Rect::clip_to(const Rect& boundingBox, int*  adjustX, int*  adjustY)
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


