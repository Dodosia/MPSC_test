#include "logger.hpp"

void print(std::string_view text) {
  static std::mutex mutex;
  const std::lock_guard lock{mutex};
  std::fwrite(text.data(), text.size(), sizeof(char), stdout);
  std::fputc('\n', stdout);
  std::fflush(stdout);
}
